#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char *pattern = (char *)calloc(SIZE, sizeof(char));
  Flags flags = {false};
  Params params = {false, false, 0, 0};

  if (argc < 2) {
    fprintf(stderr, "Missing arguments\n");
    params.error = true;
  } else {
    check_flags(argc, argv, &flags, &params, &pattern);
  }

  if (!params.error) {
    if (!flags.f && !flags.e) {
      add_pattern(&pattern, argv[optind++]);
    }

    if (argc - optind > 1) params.multifile = true;

    for (int i = optind; i < argc; i++) {
      process_file(flags, &params, argv[i], pattern);
    }
  } else {
    fprintf(stderr, "Usage: ./s21_grep [flag] [pattern] [file]\n");
  }

  free(pattern);

  return params.error;
}

void check_flags(int argc, char *argv[], Flags *flags, Params *params,
                 char **pattern) {
  int option;

  while ((option = getopt(argc, argv, "e:ivclnhsf:o")) != -1 &&
         !(params->error)) {
    if (option == 'e') {
      flags->e = true;
      add_pattern(pattern, optarg);
    } else if (option == 'i') {
      flags->i = true;
    } else if (option == 'v') {
      flags->v = true;
    } else if (option == 'c') {
      flags->c = true;
    } else if (option == 'l') {
      flags->l = true;
    } else if (option == 'n') {
      flags->n = true;
    } else if (option == 'h') {
      flags->h = true;
    } else if (option == 's') {
      flags->s = true;
    } else if (option == 'f') {
      flags->f = true;
      params->files_count++;
      process_file_pattern(params, pattern, optarg);
    } else if (option == 'o') {
      flags->o = true;
    } else {
      params->error = true;
    }
  }

  if (flags->l) {
    flags->c = false, flags->n = false, flags->o = false;
  }

  if (flags->c) {
    flags->n = false, flags->o = false;
  }

  if (optind >= argc || argv[optind][0] == '-' || strlen(argv[optind]) == 0) {
    params->error = true;
  }
}

void process_file_pattern(Params *params, char **pattern, char *optarg) {
  FILE *file = fopen(optarg, "r");

  if (file != NULL) {
    char *line = NULL;
    size_t length = 0;

    while ((getline(&line, &length, file)) != -1) {
      add_pattern(pattern, line);
    }

    free(line);
    fclose(file);
  } else {
    params->error = true;
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
  }
}

void add_pattern(char **pattern, char *line) {
  char *copy_line = malloc(strlen(line) + 10);
  strcpy(copy_line, line);

  if (copy_line[0] == '\0' || copy_line[0] == '\n') {
    strcpy(copy_line, "$");
  }

  replace_linebreak(&copy_line);

  static size_t buffer = SIZE;
  while (strlen(*pattern) + strlen(line) + 10 > buffer) {
    buffer *= 2;
    *pattern = (char *)realloc(*pattern, buffer * sizeof(char));
  }

  sprintf(*pattern + strlen(*pattern), "%s\\(%s\\)", *pattern[0] ? "\\|" : "",
          copy_line);

  free(copy_line);
}

void replace_linebreak(char **line) {
  int last_index = (int)strlen(*line) - 1;
  if ((*line)[last_index] == '\n') (*line)[last_index] = '\0';
}

void process_file(Flags flags, Params *params, const char *filename,
                  char *pattern) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    regex_t regex;

    regex_compile(flags, params, &regex, pattern);

    if (!params->error && !(flags.o && flags.v)) {
      if (flags.o) {
        process_flag_o(flags, params, file, &regex, filename);
      } else {
        process_file_lines(flags, params, file, &regex, filename);
      }
    }

    regfree(&regex);
    fclose(file);
  } else if (!flags.s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
  }
}

void regex_compile(Flags flags, Params *params, regex_t *regex, char *pattern) {
  if (regcomp(regex, pattern, flags.i ? REG_ICASE : 0)) {
    params->error = true;
    fprintf(stderr, "Error compiling regex\n");
  }
}

void process_flag_o(Flags flags, Params *params, FILE *file, regex_t *regex,
                    const char *filename) {
  regmatch_t match;
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, status;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    replace_linebreak(&line);

    char *copy_line = strdup(line);
    char *original_copy_line = copy_line;

    while (((status = regexec(regex, copy_line, 1, &match, REG_NOTEOL)) == 0) &&
           strlen(copy_line)) {
      if (match.rm_so == match.rm_eo) {
        copy_line++;
        continue;
      }

      if (params->multifile && !flags.h) printf("%s:", filename);
      if (flags.n) printf("%d:", line_count);
      printf("%.*s\n", (int)match.rm_eo - (int)match.rm_so,
             copy_line + match.rm_so);

      copy_line += match.rm_eo;
    }

    free(original_copy_line);
    original_copy_line = NULL;
  }

  free(line);
  line = NULL;
}

void process_file_lines(Flags flags, Params *params, FILE *file, regex_t *regex,
                        const char *filename) {
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, match_count = 0;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    replace_linebreak(&line);

    int status = regexec(regex, line, 0, NULL, 0);

    if (!status ^ flags.v) {
      if (flags.l) {
        printf("%s\n", filename);
        break;
      }

      match_count++;

      if (!flags.c) {
        if (params->multifile && !flags.h) printf("%s:", filename);
        if (flags.n) printf("%d:", line_count);
        printf("%s\n", line);
      }
    }
  }

  if (flags.c) {
    if (params->multifile && !flags.h) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  free(line);
  line = NULL;
}