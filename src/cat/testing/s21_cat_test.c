#include "s21_cat_test.h"

int main(int argc, char* option[]) {
  if (argc == 2 && option[1][0] >= '0' && option[1][0] <= '3') {
    create_tests();
    start_testing(option[1][0]);
    printf("\t\t\tCreated by huldades and lorindab\n");
  } else {
    printf("Usage: ./s21_cat_test [flag 0-3]\n");
  }

  return 0;
}

void start_testing(int option) {
  for (int flags_count = 0; flags_count <= option - '0'; flags_count++) {
    int tests_count = 1;

    for (int i = 0; i < flags_count; i++) tests_count *= 11;

    for (int test_id = 0; test_id < tests_count; test_id++) {
      printf("\033[1;37mTest %3d / %3d: \033[0m", test_id + 1, tests_count);

      char line_flags[200] = {0};
      int copy_id = test_id;
      for (int j = 0; j < flags_count; j++) {
        strcat(line_flags, flags[copy_id % 11]);
        copy_id /= 11;
      }

      system_call(line_flags);

      int error = file_compare();

      if (error) {
        paint_pikachu();

        if (flags_count > 0)
          printf("\033[1;37mWrong flag: %s\033[0m\n", line_flags);
        else
          printf("Wrong work without flags\n");

        exit(1);
      }

      printf("\033[42m\033[1;37mSUCCESS :)\033[0m\n");
    }
  }

  paint_tyan();
  system("rm -rf " PATH);
}

void system_call(char* line_flags) {
  char command[BUFSIZ] = {0};

  sprintf(command, "./s21_cat %s %s > %s", line_flags, TEST_FILES, S21_OUTPUT);
  system(command);

  sprintf(command, "cat %s %s > %s", line_flags, TEST_FILES, CAT_OUTPUT);
  system(command);
}

int file_compare() {
  int error = 0;

  FILE* s21_cat_file = fopen(S21_OUTPUT, "r");
  FILE* cat_file = fopen(CAT_OUTPUT, "r");

  while (1) {
    int ch1 = fgetc(s21_cat_file);
    int ch2 = fgetc(cat_file);

    if (ch1 == EOF && ch2 == EOF) break;
    if (ch1 != ch2) {
      error = 1;
      break;
    }
  }

  fclose(s21_cat_file);
  fclose(cat_file);

  return error;
}

void create_tests() {
  create_dir();

  create_test_1();
  create_test_2();
  create_test_3();
  create_test_4();
  create_test_5();
}

void create_dir() {
  mkdir("testing", 0777);
  if (mkdir("testing/test-samples", 0777) == 0) {
    printf("Folder created\n");
  }
}

void create_test_1() {
  FILE* f = fopen(PATH "test_1.txt", "w");
  fprintf(f, "\nabc end\n\n\nabcabcabc end\n\n\n\nabcabcabcabc end\n\n");
  fclose(f);
}

void create_test_2() {
  FILE* f = fopen(PATH "test_2.txt", "w");
  fprintf(f, "tab	tab	end\n\nabc tab	1abc end\nabc end\n\n");
  fclose(f);
}

void create_test_3() {
  FILE* f = fopen(PATH "test_3.txt", "w");

  for (int ch = 0; ch < 128; ch++) {
    fprintf(f, "%c", ch);
  }

  fclose(f);
}

void create_test_4() {
  FILE* f = fopen(PATH "test_4.txt", "w");
  fprintf(f,
          "	\n    		\n            			\n             "
          "           				\n                             "
          "           					");
  fclose(f);
}

void create_test_5() {
  FILE* f = fopen(PATH "test_5.txt", "w");
  fclose(f);
}

void paint_pikachu() {
  printf("\n");
  printf("\033[48;5;226m\033[1;30m⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿\033[0m\n");
  printf("\033[48;5;226m\033[1;30m⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿\033[0m\n");
  printf("\033[41m\033[1;37m        FAILED :(        \033[0m\n");
}

void paint_tyan() {
  printf("\033[48;5;93m\033[1;37m  ⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⡠⢴⣴⣾⣿⡿⠓⡠⠀⠀⠀⠀⠠⢄⠁⢀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠳⣽⡽⠀⠀⡠⢊⣴⣿⣿⣿⣡⠖⠁⣀⡤⢖⠟⠁⡠⠀⡙⢿⣷⣄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠐⡀⠀⠀⠀⠀⢠⣾⣿⣿⢽⣿⣿⣿⣥⠖⣻⣯⡾⠃⠀⡔⡀⠀⣷⢸⢿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⢰⠀⠀⠀⢠⢟⣿⠃⢀⣾⣿⠟⠋⢀⡾⢋⣾⠃⣠⡾⢰⡇⡇⣿⣿⡞⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡤⣈⡀⠀⢀⠏⣼⣧⡴⣼⠟⠁⠀⠀⡾⠁⣾⡇⣰⢿⠃⢾⣿⣷⣿⣿⣇⢿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠱⠼⠊⠀⠄⡜⣿⣿⡿⠃⠈⠁⠀⢸⠁⢠⡿⣰⢯⠃⠀⠘⣿⣿⣿⣿⣿⠸\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⡘⡀⣸⣿⣱⡤⢴⣄⠀⠈⠀⠘⣷⠏⠌⠢⡀⠀⢿⣿⣿⣿⡟⡄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⢀⣌⠌⣴⣿⣿⠃⣴⣿⣟⡇⠀⠀⠀⠟⠀⠀⠀⠈⠢⢈⣿⡟⣿⡗⡇\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⢀⡴⡻⣡⣾⠟⢹⡇⠀⡇⢄⢿⠇⠀⠀⠀⠀⠀⠀⣽⣶⣄⡀⠘⢷⡹⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⣧⣾⡿⠋⠁⢀⡜⠙⡄⠓⠐⠁⠀⠀⠀⠀⠀⠀⡼⠛⠻⣟⠛⣆⠈⢷⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⣴⣾⣟⣵⣿⣿⣿⣁⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠠⠔⡹⠀⢸⠀⣼⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠿⡽⢫⡉⠀⣠⠔⠁⡀⠕⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠖⠊⠀⠀⢊⣾⢿⡿⠉\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠁⠀⡹⢨⠁⠐⠈⢀⡠⠐⠁⠄⠡⡀⡀⠀⠀⠀⠀⠀⠀⠀⠠⠶⢛⡨⠊⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡜⠀⠈⣂⠀⠀⠀⠀⡠⠐⠉⡆⠀⣀⢀⣀⣀⣀⡀⠀⠀⣀⠴⣁⡀⠤⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠈⠀⠀⠀⡇⠑⢄⠀⠀⠀⠀⣲⢥⡎⠀⢰⠀⢸⠀⢀⠉⠙⣿⣧⣀⣀⣂⣤⣼\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠆⠁⠃⠀⠀⠈⠒⠒⠊⣸⠚⠁⠀⠀⠀⠀⠀⠀⠀⡜⠁⠀⠀⠀⠀⠈⠚\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⢀⠋⢆⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠂⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[42m\033[1;37m   YOU'RE AWESOME!  \\(^.^)/   \033[0m\n");
}