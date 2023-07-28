#include <vector>
#include <string_view>
#include <string>

#ifdef WIN32
	#ifndef textlib_EXPORT
		#define textlib_EXPORTS __declspec( dllexport )
	#else
		#define textlib_EXPORTS __declspec( dllimport )
	#endif
#else
	#define textlib_EXPORTS __attribute__( ( visibility( "default" ) ) )
#endif

struct TextSegment {
    const std::string text; // TODO change copy to a reference to the original string
    size_t start;
    size_t end;
    uint8_t level;

    // Constructor
    TextSegment(const std::string& str, size_t start, size_t end, uint8_t level)
            : text(str), start(start), end(end), level(level) {}

    std::string_view get_segment_text() const {
        return std::string_view(text.c_str() + start, end - start);
    }
};


// TODO why not create a textlib class and make textSegments a member variable instead of a global variable?
extern textlib_EXPORTS std::vector<TextSegment> textSegments;
textlib_EXPORTS void processText( const char* str );
