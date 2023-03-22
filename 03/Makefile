CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra -Wno-unused-parameter
TEST_LIB=-lgtest -lgtest_main -lpthread

all: matrix test_bin

matrix: matrix.cpp
	$(CC) $(FLAGS) -c matrix.cpp

test_bin: matrix.o test_matrix.cpp
	$(CC) $(FLAGS) matrix.o test_matrix.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
