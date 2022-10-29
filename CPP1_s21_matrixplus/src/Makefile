BUILD_DIR="build"


.PHONY: all
all:
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=DEBUG
	make -C $(BUILD_DIR) $@

.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test
test:
	echo "Not implemented"

#	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=CTEST
#	make -C $(BUILD_DIR) tests

.PHONY: s21_matrix_oop.a
s21_matrix_oop.a:
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE
	make -C $(BUILD_DIR) s21_matrix_oop
