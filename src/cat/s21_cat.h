#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {0, 0, 0, 0}};

typedef struct {
  bool b, e, n, s, t, v;
} Flags;

void process_file(Flags flags, const char* filename);
void cat(FILE* file, const Flags flags);
bool check_flags(int argc, char* argv[], Flags* flags);