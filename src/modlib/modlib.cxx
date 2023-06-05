// Global module fragment where #includes can happen
module;
#include <fmt/core.h>

// first thing after the Global module fragment must be a module command
export module modlib;

export class ModLibPrinter {
	public:
		ModLibPrinter();
		~ModLibPrinter();
		void printStuff() const;
};

ModLibPrinter::ModLibPrinter() = default;

ModLibPrinter::~ModLibPrinter() = default;

void ModLibPrinter::printStuff() const {
	fmt::print( "Hello, world!\n" );
}
