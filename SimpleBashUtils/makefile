all: cat grep

grep:
#-Wextra -Werror
	gcc -g -fsanitize=address src/grep/new_grep.c src/linked_list/linked_list.c -o build/s21_grep
cat:
	gcc -Wextra -Werror -Wall -g -fsanitize=address src/cat/cat.c -o build/s21_cat

run_test_cat: cat
	python test_cat.py

run_test_grep: grep
	gcc -lcheck -g -fsanitize=address src/grep/test/*.c -o build/s21_grep_test
test:
	gcc main.c