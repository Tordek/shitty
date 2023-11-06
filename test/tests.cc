#include <cstddef>
#include <algorithm>
#include <memory>
#include "lib/shvector.h"

#include "gtest/gtest.h"

class BasicTests : public testing::Test
{
};

TEST(BasicTests, CanBeCreated)
{
    shitty::shvector<int> vector;
}

TEST(BasicTests, AnEmptyVectorHasSizeZero)
{
    shitty::shvector<int> vector;
    ASSERT_EQ(vector.size(), 0);
}

TEST(BasicTests, CanPushIntoAVectorAndItGrows)
{
    shitty::shvector<int> vector;
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 1);
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 2);
    vector.push_back(1);
    ASSERT_EQ(vector.size(), 3);
}

TEST(BasicTests, CanAccessAnElement)
{
    shitty::shvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    ASSERT_EQ(vector[1], 2);
}