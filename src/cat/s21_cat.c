#include "s21_cat.h"

int main(int argc, char* argv[]) {
  Flags flags = {false};
  bool is_correct_flag = check_flags(argc, argv, &flags);

  if (is_correct_flag) {
    for (int i = optind; i < argc; i++) {
      process_file(flags, argv[i]);
    }
  }

  return !is_correct_flag;
}

bool check_flags(int argc, char* argv[], Flags* flags) {
  bool is_correct_flag = true;
  int option, option_index = 0;

  while ((option = getopt_long(argc, argv, "beEnstTv", long_options,
                               &option_index)) != -1 &&
         is_correct_flag) {
    if (option == 'b') {
      flags->b = true;
      flags->n = false;
    } else if (option == 'e') {
      flags->e = true;
      flags->v = true;
    } else if (option == 'E') {
      flags->e = true;
    } else if (option == 'n') {
      flags->n = !flags->b;
    } else if (option == 's') {
      flags->s = true;
    } else if (option == 't') {
      flags->t = true;
      flags->v = true;
    } else if (option == 'T') {
      flags->t = true;
    } else if (option == 'v') {
      flags->v = true;
    } else {
      is_correct_flag = false;
    }
  }

  if (!is_correct_flag) fprintf(stderr, "Unknown flag entered\n");

  return is_correct_flag;
}

void process_file(Flags flags, const char* filename) {
  FILE* file = fopen(filename, "r");

  if (file != NULL) {
    cat(file, flags);
    fclose(file);
  } else {
    fprintf(stderr, "Could not open the file: %s\n", filename);
  }
}

void cat(FILE* file, const Flags flags) {
  static int symbol, prev_symbol = '\n';
  static int newline_count = 0, line_num = 0;

  while ((symbol = fgetc(file)) != EOF) {
    if (symbol == '\n' && prev_symbol == '\n') {
      newline_count++;
    } else {
      newline_count = 0;
    }

    if (flags.s && newline_count > 1) continue;

    if (prev_symbol == '\n' && (flags.n || (flags.b && symbol != '\n')))
      printf("%6d\t", ++line_num);

    if (flags.t && symbol == '\t') {
      printf("^");
      symbol += 64;
    }

    if (flags.e && symbol == '\n') printf("$");

    if (flags.v && symbol != '\t' && symbol != '\n') {
      if (symbol > 127) {
        printf("M-");
        symbol -= 128;
      }

      if (symbol < 32 || symbol == 127) {
        printf("^");
        symbol = symbol == 127 ? symbol - 128 + 64 : symbol + 64;
      }
    }

    printf("%c", symbol);
    prev_symbol = symbol;
  }
}
