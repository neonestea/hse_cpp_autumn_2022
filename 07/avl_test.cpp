#include <gtest/gtest.h>
#include <iostream>
#include "avl.cpp"
#include <string>



class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, adding_elements) //Правильный случай
{
    avl<int, std::string> tree;
    bool checkEmpty = tree.empty(); //now tree is empty
    ASSERT_EQ(checkEmpty, 1);
    tree.insert(19 , "nineteen"); //inserted element
    ASSERT_EQ(tree.size(), 1); //size
    tree.insert(36, "thirty six");
    ASSERT_EQ(tree.size(), 2);
    tree.insert(25, "25");
    ASSERT_EQ(tree.size(), 3);
    tree.insert(14, "fourteen");
    ASSERT_EQ(tree.size(), 4);
    tree.insert(12, "12");
    ASSERT_EQ(tree.size(), 5);
    tree.insert(23, "23");
    ASSERT_EQ(tree.size(), 6);
    bool checkNotEmpty = tree.empty(); //empty
    ASSERT_EQ(checkNotEmpty, 0);
    //tree.print2D(tree.root, 5);
    //tree.print(tree.root);
    bool checkExists = tree.contains(36);
    bool checkNotExists = tree.contains(37);
    ASSERT_EQ(checkExists, 1); //contains
    ASSERT_EQ(checkNotExists, 0); //does not contain
    std::string el = tree[1];
    std::cout << "It was "  << tree[1] << std::endl;
    tree[1] = "NEW";
    std::cout << "Now it is " << tree[1]<< std::endl; //ADD CHECKING

    int num = 36;
    tree.erase(num); //deleted element
    ASSERT_EQ(tree.size(), 5);

    auto begin_it = tree.begin();
    auto end_it = tree.end();
    std::string beg = *begin_it; //check iterators
    std::string end = *end_it;
    ASSERT_EQ(beg, "12");
    ASSERT_EQ(end, "25");

    auto rbegin_it = tree.rbegin();
    auto rend_it = tree.rend();
    std::string rbeg = *rbegin_it;
    std::string rend = *rend_it;
    ASSERT_EQ(rend, "12");
    ASSERT_EQ(rbeg, "25");
    
    //tree.print2D(tree.root, 5);
    //tree.print(tree.root);
    tree.clear();
    checkEmpty = tree.empty();
    ASSERT_EQ(checkEmpty, 1);
}

TEST(TestUtils, check_not_exists) //trying to access element that does not exist
{
    
    avl<int, std::string> tree;
    tree.insert(19 , "nineteen");
    tree.insert(36, "thirty six");
    tree.insert(25, "25");
    tree.insert(12, "12");
    tree.insert(23, "23");
    EXPECT_THROW({
        try
        {
            
            tree[100] = "NEW";
        }
        catch( const ElementNotExistst& e )
        {
            
            EXPECT_STREQ( "Element not exist", e.what() );
            throw;
        }
    }, ElementNotExistst );

    
    
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}