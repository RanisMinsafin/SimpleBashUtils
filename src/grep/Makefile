CFLAGS = -Wall -Werror -Wextra 
CC = gcc 

all: s21_grep

s21_grep :
		$(CC) s21_grep.c $(CFLAGS) -o s21_grep

test : 
		$(CC) s21_grep.c $(CFLAGS) -o s21_grep
		sh test_func_grep.sh

clean : 
		rm -rf *.o
		rm -rf *.log
		rm -rf s21_grep

rebuild:
		make clean
		make all