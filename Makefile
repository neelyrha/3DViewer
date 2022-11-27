CC = gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
CCOV = -fprofile-arcs -ftest-coverage
SOURCE_FILES = *.c 3d_viewer.h
COVFLAGS = --coverage
LDFLAGS = -lgcov
TFLAGS = -lcheck
#ASAN = -g -fsanitize=address


all: clean install run	

install:
	@mkdir build
	cd build; cmake ..; cmake --build .

uninstall:
	rm -rf build

dvi:
	open html/index.html

dist: 
	@mkdir 3Dviewer_dist
	cp *.c 3Dviewer_dist
	cp *.h 3Dviewer_dist
	cp CMakeLists.txt.user 3Dviewer_dist
	cp *.txt 3Dviewer_dist
	cp *.cpp 3Dviewer_dist
	cp *.ui 3Dviewer_dist
	cp Makefile 3Dviewer_dist
	tar -czf 3Dviewer.tar.gz 3Dviewer_dist/
	rm -rf 3Dviewer_dist

run:
	open build/3d_viewer.app

test: 
	$(CC) $(CFLAGS) $(ASAN) $(CCOV) $(SOURCE_FILES) -o test $(TFLAGS)
	./test

gcov_report:
	$(CC) $(ASAN) $(GFLAGS) $(CCOV) $(SOURCE_FILES) $(TFLAGS) -o ./htmlreport.out
	./htmlreport.out
	lcov -t "htmlreport" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check:
	cppcheck --enable=all --force *.c 3d_viewer.h

leakscheck: test
	leaks --atExit -- ./test
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report *.dSYM *.gcov build *.gch 3Dviewer_dist 3Dviewer.tar.gz

rebuild: all

.PHONY : clean run install uninstall dvi test gcov_report