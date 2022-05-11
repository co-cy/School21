all: cat grep

grep:
#-Wextra -Werror
	gcc -g -fsanitize=address src/grep/grep.c src/linked_list/linked_list.c -o build/s21_grep
cat:
	gcc -Wextra -Werror -Wall -g -fsanitize=address src/cat/cat.c -o build/s21_cat

run_test_cat: cat
	python test_cat.py

run_test_grep: grep
	python3 test_grep.py

test:
	gcc main.c