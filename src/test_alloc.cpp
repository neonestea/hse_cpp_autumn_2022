#include <gtest/gtest.h>
#include <iostream>
#include "my_allocator.cpp"

class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestAlloc, test_init)
{
    //initialization
    std::cout << "\nInitialization test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    ASSERT_EQ(alloc.compareMemAndOffset(), 1);
    std::cout << "Initialization test: ok" << std::endl;
}

TEST(TestAlloc, test_alloc_ok)
{
    //correct allocation
    std::cout << "\nCorrect allocation test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    ASSERT_EQ(alloc.compareMemAndOffset(), 0);
    std::cout << "Correct allocation test: ok" << std::endl;

}

TEST(TestAlloc, test_alloc_error)
{
    //allocation error
    std::cout << "\nAllocation error test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    ASSERT_EQ(alloc.alloc(11), nullptr);
    std::cout << "Allocation error test: ok" << std::endl;
   
}

TEST(TestAlloc, test_reset)
{
    //reset
    std::cout << "\nReset test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    alloc.alloc(5);
    alloc.reset();
    ASSERT_EQ(alloc.compareMemAndOffset(), 1);
    std::cout << "Reset test: ok" << std::endl;

}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
