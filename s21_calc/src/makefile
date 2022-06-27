ALL_C_FILES := $(shell find . -name '*.c')

lint: $(ALL_C_FILES)
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $^
	rm CPPLINT.cfg

	cppcheck --enable=all --suppress=missingIncludeSystem $^