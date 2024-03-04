#include <gtest/gtest.h>

/// @brief Class to setup environment for all the test ran in within this exe/main()
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

/// @brief Class to work with a set/suite of test which have similar setup  
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

/// @brief Macro for making a test within a Test Suite, for each test Suite's SetUp and TearDown will be ran
/// @param ExampleTestSuite - Suite name
/// @param example_test - Test name
TEST_F(ExampleTestSuite, example_test)
{
       EXPECT_EQ(2, 2);
};

/// @brief Macro for making a test
/// @param ExampleTestSuite - Suite name
/// @param example_test - Test name
TEST(ExampleTests, example_test1)
{
       EXPECT_EQ(2, 2);
};

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment( new TestEnvironment);
    return RUN_ALL_TESTS();
}
