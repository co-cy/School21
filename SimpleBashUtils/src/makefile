CC = gcc
ASAN = -g -fsanitize=address
CFLAG := -c -Wextra -Werror -Wall -std=c11 $(ASAN)

PY = python3

TARGET_CAT = s21_cat
SOURCE_CAT = src/cat/cat.c

TARGET_GREP = s21_grep
SOURCE_GREP = grep/grep.c grep/grep_parser.c grep/more_string.c

SOURCE_LIB = linked_list/linked_list.c

OBJ_CAT = $(SOURCE_CAT:.c=.o)
OBJ_GREP = $(SOURCE_GREP:c=o)
OBJ_LIB = $(SOURCE_LIB:c=o)

OBJ_DIR = build/obj

RM = rm -f
MK = mkdir -p

.PHONY = all run_test_cat run_test_grep clean re rebuild s21_cat s21_grep
all: $(TARGET_CAT) $(TARGET_GREP)

s21_cat: $(TARGET_CAT)
s21_grep: $(TARGET_GREP)

$(TARGET_CAT): $(OBJ_CAT)
	$(CC) $(OBJ_CAT) -o $(TARGET_CAT)

$(TARGET_GREP): $(OBJ_GREP) $(OBJ_LIB)
	$(CC) $(OBJ_GREP) $(OBJ_LIB) -o $(TARGET_GREP)

$(OBJ_DIR):
	$(MK) $(OBJ_DIR)

$(SOURCE_CAT):
	$(CC) $< -o $@

$(SOURCE_GREP):
	$(CC) $< -o $@

$(SOURCE_LIB):
	$(CC) $< -o $@

run_test_cat: $(TARGET_CAT)
	$(PY) ../test_cat.py

run_test_grep: $(TARGET_GREP)
	$(PY) ../test_grep.py

clean:
	$(RM) $(TARGET_CAT)
	$(RM) $(TARGET_GREP)
	$(RM) $(OBJ_CAT) $(OBJ_GREP) $(OBJ_LIB)

re: clean all
rebuild: clean all