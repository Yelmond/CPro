#include "textlib.h"
#include <iostream>

#include <ICU4XBidi.hpp>
#include <ICU4XDataProvider.hpp>

textlib_EXPORTS std::vector<TextSegment> textSegments;

void processText(const char* str) {
    ICU4XDataProvider dp = ICU4XDataProvider::create_test();
    auto bidi = ICU4XBidi::create(dp).ok().value();

    auto bidi_info = bidi.for_text(str, ICU4XBidi::level_ltr());
    auto n_para = bidi_info.paragraph_count();

    // Split the reordered paragraph into segments of same directionality
    for (int i = 0; i < n_para; ++i) {
        auto para = bidi_info.paragraph_at(i).value();
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

// Our simple Glyph struct which holds information for each glyph
/*struct Glyph {
	uint32_t codepoint;
	int x_advance;
	int y_advance;
	int x_offset;
	int y_offset;
};*/

// Function that loads and processes a TTF font
/*
std::vector<Glyph> processFont(const char* font_path, const char* text, int font_size) {
	// Initialize FreeType
	FT_Library ft_library;
	FT_Init_FreeType(&ft_library);

	// Load the font
	FT_Face ft_face;
	FT_New_Face(ft_library, font_path, 0, &ft_face);

	// Set the character size
	FT_Set_Char_Size(ft_face, font_size << 6, font_size << 6, 96, 96);

	// Initialize HarfBuzz and create a font
	hb_font_t* hb_font;
	hb_font = hb_ft_font_create(ft_face, NULL);

	// Create a buffer for HarfBuzz to use
	hb_buffer_t* hb_buffer;
	hb_buffer = hb_buffer_create();
	hb_buffer_add_utf8(hb_buffer, text, -1, 0, -1);

	// Set up the buffer for horizontal layout
	hb_buffer_guess_segment_properties(hb_buffer);

	// Shape the text
	hb_shape(hb_font, hb_buffer, NULL, 0);

	// Get glyph information and positions out of the buffer
	unsigned int glyph_count;
	hb_glyph_info_t* glyph_info   = hb_buffer_get_glyph_infos(hb_buffer, &glyph_count);
	hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, &glyph_count);

	// Create a vector to hold our glyphs
	std::vector<Glyph> glyphs;

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

	// Cleanup
	hb_buffer_destroy(hb_buffer);
	hb_font_destroy(hb_font);
	FT_Done_Face(ft_face);
	FT_Done_FreeType(ft_library);

	return glyphs;
}
*/
