#include <cstddef>
#include <algorithm>
#include <memory>
#include "lib/shvector.h"

#include "gtest/gtest.h"

class ShittyVector : public testing::Test
{
};

TEST(ShittyVector, CanBeCreated)
{
    shitty::shvector<int> vector;
}

TEST(ShittyVector, AnEmptyVectorHasSizeZero)
{
    shitty::shvector<int> vector;
    ASSERT_EQ(vector.size(), 0);
}

TEST(ShittyVector, CanPushIntoAVectorAndItGrows)
{
    shitty::shvector<int> vector;
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 1);
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 2);
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 3);
}

TEST(ShittyVector, CanAccessAnElement)
{
    shitty::shvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    ASSERT_EQ(vector[1], 2);
}

TEST(ShittyVector, SimpleIteratorTest)
{
    shitty::shvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    ASSERT_EQ(*std::find(vector.begin(), vector.end(), 2), 2);
}