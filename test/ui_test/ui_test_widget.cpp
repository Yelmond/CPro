#include <gtest/gtest.h>

// Mock function (replace this with your actual function from the app project)
int add( int a, int b ) {
	return a + b;
}

// Test case for the add function
TEST( AdditionTest, HandlesPositiveNumbers ) {
	EXPECT_EQ( add( 1, 2 ), 3 );
}

TEST( AdditionTest, HandlesNegativeNumbers ) {
	EXPECT_EQ( add( -1, -2 ), -3 );
}

TEST( AdditionTest, HandlesMixedNumbers ) {
	EXPECT_EQ( add( -1, 2 ), 1 );
}

// Main function
int main( int argc, char **argv ) {
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
