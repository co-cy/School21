CC=gcc

CFLAGS = -Wall -Wextra -Werror # -g -fsanitize=address
TARGET_CAT=cat/s21_cat
SOURCE_CAT=cat/s21_cat.c

TARGET_GREP=grep/s21_grep
SOURCE_GREP=grep/s21_grep.c

all: s21_cat s21_grep
.PHONY : all

$(TARGET_CAT): $(SOURCE_CAT)
	$(CC) $(CFLAGS) $(SOURCE_CAT) -o $(TARGET_CAT)

s21_cat: $(TARGET_CAT)
.PHONY : s21_cat

$(TARGET_GREP): $(SOURCE_GREP) $(SOURCE_GREP)
	$(CC) $(CFLAGS) $(SOURCE_GREP) -o $(TARGET_GREP)

s21_grep: $(TARGET_GREP)
.PHONY : s21_grep


clean:
	rm -f $(TARGET_CAT) $(TARGET_GREP)
.PHONY : clean
