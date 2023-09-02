CFLAGS = -Wall -Werror -Wextra 
CC = gcc 

all: s21_cat

s21_grep :
		$(CC) s21_cat.c $(CFLAGS) -o s21_cat

test : 
		$(CC) s21_cat.c $(CFLAGS) -o s21_cat
		sh test_func_cat.sh

clean : 
		rm -rf *.o
		rm -rf *.log
		rm -rf s21_cat

rebuild:
		make clean
		make all