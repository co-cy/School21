all: cat grep
	gcc -Wextra -Werror -Wall src/cat/cat.c -o build/s21_cat

grep:
	gcc -Wextra -Werror -Wall src/grep/main.c -o build/s21_grep
cat:
	gcc -Wextra -Werror -Wall src/cat/cat.c -o build/s21_cat

run_test_cat: cat
	python test_cat.py

run_test_grep: grep
	python test_grep.py