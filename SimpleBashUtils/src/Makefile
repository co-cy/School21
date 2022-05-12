CC = gcc
ASAN = -g -fsanitize=address
CFLAG := -c -Wextra -Werror -Wall -std=c11 $(ASAN)

PY = python3

OBJ_DIR = build/obj

RM = rm -f
MK = mkdir -p

.PHONY = all run_test_cat run_test_grep clean re rebuild

s21_cat:
	$(CC) cat/cat.c -o s21_cat

s21_grep:
	$(CC) grep/grep.c grep/grep_parser.c grep/more_string.c linked_list/linked_list.c -o s21_grep

all: s21_cat s21_grep

run_test_cat: $(TARGET_CAT)
	$(PY) ../test_cat.py

run_test_grep: $(TARGET_GREP)
	$(PY) ../test_grep.py

clean:
	$(RM) grep/grep.o grep/grep_parser.o grep/more_string.o linked_list/linked_list.o s21_cat s21_grep

re: clean all
rebuild: clean all