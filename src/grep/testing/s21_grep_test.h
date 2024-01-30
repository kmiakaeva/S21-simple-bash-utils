#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "test_utils.h"

#define PATH "testing/test-samples/"
#define S21_OUTPUT PATH "s21_output.txt"
#define GREP_OUTPUT PATH "grep_output.txt"
#define VALGRIND_OUTPUT PATH "valgrind.txt"
#define TEST_FILES                                              \
  PATH "test_1.txt " PATH "test_2.txt " PATH "test_3.txt " PATH \
       "test_4.txt " PATH "test_5.txt "
#define FLAGS_COUNT 10
#define VALGRIND "valgrind --tool=memcheck --leak-check=yes "
#define SUCCESS "\033[42m\033[1;37m SUCCESS :) \033[0m\n"
#define FAIL "\033[41m\033[1;37m FAILED :( \033[0m\n"

const char flags[FLAGS_COUNT][4] = {"-i ", "-v ", "-c ", "-l ", "-n ",
                                    "-h ", "-s ", "-o ", "-e ", "-f "};

void start_testing(int param, int valgrind);
void system_call(char* line_flags, int valgrind);
int file_compare(int valgrind);