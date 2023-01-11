CC=g++
FLAGS=-std=c++20 
TEST_LIB=-lgtest -lgtest_main -lpthread

all: serializer test_bin

serializer: serializer.cpp
	$(CC) $(FLAGS) -c serializer.cpp

test_bin: serializer.o test_serializer.cpp
	$(CC) $(FLAGS) serializer.o test_serializer.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
