#include <gtest/gtest.h>
#include "../../src/ui/ui_enums.h"

TEST( EnumTests, HasFlag ) {
	EXPECT_TRUE( UI::hasFlag(
		UI::PseudoStates::Active, UI::PseudoStates::Active ) );
}
