build:
	g++ -g -std=c++11 -o test tests.cpp

test: build
	valgrind --leak-check=full ./test