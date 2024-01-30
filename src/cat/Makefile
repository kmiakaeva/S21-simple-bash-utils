CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
TEST_PATH=testing

all: s21_cat test

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	$(CC) $(CFLAGS) $(TEST_PATH)/s21_cat_test.c -o s21_cat_test

run:
	./s21_cat_test 1

rebuild: clean all

clean:
	rm s21_cat s21_cat_test