#include "s21_grep_test.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Usage: ./s21_grep_test [flag 0-5] [valgrind v or 0]\n");
    return 1;
  }

  char flag = argv[1][0];
  char v_flag = argv[2][0];

  if (flag >= '0' && flag <= '5' && (v_flag == 'v' || v_flag == '0')) {
    create_tests();
    start_testing(flag - '0', v_flag == 'v' ? 1 : 0);
    printf("\t\t\tCreated by huldades and lorindab\n");
  } else {
    printf("Usage: ./s21_grep_test [flag 0-5] [valgrind v or 0]\n");
  }

  return 0;
}

void start_testing(int max_flags, int valgrind) {
  int tests_count = 1;

  for (int i = 0, j = FLAGS_COUNT; i < max_flags; i++, j *= FLAGS_COUNT)
    tests_count += j;

  for (int test_id = -1; test_id < tests_count - 1; test_id++) {
    srand(/* (int)time(NULL) +*/ test_id);  // for preset random use <test_id>
                                            // add flag -r?

    int param = 1, prev_flag = FLAGS_COUNT, skip_test = 0;
    char line_flags[200] = {0};
    char ch[2] = "0";  // grep, for strcat()

    for (int copy_id = test_id; copy_id >= 0;
         copy_id = copy_id / FLAGS_COUNT - 1) {
      int flag_id = (copy_id) % FLAGS_COUNT;

      if (flag_id > prev_flag) {
        skip_test = 1;
        break;
      }
      prev_flag = flag_id;

      strcat(line_flags, flags[flag_id]);

      if (flag_id == 8) {
        for (int i = rand() % 3 + 1; i > 0; i--) {
          do ch[0] = rand() % 128;
          while (!isalnum(ch[0]));
          strcat(line_flags, ch);
        }

        strcat(line_flags, " ");
        param = 0;
      }

      if (flag_id == 9) {
        sprintf(line_flags + strlen(line_flags), PATH "test_%d.txt ",
                rand() % 5 + 1);
        param = 0;
      }
    }

    if (skip_test) continue;
    printf("\033[1;37mTest %3d / %3d: \033[0m", test_id + 2, tests_count);

    for (int i = rand() % 3 + 1; param && i > 0; i--) {
      do ch[0] = rand() % 128;
      while (!isalnum(ch[0]));
      strcat(line_flags, ch);
    }

    strcat(line_flags, " ");
    system_call(line_flags, valgrind);

    int error = file_compare(valgrind);

    if (error) {
      paint_pikachu(1);

      // if (max_flags > 0)  // grep
      printf("\033[1;37mWrong flag: %s\033[0m\n", line_flags);
      // else
      //   printf("Wrong work without flags\n");  // grep
      printf("Output_compare: %s\n", error & 1 ? FAIL : SUCCESS);
      printf("Valgrind: %s\n", error & 2 ? FAIL : SUCCESS);

      exit(1);
    }

    if (!error) printf(SUCCESS);
  }

  paint_tyan();
  system("rm -rf testing/test-samples/");
}

void system_call(char* line_flags, int valgrind) {
  char command[BUFSIZ] = {0};

  sprintf(command, "./s21_grep %s %s > %s", line_flags, TEST_FILES, S21_OUTPUT);
  printf("%s\n", command);
  system(command);

  sprintf(command, "grep %s %s > %s", line_flags, TEST_FILES, GREP_OUTPUT);
  printf("%s\n", command);
  system(command);

  if (valgrind) {
    sprintf(command, VALGRIND "./s21_grep %s %s > %s 2>&1", line_flags,
            TEST_FILES, VALGRIND_OUTPUT);
    printf("%s\n", command);
    system(command);
  }
}

int file_compare(int valgrind) {
  int error = 0;

  FILE* s21_file = fopen(S21_OUTPUT, "r");
  FILE* grep_file = fopen(GREP_OUTPUT, "r");

  while (1) {
    int ch1 = fgetc(s21_file);
    int ch2 = fgetc(grep_file);

    if (ch1 == EOF && ch2 == EOF) break;
    if (ch1 != ch2) {
      error = 1;
      break;
    }
  }

  fclose(s21_file);
  fclose(grep_file);

  if (valgrind) {
    FILE* valgrind_file = fopen(VALGRIND_OUTPUT, "r");

    const char noleaks[100] =
        "All heap blocks were freed -- no leaks are possible";
    char line[100] = {0};
    int no_leaks = 0;

    while (fgets(line, 100, valgrind_file) != NULL && !no_leaks)
      if (strstr(line, noleaks) != NULL) no_leaks = 1;

    if (!no_leaks) error += 2;

    fclose(valgrind_file);
  }

  return error;
}