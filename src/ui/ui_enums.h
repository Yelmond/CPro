#pragma once
#include <type_traits>
#include <concepts>
#include <stdexcept>
#include <expected>

namespace UI {
	enum class PseudoStates : short {
		Active		= 1 << 0,
		Hover		= 1 << 1,
		Checked		= 1 << 2,
		Disabled	= 1 << 3,
		Focus		= 1 << 4,
		Root		= 1 << 5
	};

	enum class LanguageDirection
	{
		Inherit,
		LTR,
		RTL
	};

	enum class LanguageDirection2
	{
		Inherit,
		LTR,
		RTL
	};

	inline auto toTextCore(LanguageDirection dir)
	{
		switch (dir)
		{
		case LanguageDirection::Inherit:
		case LanguageDirection::LTR:
			return LanguageDirection2::LTR;
		case LanguageDirection::RTL:
			return LanguageDirection2::RTL;
		default:
			//return std::unexpected(std::out_of_range("impossible to convert value"));
			throw new std::out_of_range("impossible to convert value");
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Utility Methods
	
	template< typename T >
	concept EnumConcept = std::is_enum_v<T>;

	template< EnumConcept TEnum >
	inline auto operator|( TEnum a, TEnum b ) {
		return static_cast< TEnum >(
			std::underlying_type_t<TEnum>( a ) |
			std::underlying_type_t<TEnum>( b ) );
	}

	template< EnumConcept TEnum >
	inline auto operator&( TEnum a, TEnum b ) {
		return static_cast< TEnum >(
			std::underlying_type_t<TEnum>( a ) &
			std::underlying_type_t<TEnum>( b ) );
	}

	template< EnumConcept TEnum >
	inline bool hasFlag( TEnum a, TEnum b ) {
		return ( a & b ) == b;
	}


}
