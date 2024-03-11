#include <gtest/gtest.h>
#include "../../src/ui/ui_widget.h"
#include "../../src/ui/ui_panel.h"

using W = UI::Widget;
using P = UI::Panel;

TEST( Widget, AddChild ) {
	P p;

	auto & w = p.createChild( 1 );
	EXPECT_EQ( w.getField(), 1 );

	{
		auto & child = p.createChild( 24890324 );
		child.createChild( 43574 );

		w.addChild( std::move( child ) );

		EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
		EXPECT_EQ( child.getField(), 0 );
		EXPECT_EQ( child.getChildCount(), 0 );
	}

	EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
}

TEST( Widget, MoveChild ) {
	P p;

	auto & parent1 = p.createChild( 1 );
	auto & parent2 = p.createChild( 2 );

	parent1.createChild( 3 );
	parent2.createChild( 4 );

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
