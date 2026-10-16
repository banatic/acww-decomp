/* The game's four bitmap fonts (fontA-fontD, the globals data_021c8230, data_021c828c,
 * data_021c82e8 and data_021c81d4), which the text boxes (text_draw.h) draw with.
 *
 * A font is three files of the ROM's file system: "/font/<name>_head.bin" (the glyph count and
 * the size of a glyph's bitmap), "/font/<name>_attr.bin" (one entry per glyph: its character
 * code and its width) and "/font/<name>_img.bin" (the bitmaps, one bit per pixel, read glyph by
 * glyph from the open file). The first two are read whole into blocks of the current heap; the
 * third stays open. A glyph index with the top bit set names a glyph of the fallback font. */
#ifndef CLEAN_MAIN_TEXT_FONT_H
#define CLEAN_MAIN_TEXT_FONT_H

#include "types.h"

/* A glyph index's top bit: the glyph belongs to the fallback font. */
#define TEXT_FONT_FALLBACK_BIT 0x80000000u

/* "/font/<name>_head.bin". */
typedef struct TextFontHeader {
    u32 count;  /* glyphs */
    u16 width;  /* of every glyph's bitmap, in pixels */
    u16 height; /* the same */
} TextFontHeader;

/* An entry of "/font/<name>_attr.bin". */
typedef struct TextFontGlyph {
    u16 code; /* the character it draws */
    u8 width; /* how far the pen moves, in pixels */
    u8 unk_03;
} TextFontGlyph;

typedef struct TextFont {
    TextFontHeader *header; /* NULL when not loaded */
    TextFontGlyph *glyphs;  /* the same */
    void *unk_08;           /* freed with the others; nothing here loads it */
    struct TextFont *fallback;
    u8 unk_10;
    u8 pad_11[3];
    u8 image_file[0x48]; /* 0x14: the FSFile of "/font/<name>_img.bin" */
} TextFont;

int TextFont_FindGlyph(TextFont *font, int code);
unsigned int TextFont_GlyphWidth(TextFont *font, unsigned int glyph);
void TextFont_Close(TextFont *font);
void TextFont_Open(TextFont *font, const char *name, const char *variant, TextFont *fallback, unsigned char unk_10);
TextFont *TextFont_Destruct(TextFont *font);
void TextFont_Construct(TextFont *font);

#endif
