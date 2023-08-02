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

struct Glyph {
	uint32_t codepoint;
    int x_origin;
	int x_advance;
	int y_advance;
	int x_offset;
	int y_offset;
};

class textlib_EXPORTS TextLib {
public:
    TextLib();
    ~TextLib();

    void bidi(const char* src, size_t len);
    void shape(const char* font_path, int font_size);
    void shape_segment(const char* font_path, const uint16_t* text, int font_size);
    void segmenter();
    void layout(int width);
    void layoutLine(int start, int end);

    std::vector<Glyph> glyphs;
};
