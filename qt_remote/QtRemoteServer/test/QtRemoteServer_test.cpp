#include <gtest/gtest.h>

class TestEnvironment : public ::testing::Environment
{
public:
    virtual void SetUp() override
    {
    };

    virtual void TearDown () override
    {
    };
};

class ExampleTestSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

public:
};


TEST_F(ExampleTestSuite, example_test)
{
       EXPECT_EQ(2, 2);
};

TEST(ExampleTests, example_test1)
{
       EXPECT_EQ(2, 2);
};
