CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra -Wno-unused-parameter
TEST_LIB=-lgtest -lgtest_main -lpthread

all avl test_bin

avl avl.cpp
	$(CC) $(FLAGS) -c avl.cpp

test_bin avl.o avl_test.cpp
	$(CC) $(FLAGS) avl.o avl_test.cpp -o test_bin $(TEST_LIB)

test
	.test_bin

clean
	rm -f .o test_bin
