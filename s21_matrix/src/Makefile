CC := gcc
AR := ar rc
RAN := ranlib

CFLAGS = -Wall -Wextra -Werror -std=c11

SOURCE := s21_matrix.c common/features.c
beba := ${SOURCE:c=o}

all: $(beba) s21_matrix
.PHONY : all

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

s21_matrix: $(SOURCE)
	$(AR) -r lib.a $(beba)
	$(RAN) lib.a

s21_matrix_d: $(CC += -g -fsanitize=address) s21_matrix
