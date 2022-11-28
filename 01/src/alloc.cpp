#include <iostream>

class Allocator
{
    private:
        static char[] buff = nullptr;
        static char *offset = buff;
        static int buff_size;
    public:

        void makeAllocator(size_t maxSize)
        {
            buff_size = maxSize;

            std::cout << buff_size << "b will be allocated." << std::endl;
            if(std::size(buff) != 0) {
                delete buff;
            }
            buff = new char[maxSize];
            offset = buff;
            
            std::cout << "offset: " << (void*)offset << std::endl;
            std::cout << "mem: " << buff << std::endl;
        }

        char* getBuffAddress()
        {
            return buff;
        }

        char* getOffsetAddress()
        {
            return (void*)offset;
        }



        char* alloc(size_t size)
        {
            if ( buff + buff_size - offset >= size)
            {
                offset += size;
                std::cout << "offset: " << offset << std::endl;

                return offset - size;
            }
            else
            {
                std::cout << "Cannot allocate!" << std::endl;
                return nullptr;
            }
        }

        void reset()
        {
            //std::cout << "Before reset: mem: " << &mem << ", offset: " << &offset << std::endl;
            offset = buff;
            //std::cout << "After reset: mem: " << &mem << ", offset: " << &offset << std::endl;

        }

        // Это деструктор!
        ~Allocator()
        {
            delete[] buff;
            std::cout << "Deleted Allocator" << std::endl;

        }
};

int main (int argc, char *argv[])
{
    std::cout << "char size: " << sizeof(char) << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    return 0;
}