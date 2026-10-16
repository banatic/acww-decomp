/* The bitmap fonts of the text boxes (text_font.h). */
#include "text_font.h"

#include "autoload_2/heap.h" /* Heap_FreeCurrent */
#include "clean.h"

static_assert(sizeof(TextFontHeader) == 8, "TextFontHeader size");
static_assert(sizeof(TextFontGlyph) == 4, "TextFontGlyph size");
static_assert(offsetof(TextFontGlyph, width) == 2, "TextFontGlyph width");
static_assert(offsetof(TextFont, fallback) == 0x0c, "TextFont fallback");
static_assert(offsetof(TextFont, unk_10) == 0x10, "TextFont unk_10");
static_assert(offsetof(TextFont, image_file) == 0x14, "TextFont image_file");
static_assert(sizeof(TextFont) == 0x5c, "TextFont size");

/* The two files read whole, by the suffix of their name: "head" and "attr". */
#define TEXT_FONT_TABLE_FILES 2

extern const char *const data_020cb918[TEXT_FONT_TABLE_FILES]; /* "head", "attr" */
extern const char data_020dcfa8[];                             /* "/font/%s_%s_%s.bin" */
extern const char data_020dcfbc[];                             /* "/font/%s_%s.bin" */
extern const char data_020dcfcc[];                             /* "/font/%s_img.bin" */

/* A file of the ROM read whole into a new block of the current heap, its path formatted from
 * `format` as by sprintf. */
extern void *func_0206493c(const char *format, ...);
/* sprintf (the runtime library's, not named in the ROM's symbols) */
extern int func_0212a13c(void *buffer, const void *format, int arg);
extern int FS_OpenFile(void *file, const void *path);
extern int FS_CloseFile(void *file);

/* The character code of glyph `glyph`, or -1 when the font has no such glyph. Only one level
 * of fallback is looked at. */
static int glyph_code(const TextFont *font, u32 glyph)
{
    if (glyph & TEXT_FONT_FALLBACK_BIT) {
        const TextFont *fallback = font->fallback;
        u32 index = glyph & ~TEXT_FONT_FALLBACK_BIT;
        return index < fallback->header->count ? fallback->glyphs[index].code : -1;
    }
    return glyph < font->header->count ? font->glyphs[glyph].code : -1;
}

/* func_020516b8: the index of the glyph that draws character `code`, or -1 when the font has
 * none. QUIRK: the search runs over the font's own glyph count, so the fallback font's glyphs
 * (indexes with the top bit set) are only reached when that count is 2^31 or more, and there a
 * fallback index past the fallback's end matches a `code` of -1. */
int TextFont_FindGlyph(TextFont *font, int code)
{
    for (u32 glyph = 0; glyph < font->header->count; glyph++) {
        if (glyph_code(font, glyph) == code) {
            return (int) glyph;
        }
    }
    return -1;
}
CLEAN_AS(func_020516b8, TextFont_FindGlyph)

/* func_0205171c: how far glyph `glyph` moves the pen, in pixels; 0 for an index past the end.
 * A glyph of the fallback font is looked up there (through as many fallbacks as the top bit
 * says, which is one). */
unsigned int TextFont_GlyphWidth(TextFont *font, unsigned int glyph)
{
    if (glyph & TEXT_FONT_FALLBACK_BIT) {
        return TextFont_GlyphWidth(font->fallback, glyph & ~TEXT_FONT_FALLBACK_BIT);
    }
    if (glyph < font->header->count) {
        return font->glyphs[glyph].width;
    }
    return 0;
}
CLEAN_AS(func_0205171c, TextFont_GlyphWidth)

/* func_02051758: the loaded tables freed and the bitmap file closed. */
void TextFont_Close(TextFont *font)
{
    if (font->header != NULL) {
        Heap_FreeCurrent(font->header);
        font->header = NULL;
    }
    if (font->glyphs != NULL) {
        Heap_FreeCurrent(font->glyphs);
        font->glyphs = NULL;
    }
    if (font->unk_08 != NULL) {
        Heap_FreeCurrent(font->unk_08);
        font->unk_08 = NULL;
    }
    FS_CloseFile(font->image_file);
}
CLEAN_AS(func_02051758, TextFont_Close)

/* func_02051794: font `name` loaded: "/font/<name>_head.bin" and "/font/<name>_attr.bin" (with
 * "_<variant>" before ".bin" when a variant is given) read, then the bitmap file opened. Both
 * tables are read before either pointer is stored. */
void TextFont_Open(TextFont *font, const char *name, const char *variant, TextFont *fallback, unsigned char unk_10)
{
    void *tables[TEXT_FONT_TABLE_FILES];
    char path[0x84];

    for (int i = 0; i < TEXT_FONT_TABLE_FILES; i++) {
        if (variant != NULL) {
            tables[i] = func_0206493c(data_020dcfa8, name, data_020cb918[i], variant);
        } else {
            tables[i] = func_0206493c(data_020dcfbc, name, data_020cb918[i]);
        }
    }
    font->header = tables[0];
    font->glyphs = tables[1];

    func_0212a13c(path, data_020dcfcc, (int) (uintptr_t) name);
    FS_OpenFile(font->image_file, path);

    font->fallback = fallback;
    font->unk_10 = unk_10;
}
CLEAN_AS(func_02051794, TextFont_Open)

/* func_02051810: the destructor (registered for the four global fonts): the font closed. */
TextFont *TextFont_Destruct(TextFont *font)
{
    TextFont_Close(font);
    return font;
}
CLEAN_AS(func_02051810, TextFont_Destruct)

/* func_02051820: the constructor: no tables loaded. */
void TextFont_Construct(TextFont *font)
{
    font->header = NULL;
    font->glyphs = NULL;
    font->unk_08 = NULL;
}
CLEAN_AS(func_02051820, TextFont_Construct)
