```cpp
	// A.m
	export module A;
	export import A.B;
	export import A.C;
	export import <Old.h>;

	// A.B.m
	export module A.B;
	export import :part1;
	export import :part2;

	// A.B.part1.m
	export module A.B:part1;
	export int do1();

	// A.B.part1.cpp
	module A.B:part1;
	int do1() { return 42; }

	// A.B.part2.m
	export module A.B:part2;
	import :part1;
	export int do2() { return do1(); }

	// A.C.m
	module;
	#include <sys/stat.h>
	export module A.C;
	namespace Sys {
		export stat stat_directory( const char * );
		export using ::stat;
		export using ::chmod;
	}

	// main.cpp
	import <iostream>;
	import A;
	int main() {
		std::cout << do2();
	}
```
