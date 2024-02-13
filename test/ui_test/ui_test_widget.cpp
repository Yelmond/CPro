#include <gtest/gtest.h>
#include "../../src/ui/ui_widget.h"

TEST( WidgetTest, Widget ) {
	UI::Widget w( 1 );
	EXPECT_EQ( w.getField(), 1 );

	{
		UI::Widget child( 24890324 );
		w.addChild( child );

		EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
	}

	EXPECT_EQ( w.getChild( 0 ).getField(), 24890324 );
}

// Main function
int main( int argc, char **argv ) {
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
