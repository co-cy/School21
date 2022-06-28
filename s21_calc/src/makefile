CC := gcc
CFALGS = -Wall -Wextra -fanalyzer -g -fsanitize=address

OTHER_FLAGS := -g

ALL_C_FILES := $(shell find . -name '*.c')
TARGET = s21_calc

.PHONY: all
all: $(TARGET)

$(TARGET): $(ALL_C_FILES) makefile
	$(CC) $(CFALGS) $^ -o $@

.PHONY: test
test: CLAGS += $(OTHER_FLAGS)
test: $(TARGET)


.PHONY: lint
lint: $(ALL_C_FILES)
	cp ../materials/linters/CPPLINT.cfg .
	-python3 ../materials/linters/cpplint.py --extensions=c $^
	rm CPPLINT.cfg

	cppcheck --enable=all --suppress=missingIncludeSystem $^

.PHONY: clean
clean:
	rm -rf $(TARGET)