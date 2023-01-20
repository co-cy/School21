CC := gcc
AR := ar -rc
RAN := ranlib

FLAGS := -g -fsanitize=address -Wall -Wextra -Werror -std=c11 -lcheck --coverage

SOURCE := $(shell find . -name '*.c' -not -path './test/*' -and -not -path './debug/*')
SOURCE_TEST := $(shell find test -name '*.c')

OBJS := ${SOURCE:.c=.o}
OBJS_TEST := ${SOURCE_TEST:.c=.o}

TARGET := s21_matrix.a
TARGET_TEST := test.out

.PHONY : all
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(AR) $@ $^

.PHONY : clean
clean:
	rm -rf $(OBJS) $(TARGET) $(TARGET_TEST) $(OBJS_TEST) $(shell find . -name '*.gcda' -or -name '*.gcno') bebra coverage


.PHONY : test
test: CFLAGS+=$(FLAGS)
test: $(TARGET) $(OBJS_TEST)
	$(CC) $(CFLAGS) $(TARGET) $(OBJS_TEST) -o $(TARGET_TEST)

.PHONY : gcov_report
gcov_report: test
	geninfo $(shell find . -name '*.gcda' -or -name '*.gcno') -b . -o bebra
	genhtml bebra -o coverage

.PHONY : open
open: gcov_report
	open coverage/index.html

.PHONY : lint
lint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(shell find . -name '*.c' -not -path './test/*')

	rm CPPLINT.cfg
	cppcheck --enable=all --suppress=missingIncludeSystem $(shell find . -name '*.c' -not -path './test/*')
