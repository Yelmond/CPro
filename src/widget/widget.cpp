#include "widget.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <concepts>
#include <fmt/format.h>

template< typename T >
concept WidgetConcept = requires( T a ) {
	{ a.getId() } -> std::convertible_to< int >;
};

template< typename T >
class Widget {
public:
	constinit static int objectCount;

	explicit( std::is_integral_v< T > ) Widget( T id ) : mId( id ) {
		std::cout << "Widget " << mId << " constructed\n";
		++objectCount;
	}

	~Widget() {
		std::cout << "Widget " << mId << " destroyed\n";
		--objectCount;
	}

	Widget( const Widget & ) = delete;
	Widget & operator=( const Widget & ) = delete;

	Widget( Widget && other) noexcept : mId( other.mId ) {
		other.mId = 0;
		std::cout << "Widget " << mId << " moved\n";
	}

	Widget & operator=( Widget && other ) noexcept {
		if ( this != &other ) {
			mId = other.mId;
			other.mId = 0;
			std::cout << "Widget " << mId << " move-assigned\n";
		}
		return *this;
	}

	constexpr T getId() const { return mId; }

private:
	T mId;
};

template< typename T >
constinit int Widget< T >::objectCount = 0;

consteval int square( int num ) {
	return num * num;
}

void widgetise() {
	constexpr int squaredValue = square( 5 ); // Compile-time computation
	std::cout << "Squared Value: " << squaredValue << std::endl;

	std::vector< std::unique_ptr< Widget< int > > > widgets;

	// Creating Widgets
	for ( int i = 1; i <= 5; ++i ) {
		widgets.emplace_back( std::make_unique< Widget< int > >( i ) );
	}

	// Lambda to check Widget ID
	auto isOdd = []( const std::unique_ptr< Widget< int > > & w ) -> bool {
		return w->getId() % 2 != 0;
	};

	widgets.erase(
		std::remove_if( widgets.begin(), widgets.end(), isOdd ),
		widgets.end() );

	std::cout << "Remaining Widgets:\n";
	for ( const auto & w : widgets ) {
		if constexpr ( WidgetConcept< decltype( *w ) >) {
			std::cout << "Widget " << w->getId() << '\n';
		} else {
			std::cout << "Non-conforming Widget\n";
		}
	}

	std::cout << "Total Widget objects: " << Widget< int >::objectCount << std::endl;
}
