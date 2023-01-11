#include <gtest/gtest.h>
#include <iostream>
#include "my_allocator.cpp"


class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, test_init)
{
    //initialization
    std::cout << "\nInitialization test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    ASSERT_EQ(alloc.compareMemAndOffset(), 1);
    std::cout << "Initialization test: ok" << std::endl;
}

TEST(TestUtils, test_alloc_ok)
{
    //correct allocation
    std::cout << "\nCorrect allocation test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    alloc.alloc(5);
    ASSERT_EQ(alloc.compareMemAndOffset(), 0);
    std::cout << "Correct allocation test: ok" << std::endl;

}

TEST(TestUtils, test_alloc_error)
{
    //allocation error
    std::cout << "\nAllocation error test" << std::endl;
    Allocator alloc;
    alloc.makeAllocator(10);
    ASSERT_EQ(alloc.alloc(11), nullptr);
    std::cout << "Allocation error test: ok" << std::endl;
   
}

TEST(TestUtils, test_reset)
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

TEST(TestUtils, test_double_call)
{
    Allocator alloc;
    alloc.makeAllocator(50);
    int mem = alloc.getMemsize();
    ASSERT_EQ(mem, 50);
    alloc.makeAllocator(50);
    mem = alloc.getMemsize();
    ASSERT_EQ(mem, 50);
    ASSERT_EQ(alloc.compareMemAndOffset(), 1);
}

TEST(TestUtils, boundary_values)
{
    Allocator alloc;
    alloc.makeAllocator(1);
    alloc.alloc(1);
    //alloc.alloc(1);
    ASSERT_EQ(alloc.alloc(1), nullptr);

    alloc.makeAllocator(50);
    //alloc.alloc(20);
    ASSERT_NE(alloc.alloc(20), nullptr);
    ASSERT_EQ(alloc.compareMemAndOffset(), 0);
    //alloc.alloc(30);
    ASSERT_NE(alloc.alloc(30), nullptr);
    ASSERT_EQ(alloc.compareMemAndOffset(), 0);
    //alloc.alloc(1);
    ASSERT_EQ(alloc.alloc(1), nullptr);

    alloc.reset();
    ASSERT_EQ(alloc.compareMemAndOffset(), 1);

    //alloc.alloc(50);
    ASSERT_NE(alloc.alloc(50), nullptr);
    ASSERT_EQ(alloc.compareMemAndOffset(), 0);


}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}