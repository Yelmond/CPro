#pragma once

#include <type_traits>
#include <concepts>

namespace UI {
	enum class PseudoStates : short {
		Active		= 1 << 0,
		Hover		= 1 << 1,
		Checked		= 1 << 2,
		Disabled	= 1 << 3,
		Focus		= 1 << 4,
		Root		= 1 << 5
	};

	enum class LanguageDirection : short {
		Inherit,
		LTR,
		RTL
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// Utility Methods
	
	template< typename T >
	concept EnumConcept = std::is_enum_v< T >;

	template< EnumConcept TEnum >
	inline auto operator|( TEnum a, TEnum b ) {
		return static_cast< TEnum >(
			std::underlying_type_t< TEnum >( a ) |
			std::underlying_type_t< TEnum >( b ) );
	}

	template< EnumConcept TEnum >
	inline auto operator&( TEnum a, TEnum b ) {
		return static_cast< TEnum >(
			std::underlying_type_t< TEnum >( a ) &
			std::underlying_type_t< TEnum >( b ) );
	}

	template< EnumConcept TEnum >
	inline bool hasFlag( TEnum a, TEnum b ) {
		return ( a & b ) == b;
	}

}
