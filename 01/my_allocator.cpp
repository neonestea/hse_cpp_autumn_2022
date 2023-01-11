#include <iostream>

class Allocator
{
    private:
        char* mem = nullptr;
        char* offset = mem;
        size_t max;
    public:

        void makeAllocator(size_t maxSize)
        {
            std::cout << "\nMAKE ALLOCATOR" << std::endl;

            max = maxSize;

            std::cout << max << "b will be allocated." << std::endl;
            if(mem != nullptr) {
                delete[] mem;
            }
            mem = new char[maxSize];
            offset = mem;
            std::cout << "offset: " << (void*)offset << std::endl;
            std::cout << "mem: " << (void*)mem << std::endl;
            std::cout << "memsize: " << max << std::endl;

        }

        bool compareMemAndOffset()
        {
            return mem == offset;
        }

        int getMemsize()
        {
            return max;
        }


        char* alloc(size_t size)
        {
            std::cout << "\nALLOC" << std::endl;
            std::cout << "Before: mem: " << (void*)mem << std::endl;
            std::cout << "Before: offset: " << (void*)offset << std::endl;
            std::cout << "Elements: " << max << std::endl;
            std::cout << "Elements: " << max << std::endl;
            std::cout << "Before: mem + max = " << (void*)(mem + max) << std::endl;
            std::cout << "Before: offset + size = " << (void*)(offset + size) << std::endl;

            if (mem + max >= offset + size)
            {
                offset += size;
                std::cout << "After: mem: " << (void*)mem << std::endl;
                std::cout << "After: offset: " << (void*)offset << std::endl;
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
            std::cout << "\nRESET" << std::endl;
            std::cout << "Before reset: mem: " << (void*)mem << ", offset: " << (void*)offset << std::endl;
            offset = mem;
            std::cout << "After reset: mem: " << (void*)mem << ", offset: " << (void*)offset << std::endl;

        }

        // Это деструктор!
        ~Allocator()
        {
            delete[] mem;
            std::cout << "\nDeleted Allocator" << std::endl;

        }
};

/*int main (int argc, char** argv)
{
    std::cout << "char size: " << sizeof(char) << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    std::cout << "Offset == mem: " << alloc.compareMemAndOffset() << std::endl;

    alloc.alloc(5);
    std::cout << "Offset == mem: " << alloc.compareMemAndOffset() << std::endl;

    alloc.reset();
    alloc.alloc(11);
    return 0;
}*/