CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra -Wno-unused-parameter
TEST_LIB=-lgtest -lgtest_main -lpthread

all: my_allocator test_bin

my_allocator: my_allocator.cpp
	$(CC) $(FLAGS) -c my_allocator.cpp

test_bin: my_allocator.o test_alloc.cpp
	$(CC) $(FLAGS) my_allocator.o test_alloc.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin
