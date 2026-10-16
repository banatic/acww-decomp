/* Two small text classes that hold a name (name_texts.h). */
#include "name_texts.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "furniture_info.h"
#include "item_code.h"
#include "item_form.h"
#include "item_info.h"
#include "text_base.h"
#include "text_string.h"

static_assert(sizeof(NameWideText) == 0x24 && offsetof(NameWideText, chars) == 0x0e, "NameWideText layout");
static_assert(sizeof(NameText) == 0x28 && offsetof(NameText, attr_04) == 0x0c && offsetof(NameText, chars) == 0x12,
              "NameText layout");

extern const u8 data_020de614[]; /* the wide name's vtable */
extern const u8 data_020de62c[]; /* the 8-bit name's vtable */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

typedef int NameTextCapacity(void *text);

/* A text's capacity, through its vtable (slot 2). */
static int name_texts_capacity(void *text)
{
    const TextVtable *vtable = *(const TextVtable *const *) text;
    return ((NameTextCapacity *) (uintptr_t) vtable->capacity)(text);
}

/* ---- the wide name */

/* func_02062da4: when `room` holds the text's capacity, its characters (as many as the
 * capacity) copied to `out`, and 1; else 0 and nothing copied. The capacity is asked of the
 * vtable twice. */
int NameWideText_CopyOut(NameWideText *text, u16 *out, int room)
{
    if (room < name_texts_capacity(text)) {
        return 0;
    }
    int count = name_texts_capacity(text);
    MI_CpuCopy8(text->chars, out, (u32) count * 2);
    return 1;
}
CLEAN_AS(func_02062da4, NameWideText_CopyOut)

/* func_02062dd8 (vtable slot 3): the address of the characters. */
int NameWideText_Chars(int text)
{
    return text + (int) offsetof(NameWideText, chars);
}
CLEAN_AS(func_02062dd8, NameWideText_Chars)

/* func_02062ddc (vtable slot 2): the capacity. */
int NameWideText_Capacity(void)
{
    return NAME_WIDE_TEXT_CAPACITY;
}
CLEAN_AS(func_02062ddc, NameWideText_Capacity)

/* func_02062de0 (vtable slot 1): destructs and frees. */
NameWideText *NameWideText_Delete(NameWideText *text)
{
    text->vtable = (const TextVtable *) data_020de614;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02062de0, NameWideText_Delete)

/* func_02062e00 (vtable slot 0): the destructor. */
NameWideText *NameWideText_Destruct(NameWideText *text)
{
    text->vtable = (const TextVtable *) data_020de614;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_02062e00, NameWideText_Destruct)

/* func_02062e18: constructed, cleared, then given the 10 characters at `chars` (copied a
 * character at a time, first to last). */
NameWideText *NameWideText_ConstructFrom(NameWideText *text, const u16 *chars)
{
    TextBase_WideConstruct(text);
    text->vtable = (const TextVtable *) data_020de614;
    TextString_ClearWide((TextObject *) text);
    for (int i = 0; i < NAME_WIDE_TEXT_CAPACITY; i++) {
        text->chars[i] = chars[i];
    }
    return text;
}
CLEAN_AS(func_02062e18, NameWideText_ConstructFrom)

/* func_02062e50: the constructor: an empty text. */
NameWideText *NameWideText_Construct(NameWideText *text)
{
    TextBase_WideConstruct(text);
    text->vtable = (const TextVtable *) data_020de614;
    TextString_ClearWide((TextObject *) text);
    return text;
}
CLEAN_AS(func_02062e50, NameWideText_Construct)

/* ---- the 8-bit name */

/* func_02062e70 (vtable slot 3): the address of the characters. */
int NameText_Chars(int text)
{
    return text + (int) offsetof(NameText, chars);
}
CLEAN_AS(func_02062e70, NameText_Chars)

/* func_02062e74 (vtable slot 2): the capacity. */
int NameText_Capacity(void)
{
    return NAME_TEXT_CAPACITY;
}
CLEAN_AS(func_02062e74, NameText_Capacity)

/* func_02062e78: the text set to a message text (TextBase_SetChars); whether it fitted. */
int NameText_SetChars(int text, int chars)
{
    return TextBase_SetChars((TextBase *) (uintptr_t) (u32) text, (const char *) (uintptr_t) (u32) chars);
}
CLEAN_AS(func_02062e78, NameText_SetChars)

/* func_02062e80: the text set to the name of series `series`, and 1; 0 for a number past the
 * last series (nothing set). */
int NameText_SetSeries(int text, int series)
{
    if (series >= ITEM_INFO_SERIES) {
        return 0;
    }
    NameText_SetChars(text, (int) (uintptr_t) ItemInfo_SeriesRecord(series));
    return 1;
}
CLEAN_AS(func_02062e80, NameText_SetSeries)

/* func_02062ea4: the text set to the name of the item `item` stands for when carried
 * (ItemForm_ToCarried), from its dma.bin record: an item of kind 1 by item_info.h, one with a
 * variant by furniture_info.h; the attributes' fields 0x04, 0x09 and 0x08 set from the three
 * values their files give for it (all -1). 1 then, 0 for an item of another kind (nothing
 * set). */
int NameText_SetItem(NameText *text, u16 *item)
{
    u16 carried;
    ItemForm_ToCarried(&carried, item);
    if (ItemCode_IsKind1(&carried)) {
        NameText_SetChars((int) (uintptr_t) text, (int) (uintptr_t) ItemInfo_Dma(&carried));
        text->attr_04 = ItemInfo_NoneC(&carried);
        text->attr_09 = (u8) ItemInfo_NoneB(&carried);
        text->attr_08 = (u8) ItemInfo_NoneA(&carried);
        return 1;
    }
    if (ItemCode_HasVariant(&carried)) {
        int number = ItemCode_VariantItem(&carried);
        NameText_SetChars((int) (uintptr_t) text, (int) (uintptr_t) FurnitureInfo_Dma(number));
        text->attr_04 = FurnitureInfo_NoneC(number);
        text->attr_09 = (u8) FurnitureInfo_NoneB(number);
        text->attr_08 = (u8) FurnitureInfo_NoneA(number);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02062ea4, NameText_SetItem)

/* func_02062f2c (vtable slot 1): destructs and frees. */
NameText *NameText_Delete(NameText *text)
{
    text->vtable = (const TextVtable *) data_020de62c;
    TextBase_Destruct((TextBase *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02062f2c, NameText_Delete)

/* func_02062f4c (vtable slot 0): the destructor. */
NameText *NameText_Destruct(NameText *text)
{
    text->vtable = (const TextVtable *) data_020de62c;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_02062f4c, NameText_Destruct)

/* func_02062f64: constructed, cleared, and set to a series' name (NameText_SetSeries). */
NameText *NameText_ConstructSeries(NameText *text, int series)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020de62c;
    TextBase_Clear(text);
    NameText_SetSeries((int) (uintptr_t) text, series);
    return text;
}
CLEAN_AS(func_02062f64, NameText_ConstructSeries)

/* func_02062f90: constructed, cleared, and set to an item's name (NameText_SetItem). */
NameText *NameText_ConstructItem(NameText *text, u16 *item)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020de62c;
    TextBase_Clear(text);
    NameText_SetItem(text, item);
    return text;
}
CLEAN_AS(func_02062f90, NameText_ConstructItem)

/* func_02062fbc: the constructor: an empty text. */
NameText *NameText_Construct(NameText *text)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020de62c;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_02062fbc, NameText_Construct)
