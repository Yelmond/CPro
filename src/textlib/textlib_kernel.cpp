#include "textlib.h"
#include <iostream>


// ICU4C
#include <unicode/utypes.h>
#include <unicode/ubidi.h>
#include <unicode/ustring.h>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include "unicode/unistr.h"

// HarfBuzz
#include <hb.h>
#include <hb-ft.h>

FT_Library ft_library;
FT_Face ft_face;

hb_buffer_t* hb_buffer;
hb_font_t* hb_font;

UChar* logicalStr; // TODO should we use char* ?
int32_t logicalStrLen;
std::vector<int32_t> breakpoints;

struct TextSegment {
    const UChar* text; // Logical string
    int32_t start;
    int32_t length;
    uint8_t level;
    int32_t paragraph;

    // Constructor
    TextSegment(const UChar* str, int32_t start, int32_t length, uint8_t level, int32_t paragraph)
            : text(str), start(start), length(length), level(level), paragraph(paragraph) {}

    // TODO Update
    const UChar* get_segment_text() const {
        return text + start;
    }
};
std::vector<TextSegment> textSegments;

TextLib::TextLib() {
    if (FT_Init_FreeType(&ft_library)) {
        std::cerr << "Could not initialize freetype library." << std::endl;
        return;
    }
    hb_buffer = hb_buffer_create();
}

TextLib::~TextLib() {
    hb_buffer_destroy(hb_buffer);
    hb_font_destroy(hb_font);
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_library);
}

void TextLib::bidi(const char* src, size_t len) {
    UErrorCode err = U_ZERO_ERROR;
    UBiDi* para = ubidi_openSized(len, 0, &err);
    if (U_FAILURE(err)) {
        // handle error
        ubidi_close(para);
        return;
    }

    // TODO ICU4C expect UTF-16, so we need to convert from UTF-8. We might want to store the logical string in UTF16 format.
    // TODO avoid reallocating every time
    logicalStr = new UChar[len+1];
    u_strFromUTF8(logicalStr, len+1, NULL, src, len, &err);
    logicalStrLen = u_strlen(logicalStr);
    if (U_FAILURE(err)) {
        delete[] logicalStr;
        ubidi_close(para);
        return;
    }

    int32_t start = 0, p = 0;
    for (int32_t i = 0; i <= logicalStrLen; ++i) {
        // TODO might need to use ICU LineBreakIterator instead (eg. \n\r, \n\n, CJK...)
        if (i == logicalStrLen || logicalStr[i] == '\n') {
            // See example: https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/ubidi_8h.html#aec250446cb8f9327eee5f219eaf65c25
            // TODO Add automatic detection of paragraph direction
            ubidi_setPara(para, logicalStr + start, i - start, UBIDI_DEFAULT_LTR, NULL, &err);
            if (U_FAILURE(err)) {
                delete[] logicalStr;
                ubidi_close(para);
                return;
            }

            // Get the visual order
            int32_t count = ubidi_countRuns(para, &err);
            // print paragraph number and number of runs
            printf("Paragraph %d: %d run%s\n", p, count, count==1?"":"s");
            if (U_FAILURE(err)) {
                delete[] logicalStr;
                ubidi_close(para);
                throw std::runtime_error("Failed to count runs");
            }

            for (int32_t j = 0; j < count; ++j) {
                int32_t logicalStart, length;
                UBiDiDirection dir = ubidi_getVisualRun(para, j, &logicalStart, &length);

                uint8_t level = dir == UBIDI_LTR ? 0 : 1;
                textSegments.emplace_back(logicalStr, logicalStart + start, length, level, p);
            }
            start = i + 1;
            p++;
        }
    }

/*
    // Convert UChar to UTF-8
    char utf8String[4*len]; // Assumes max 4 bytes per UTF-16 code unit
    int32_t utf8Length;
    u_strToUTF8(utf8String, 4*len, &utf8Length, logicalStr, len, &err);

    std::cout << "\nVisual String:\n";
    std::cout.write(utf8String, utf8Length);
    std::cout << "\n";


    //print logical and visual strings
    std::cout << "Logical: " << src << std::endl;
*/

    ubidi_close(para);
}

