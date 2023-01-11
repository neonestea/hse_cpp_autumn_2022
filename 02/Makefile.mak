CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra -Wno-unused-parameter
TEST_LIB=-lgtest -lgtest_main -lpthread

all: parser test_bin

parser: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

test_bin: parser.o test_parser.cpp
	$(CC) $(FLAGS) parser.o test_parser.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
