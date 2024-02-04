CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g
TEST_PATH=testing

all: rebuild

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	$(CC) $(CFLAGS) $(TEST_PATH)/s21_cat_test.c -o s21_cat_test

run:
	./s21_cat_test 1

rebuild: clean s21_cat test

clean:
	rm -rf s21_cat test
