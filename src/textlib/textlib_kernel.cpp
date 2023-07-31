#include "textlib.h"
#include <iostream>

#include <ICU4XBidi.hpp>
#include <ICU4XDataProvider.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>
#include <hb-ft.h>

FT_Library ft_library;
FT_Face ft_face;

hb_buffer_t* hb_buffer;
hb_font_t* hb_font;

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

void TextLib::bidi(const char* str) {
    ICU4XDataProvider dp = ICU4XDataProvider::create_test();
    auto bidi = ICU4XBidi::create(dp).ok().value();

    auto bidi_info = bidi.for_text(str, ICU4XBidi::level_ltr());
    auto n_para = bidi_info.paragraph_count();

    // Split the reordered paragraph into segments of same directionality
    for (int i = 0; i < n_para; ++i) {
        auto para = bidi_info.paragraph_at(i).value();
        // TODO investigate reorder_line_to_writeable
        std::string reordered = para.reorder_line(para.range_start(), para.range_end()).ok().value();

        // Split the reordered paragraph into segments of same directionality
        size_t segment_start = 0;
        uint8_t previous_level = para.level_at(0);
        for (size_t j = 1; j < reordered.size(); ++j) {
            uint8_t current_level = para.level_at(j);
            if (ICU4XBidi::level_is_rtl(previous_level) != ICU4XBidi::level_is_rtl(current_level)) {
                textSegments.emplace_back(reordered, segment_start, j, previous_level);
                segment_start = j;
            }
            previous_level = current_level;
        }
        textSegments.emplace_back(reordered, segment_start, reordered.size(), previous_level);
    }
}

void TextLib::shape(const char* font_path, const char* text, int font_size) {
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

    hb_buffer_add_utf8(hb_buffer, text, -1, 0, -1);

    // TODO set script, language, direction, and font features
    hb_buffer_guess_segment_properties(hb_buffer);

    hb_shape(hb_font, hb_buffer, NULL, 0);

    // Get glyph information and positions out of the buffer
    unsigned int glyph_count;
    hb_glyph_info_t* glyph_info   = hb_buffer_get_glyph_infos(hb_buffer, &glyph_count);
    hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, &glyph_count);

    // Fill our glyphs vector with info from HarfBuzz
    for (unsigned int i = 0; i < glyph_count; ++i) {
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
    for(auto& segment : textSegments) {
    }
}
