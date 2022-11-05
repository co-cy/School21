BUILD_DIR="build"

all: s21_matrix_oop.a
.PHONY: all

clean:
	-rm -rf $(BUILD_DIR)
.PHONY: clean

test:
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=TEST -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
	make -C $(BUILD_DIR) tests
	./$(BUILD_DIR)/tests
	geninfo $(shell find . -name '*.gcda' -or -name '*.gcno') . -o ./$(BUILD_DIR)/info
	genhtml ./$(BUILD_DIR)/info -o ./$(BUILD_DIR)/coverage
	open $(BUILD_DIR)/coverage/index.html
.PHONY: test

s21_matrix_oop.a:
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
	make -C $(BUILD_DIR) s21_matrix_oop
.PHONY: s21_matrix_oop.a
