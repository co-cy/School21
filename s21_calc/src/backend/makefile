CC := gcc
CFLAGS := -shared -lm

ifdef DEV
CFLAGS += -Wall -Wextra -fanalyzer -g -fsanitize=address
endif

ALL_C_FILES := $(shell find . -name '*.c')
TARGET := backend.so

.PHONY: all
all: $(TARGET)

$(TARGET): $(ALL_C_FILES)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: lint
lint: $(ALL_C_FILES)
	cp ../materials/linters/CPPLINT.cfg .
	-python3 ../materials/linters/cpplint.py --extensions=c $^
	rm CPPLINT.cfg

	-cppcheck --enable=all --suppress=missingIncludeSystem $^

.PHONY: clean
clean:
	rm -rf $(TARGET)
