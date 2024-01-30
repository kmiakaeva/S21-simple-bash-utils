#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

typedef struct {
  bool e, i, v, c, l, n, h, s, f, o;
} Flags;

typedef struct {
  bool multifile, error;
  int patterns_count, files_count;
} Params;

void check_flags(int argc, char *argv[], Flags *flags, Params *params,
                 char **pattern);
void process_file_pattern(Params *params, char **pattern, char *optarg);
void add_pattern(char **pattern, char *line);
void replace_linebreak(char **line);
void process_file(Flags flags, Params *params, const char *filename,
                  char *pattern);
void regex_compile(Flags flags, Params *params, regex_t *regex, char *pattern);
void process_flag_o(Flags flags, Params *params, FILE *file, regex_t *regex,
                    const char *filename);
void process_file_lines(Flags flags, Params *params, FILE *file, regex_t *regex,
                        const char *filename);