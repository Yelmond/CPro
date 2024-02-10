#include <gtest/gtest.h>
#include "../../src/ui/ui_enums.h"

TEST( EnumTests, HasFlag ) {
	EXPECT_TRUE( UI::hasFlag(
		UI::PseudoStates::Active, UI::PseudoStates::Active ) );

	EXPECT_EQ( UI::toTextCore( UI::LanguageDirection::RTL ), UI::LanguageDirection2::RTL );

	//const auto value = static_cast< UI::LanguageDirection >( 24 );
	//EXPECT_THROW( UI::toTextCore( value ), std::out_of_range );
}
