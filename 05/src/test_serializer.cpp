#include <gtest/gtest.h>
#include <iostream>
#include "serializer.cpp"
#include <string>


class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, check_for_equal)
{
    DataIBI x { 1, true, 2 };
    DataIBI y { 0, false, 0 };
    //DataBBI z { true, false, 3 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    //assert(err == Error::NoError);

    //assert(x.a == y.a);
    //assert(x.b == y.b);
    //assert(x.c == y.c);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}

TEST(TestUtils, check_for_not_equal)
{
    DataIBI x { 1, true, 2 };
    //DataIBI y { 0, false, 0 };
    DataBBI z { true, false, 3 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(z);
    
    //assert(err == Error::NoError);

    //assert(x.a == y.a);
    //assert(x.b == y.b);
    //assert(x.c == y.c);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}