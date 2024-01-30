#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH "testing/test-samples/"
#define S21_OUTPUT (PATH "s21_output.txt")
#define CAT_OUTPUT (PATH "cat_output.txt")
#define TEST_FILES                                              \
  PATH "test_1.txt " PATH "test_2.txt " PATH "test_3.txt " PATH \
       "test_4.txt " PATH "test_5.txt "

const char flags[11][30] = {"-b ",
                            "-e ",
                            "-E ",
                            "-n ",
                            "-s ",
                            "-t ",
                            "-T ",
                            "-v ",
                            "--number-nonblank ",
                            "--number ",
                            "--squeeze-blank "};

void start_testing(int param);
void system_call(char* line_flags);
int file_compare();
void paint_pikachu();
void paint_tyan();
void create_dir();
void create_tests();
void create_test_1();
void create_test_2();
void create_test_3();
void create_test_4();
void create_test_5();