void TextLib::shape(const char* font_path, int font_size) {
    for (auto& segment : textSegments) {
        TextLib::shape_segment(font_path, reinterpret_cast<const uint16_t*>(segment.get_segment_text()), font_size);
    }

    // print each segment start and length
    for (auto& segment : textSegments) {
        std::cout << "start: " << segment.start << ", length: " << segment.length << std::endl;
    }

/*
    for (auto& segment : textSegments) {
        auto s = segment.get_segment_text(); // UChar*
        icu::UnicodeString unicodeString(s);
        std::string utf8String;
        unicodeString.toUTF8String(utf8String);
        std::cout << utf8String;
    }
*/
}

void TextLib::shape_segment(const char* font_path, const uint16_t* text, int font_size) {
    if (FT_Init_FreeType(&ft_library)) {
        std::cerr << "Could not initialize freetype library." << std::endl;
        return;
    }

    if (ft_face == nullptr){
        if (FT_New_Face(ft_library, font_path, 0, &ft_face)) {
            std::cerr << "Could not open font." << std::endl;
            return;
        }

        FT_Set_Char_Size(ft_face, font_size << 6, font_size << 6, 96, 96);
    }

    if (hb_font == nullptr)
        hb_font = hb_ft_font_create(ft_face, NULL);

    hb_buffer_clear_contents(hb_buffer);

    hb_buffer_add_utf16(hb_buffer, text, -1, 0, -1);

    // TODO set script, language, direction, and font features
    hb_buffer_guess_segment_properties(hb_buffer);
/*
    hb_buffer_set_direction(hb_buffer, direction);
    hb_buffer_set_script(hb_buffer, script);
    hb_buffer_set_language(hb_buffer, hb_language_from_string(language, -1));
*/


    hb_shape(hb_font, hb_buffer, NULL, 0);

    // Get glyph information and positions out of the buffer
    unsigned int glyph_count;
    hb_glyph_info_t* glyph_info   = hb_buffer_get_glyph_infos(hb_buffer, &glyph_count);
    hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, &glyph_count);

    for (unsigned int i = 0; i < glyph_count; ++i) {
        // TODO is glyph_pos.x_advance total offset from origin ?
        // If so the segmenter could be optimize to
        Glyph glyph;
        glyph.codepoint = glyph_info[i].codepoint;
        glyph.x_advance = glyph_pos[i].x_advance / 64;
        glyph.y_advance = glyph_pos[i].y_advance / 64;
        glyph.x_offset  = glyph_pos[i].x_offset / 64;
        glyph.y_offset  = glyph_pos[i].y_offset / 64;
        glyphs.push_back(glyph);
    }
}

void TextLib::segmenter() {
    breakpoints.clear();

/*
    ICU4XDataProvider dp = ICU4XDataProvider::create_test(); //TODO should we extract to a class member ?
    const auto segmenter_auto =
            ICU4XLineSegmenter::create_auto(dp).ok().value();

    auto iterator = segmenter_auto.segment_utf8(visualString);
    while (true) {
        int32_t breakpoint = iterator.next();
        if (breakpoint == -1) {
            break;
        }
        breakpoints.push_back(breakpoint);
    }
*/
}

void TextLib::layout(int width) {
/*
    int x_Advance = 0;
    int line_start = 0;
    auto last_breakpoint = breakpoints.begin();

    for (size_t i = 0; i < glyphs.size(); ++i) {
        Glyph& glyph = glyphs[i];

        if (x_Advance + glyph.x_advance > width) {
            // TODO this, we should not have to iterate over the whole vector
            auto it = std::upper_bound(last_breakpoint, breakpoints.end(), glyph.codepoint);
            if (it != breakpoints.begin()){
                --it;
                last_breakpoint = it;

                while (glyphs[i].codepoint > *last_breakpoint) {
                    i--;
                }
                layoutLine(line_start, i);
                line_start = i + 1;
                x_Advance = 0;
            }
            else {
                // TODO, need to implement word iterator
                std::cerr << "No breakpoint found before the current cluster" << std::endl;
            }
        }
    }
*/
}

void TextLib::layoutLine(int start, int end) {
    // Implement TextAlignement / x_origin / y_origin

    // Left Align
    int x_origin = 0;
    for (int i = start; i <= end; ++i) {
        Glyph& glyph = glyphs[i];
        glyph.x_origin = x_origin;

        if(i < end)
            x_origin += glyph.x_advance;
    }
}
