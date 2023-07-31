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

    TextLib textLib;

    textLib.bidi(str, strlen(str));

    for (auto& segment : textLib.textSegments) {
        std::cout << "Segment: " << segment.get_segment_text() << std::endl;
    }

    for (auto& segment : textLib.textSegments) {
        textLib.shape("../../../resources/Roboto-Bold.ttf", segment.get_segment_text().data(), 12);
    }

    textLib.segmenter();
    textLib.layout(100);

	return 0;
}
