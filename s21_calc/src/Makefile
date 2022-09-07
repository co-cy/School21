.PHONY: all
all: install


.PHONY: install
install:
	-mkdir build
	cmake CMakeLists.txt -S . -B ./build


.PHONY: uninstall
uninstall:
	-rm -rf build


.PHONY: clean
clean: install
	cd build && make clean && cd ..
	cd backend && make clean && cd ..


.PHONY: dvi
dvi:
	open ../materials/dvi.pdf


.PHONY: dist
dist: install
	cd build && make dist && cd ..


.PHONY: tests
tests:
	cd backend && make tests && cd ..


.PHONY: gcov_report
gcov_report:
	cd backend && make gcov_report && cd ..

lint:
	clang-format -i $(shell find . -name "*.c" -or -name "*.cpp")

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(shell find . -name "*.c" -or -name "*.cpp")

