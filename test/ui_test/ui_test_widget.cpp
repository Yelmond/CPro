#include <gtest/gtest.h>
#include "../../src/ui/ui_widget.h"

using W = UI::Widget;

TEST( Widget, AddChild ) {
	W w( 1 );
	EXPECT_EQ( w.getField(), 1 );

	{
		W child( 24890324 );
		child.addChild( 43574 );

		w.addChild( std::move( child ) );

		EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
		EXPECT_EQ( child.getField(), 0 );
		EXPECT_EQ( child.getChildCount(), 0 );
	}

	EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
}

TEST( Widget, MoveChild ) {
	W parent1( 1 );
	W parent2( 2 );

	parent1.addChild( 3 );
	parent2.addChild( 4 );

	auto & child3 = parent1.getChild( 0 );

	parent2.addChild( std::move( child3 ) );

	EXPECT_EQ( parent1.getChildCount(), 0 );
	EXPECT_EQ( parent2.getChildCount(), 2 );
}

// Main function
int main( int argc, char **argv ) {
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
