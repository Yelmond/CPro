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
    const std::string* text;
    size_t start;
    size_t end;
    uint8_t level;

    // Constructor
    TextSegment(const std::string* str, size_t start, size_t end, uint8_t level)
            : text(str), start(start), end(end), level(level) {}

    std::string_view get_segment_text() const {
        return std::string_view(text->c_str() + start, end - start);
    }
};


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

    void bidi(const char* logicalString, size_t len);
    void shape(const char* font_path, const char* text, int font_size);
    void segmenter();
    void layout(int width);
    void layoutLine(int start, int end);

    std::vector<TextSegment> textSegments;
    std::vector<Glyph> glyphs;

private:
    std::string visualString; // TODO should we use char* ?
    std::vector<int32_t> breakpoints;
};
