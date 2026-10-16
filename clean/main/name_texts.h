/* Two small text classes of main that hold a name: they derive from the text bases of
 * text_base.h, with the four vtable entries of a text (TextVtable).
 *
 * - A wide name (vtable data_020de614, 0x24 bytes): 10 16-bit characters, as a design's title
 *   is kept (design_info.h). NameWideText_CopyOut copies them out.
 * - An 8-bit name (vtable data_020de62c, 0x28 bytes): 22 bytes, set from an item code (the
 *   item's dma.bin record, which begins with its name; item_info.h, furniture_info.h) or from
 *   a series number (series.bin's record, which begins with the series' name). The item's
 *   three further values are put in the text's attributes. */
#ifndef CLEAN_MAIN_NAME_TEXTS_H
#define CLEAN_MAIN_NAME_TEXTS_H

#include "text_label.h" /* TextVtable */
#include "types.h"

#define NAME_WIDE_TEXT_CAPACITY 10
#define NAME_TEXT_CAPACITY 22

typedef struct NameWideText {
    const TextVtable *vtable;           /* 0x00: data_020de614 */
    u8 attributes[0x0a];                /* 0x04: the wide text base's */
    u16 chars[NAME_WIDE_TEXT_CAPACITY]; /* 0x0e */
    u8 pad_22[2];
} NameWideText;

typedef struct NameText {
    const TextVtable *vtable;       /* 0x00: data_020de62c */
    u32 length;                     /* 0x04: the text base's */
    const void *attr_vtable;        /* 0x08: the text's attributes (MessageAttributes) */
    s32 attr_04;                    /* 0x0c */
    u8 attr_08;                     /* 0x10 */
    u8 attr_09;                     /* 0x11 */
    char chars[NAME_TEXT_CAPACITY]; /* 0x12 */
} NameText;

int NameWideText_CopyOut(NameWideText *text, u16 *out, int room);
int NameWideText_Chars(int text);
int NameWideText_Capacity(void);
NameWideText *NameWideText_Delete(NameWideText *text);
NameWideText *NameWideText_Destruct(NameWideText *text);
NameWideText *NameWideText_ConstructFrom(NameWideText *text, const u16 *chars);
NameWideText *NameWideText_Construct(NameWideText *text);
int NameText_Chars(int text);
int NameText_Capacity(void);
int NameText_SetChars(int text, int chars);
int NameText_SetSeries(int text, int series);
int NameText_SetItem(NameText *text, u16 *item);
NameText *NameText_Delete(NameText *text);
NameText *NameText_Destruct(NameText *text);
NameText *NameText_ConstructSeries(NameText *text, int series);
NameText *NameText_ConstructItem(NameText *text, u16 *item);
NameText *NameText_Construct(NameText *text);

#endif
