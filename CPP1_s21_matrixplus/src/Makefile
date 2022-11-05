BUILD_DIR="build"

files="./test/sub_matrix.cpp" "./test/construct.cpp" "./test/eq_test.cpp" "./test/mul_matrix.cpp" "./test/mul_num.cpp" "./test/calc_matrix.cpp" "./test/other.cpp" "./test/sum_matrix.cpp" "./test/inverse_matrix.cpp" "./test/det_matrix.cpp" "./other/inverse.cpp" "./other/determiant.cpp" "./other/complements.cpp" "./other/crop.cpp" "./other/transpose.cpp" "./arithmetic/merge.cpp" "./arithmetic/mult.cpp" "./operators/operators.cpp" "./core/constructor.cpp" "./core/resize.cpp" "./core/destructor.cpp" "./comparison/eq.cpp" "./test/transpose_matrix.cpp"

all: clean
	g++ -I. $(files) -lgtest -lgtest_main --coverage -std=c++17 -fsanitize=address -Wall -Wextra -Werror -Wpedantic -g
	./a.out
	geninfo $(shell find . -name '*.gcda' -or -name '*.gcno') . -o bebra
	genhtml bebra -o coverage

.PHONY: all


clean:
	-rm -rf $(shell find . -name "*\.gcda" -or -name "*\.gcno") coverage bebra a.out
.PHONY: all
