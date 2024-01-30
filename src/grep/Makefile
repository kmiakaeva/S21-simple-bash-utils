CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g
TEST_PATH=testing

all: rebuild

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test:
	$(CC) $(CFLAGS) $(TEST_PATH)/s21_grep_test.c $(TEST_PATH)/test_utils.c -o s21_grep_test

run:
	./s21_grep_test 2 v

rebuild: clean s21_grep test

clean:
	rm -rf s21_grep test