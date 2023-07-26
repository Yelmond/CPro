#include "textlib.h"
#include <iostream>

#include <unicode/ubidi.h>
#include <unicode/brkiter.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>
#include <hb-ft.h>

#include <vector>

// Our simple Glyph struct which holds information for each glyph
struct Glyph {
	uint32_t codepoint;
	int x_advance;
	int y_advance;
	int x_offset;
	int y_offset;
};

// Function that loads and processes a TTF font
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

void processText( const char * str ) {
	icu::UnicodeString text = icu::UnicodeString::fromUTF8( str );

	// Create a BreakIterator for line breaks
	icu::BreakIterator* lineBreakIterator = icu::BreakIterator::createLineInstance(icu::Locale::getDefault());

	lineBreakIterator->setText(text);

	int32_t start = lineBreakIterator->first();
	for (int32_t end = lineBreakIterator->next(); end != icu::BreakIterator::DONE; start = end, end = lineBreakIterator->next()) {
		icu::UnicodeString line = text.tempSubStringBetween(start, end);

		// Now we perform bidi analysis on each line separately
		UErrorCode errorCode = U_ZERO_ERROR;
		icu::BiDi bidi(line.length(), 0, line.getBuffer(), line.length(), NULL, UBIDI_DEFAULT_LTR, &errorCode);

		// Now we can shape each line with HarfBuzz and output the glyphs
		std::string lineStr;
		line.toUTF8String(lineStr);
		std::vector<Glyph> glyphs = processFont(font_path, lineStr.c_str(), font_size);
		for (const auto& glyph : glyphs) {
			std::cout << "Glyph codepoint: " << glyph.codepoint
						<< ", X advance: " << glyph.x_advance
						<< ", Y advance: " << glyph.y_advance
						<< ", X offset: " << glyph.x_offset
						<< ", Y offset: " << glyph.y_offset << std::endl;
		}
	}

	delete lineBreakIterator;
}
