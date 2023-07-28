//import modlib;

#include <textlib.h>
#include <iostream>

int main() {
/*
	ModLibPrinter mlp;
	mlp.printStuff();
*/
    const char* str =
            "א"
            "ב"
            "ג"
            "a"
            "b"
            "c"
            "\n"
            "a"
            "b"
            "c"
            "א"
            "ב"
            "ג";

    std::cout << "Input: " << str << std::endl;

	processText( str );

    for (auto& segment : textSegments) {
        std::cout << "Segment: " << segment.get_segment_text() << std::endl;
    }

	return 0;
}
