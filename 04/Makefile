CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra -Wno-unused-parameter
TEST_LIB=-lgtest -lgtest_main -lpthread

all: bigint test_bin

bigint: bigint.cpp
	$(CC) $(FLAGS) -c bigint.cpp

test_bin: bigint.o test_bigint.cpp
	$(CC) $(FLAGS) bigint.o test_bigint.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
