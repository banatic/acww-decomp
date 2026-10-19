/* Wide texts, labels and their text boxes (text_label.h). */
#include "text_label.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "autoload_2/heap.h"
#include "display_layers.h"
#include "label_box.h"
#include "message_reader.h"
#include "number_text.h"
#include "text_base.h"
#include "text_draw.h"
#include "text_string.h"

static_assert(offsetof(WideText, text) == 0xe, "wide text characters");
static_assert(sizeof(WideText) == 0x60, "wide text size");
static_assert(offsetof(TextLabel, text) == 0x12, "label characters");
static_assert(offsetof(TextLabel, box) == 0x68, "label box");

/* The number of 16-bit characters TextLabel_CopyWide writes. */
#define LABEL_WIDE_COPY WIDE_TEXT_CAPACITY

/* The archive TextLabel_LoadMenuMessageAt names: none, which func_020b4980 reads as "2d_menu". */
#define DEFAULT_ARCHIVE NULL

/* The boxes' modes func_020a8fe8 / func_020a9034 are asked for. */
#define BOX_MODE_1 1
#define BOX_MODE_2 2

extern const TextVtable data_020e1784; /* the wide text's vtable */
extern const TextVtable data_020e179c; /* the label's vtable */
extern TextFont data_021c828c;         /* the font TextLabel_OpenStyledBox gives its box */
extern TextFont data_021c82e8;         /* the other font TextLabel_OpenStyledBox2 can */

extern int func_02051c8c_unk(u16 *text, int max); /* the 16-bit characters before a 0, at most max */

typedef char *(*TextBufferMethod)(void *self);

/* The object's characters, through its vtable. */
static const char *buffer_of(TextLabel *label)
{
    return ((TextBufferMethod) (uintptr_t) label->vtable->buffer)(label);
}

/* ---- Wide text */

/* func_02070784: its length, up to the first 0 and at most its capacity. */
int WideText_Length(WideText *text)
{
    return func_02051c8c_unk(text->text, WIDE_TEXT_CAPACITY);
}
CLEAN_AS(func_02070784, WideText_Length)

/* func_02070790 (vtable entry 3): the address of the characters. */
int WideText_Buffer(int text)
{
    return (int) ((u32) text + offsetof(WideText, text));
}
CLEAN_AS(func_02070790, WideText_Buffer)

/* func_02070794 (vtable entry 2) */
int WideText_Capacity(void)
{
    return WIDE_TEXT_CAPACITY;
}
CLEAN_AS(func_02070794, WideText_Capacity)

/* func_02070798 (vtable entry 1) */
WideText *WideText_DestructDelete(WideText *text)
{
    text->vtable = &data_020e1784;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02070798, WideText_DestructDelete)

/* func_020707b8 (vtable entry 0) */
void *WideText_Destruct(void *text)
{
    ((WideText *) text)->vtable = &data_020e1784;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_020707b8, WideText_Destruct)

/* func_020707d0 */
void *WideText_Construct(void *text)
{
    TextBase_WideConstruct(text);
    ((WideText *) text)->vtable = &data_020e1784;
    return text;
}
CLEAN_AS(func_020707d0, WideText_Construct)

/* ---- Converting a label's text */

/* func_020707e8: whether the label's text, in 16 bits, equals the first `length` characters of
 * `text`, both without trailing spaces. REQUIRES: length <= 41 (the game passes the length of a
 * name the player entered); the original reads past the wide text otherwise. */
int TextLabel_EqualsTrimmed(TextLabel *label, const u16 *text, u16 length)
{
    WideText wide;
    WideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) &wide, (TextBase *) label);
    int equal = 1;
    int n = TextString_TrimmedLength((u16 *) text, length);
    if (n != TextString_TrimmedLength(wide.text, length)) {
        equal = 0;
    } else {
        for (int i = 0; i < n; i++) {
            if (text[i] != wide.text[i]) {
                equal = 0;
                break;
            }
        }
    }
    WideText_Destruct(&wide);
    return equal;
}
CLEAN_AS(func_020707e8, TextLabel_EqualsTrimmed)

/* func_02070854: pass four values to the label's box (func_02051608 stores them at 0x3a, 0x3b,
 * 0x40 and 0x44); nothing without a box. */
void TextLabel_SetBoxParams(TextLabel *label, int a, int b, int c, int d)
{
    if (label->box != NULL) {
        TextDraw_SetMark(&label->box->base, (u8) a, (u8) b, c, d);
    }
}
CLEAN_AS(func_02070854, TextLabel_SetBoxParams)

/* func_02070870: set the label from `length` 16-bit characters; the end code is only added
 * when newlines are escaped. */
void TextLabel_SetFromWideConverted(TextLabel *label, const u16 *text, int length, int escape_newlines, u8 end_code)
{
    if (escape_newlines == 0) {
        end_code = 0;
    }
    WideText wide;
    WideText_Construct(&wide);
    TextBase_SetWide(&wide, text, length);
    TextBase_WideToBytes((TextBase *) label, (WideTextBase *) &wide, escape_newlines, end_code);
    WideText_Destruct(&wide);
}
CLEAN_AS(func_02070870, TextLabel_SetFromWideConverted)

/* func_020708b4: the label's text as 41 16-bit characters, padded with 0. */
void TextLabel_CopyWide(void *label, u16 *out)
{
    WideText wide;
    WideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) &wide, label);
    TextString_CopyWideOut((TextObject *) &wide, out, LABEL_WIDE_COPY);
    WideText_Destruct(&wide);
}
CLEAN_AS(func_020708b4, TextLabel_CopyWide)

/* func_020708e4: set the label from `length` 16-bit characters, as they are. */
void TextLabel_SetFromWide(void *label, const u16 *text, void *length)
{
    WideText wide;
    WideText_Construct(&wide);
    TextBase_SetWide(&wide, text, (int) (uintptr_t) length);
    TextBase_WideToBytes(label, (WideTextBase *) &wide, 0, 0);
    WideText_Destruct(&wide);
}
CLEAN_AS(func_020708e4, TextLabel_SetFromWide)

/* func_02070918: build the label's text with func_020b45d0. */
int TextLabel_Compose(TextLabel *label, int a, int b, int kind, int extra, u8 raw)
{
    return NumberText_Format(label, a, b, kind, extra, raw);
}
CLEAN_AS(func_02070918, TextLabel_Compose)

/* func_02070934: load message `number` of the named archive. */
void TextLabel_LoadMessage(TextLabel *label, char *archive, char number)
{
    MessageReader_LoadMessage((int) (uintptr_t) label, (unsigned char *) &number, (int) (uintptr_t) archive);
}
CLEAN_AS(func_02070934, TextLabel_LoadMessage)

/* func_0207094c: load message `number` of "2d_menu". */
int TextLabel_LoadMenuMessage(TextLabel *label, char number)
{
    return TextLabel_LoadMenuMessageAt(label, (int) (uintptr_t) &number);
}
CLEAN_AS(func_0207094c, TextLabel_LoadMenuMessage)

/* func_02070960: load the message of "2d_menu" whose number `number` points to. */
int TextLabel_LoadMenuMessageAt(TextLabel *label, int number)
{
    return MessageReader_LoadMenuMessage((int) (uintptr_t) label, (unsigned char *) ((const char *) (uintptr_t) number),
                                         DEFAULT_ARCHIVE);
}
CLEAN_AS(func_02070960, TextLabel_LoadMenuMessageAt)

/* func_0207096c: the width of the label's text, in pixels. */
int TextLabel_TextWidth(void *label)
{
    return LabelBox_CharsWidth((int) (uintptr_t) ((TextLabel *) label)->text);
}
CLEAN_AS(func_0207096c, TextLabel_TextWidth)

/* ---- The label's box */

/* func_02070978: show the text from `offset` pixels; nothing without a box. */
void TextLabel_ShowAt(TextLabel *label, int offset)
{
    if (label->box == NULL) {
        return;
    }
    label->box->base.text = buffer_of(label);
    label->box->base.offset = (u32) offset;
    TextDraw_RequestDraw(&label->box->base);
}
CLEAN_AS(func_02070978, TextLabel_ShowAt)

/* func_0207099c: show the text against the box's right edge; nothing without a box. */
void TextLabel_ShowRightAligned(TextLabel *label)
{
    if (label->box == NULL) {
        return;
    }
    label->box->base.text = buffer_of(label);
    TextDraw_AlignRight(&label->box->base);
    TextDraw_RequestDraw(&label->box->base);
}
CLEAN_AS(func_0207099c, TextLabel_ShowRightAligned)

/* func_020709c4: show the text in the middle or from the left, moved `shift` pixels; nothing
 * without a box. */
void TextLabel_ShowShifted(TextLabel *label, int center, int shift)
{
    if (label->box == NULL) {
        return;
    }
    label->box->base.text = buffer_of(label);
    if (center != 0) {
        TextDraw_Center(&label->box->base);
    } else {
        label->box->base.offset = 0;
    }
    label->box->base.offset += (u32) shift;
    TextDraw_RequestDraw(&label->box->base);
}
CLEAN_AS(func_020709c4, TextLabel_ShowShifted)

/* func_02070a04: show the text in the middle or from the left, with the text underlined
 * when `underline` is set; nothing without a box. */
void TextLabel_Show(TextLabel *label, int center, int underline)
{
    if (label->box == NULL) {
        return;
    }
    label->box->base.text = buffer_of(label);
    label->box->base.underline = underline != 0;
    if (center != 0) {
        TextDraw_Center(&label->box->base);
    } else {
        label->box->base.offset = 0;
    }
    TextDraw_RequestDraw(&label->box->base);
}
CLEAN_AS(func_02070a04, TextLabel_Show)

/* func_02070a54: replace the label's box with one from func_020a8fe8 (mode 2) that draws at
 * once, in the two colours given. */
void TextLabel_OpenBox(TextLabel *label, int a, int b, int color_38, u8 color_39)
{
    if (label->box != NULL) {
        TextLabel_CloseBox(label);
    }
    label->box = LabelBox_New(a, b, BOX_MODE_2);
    if (label->box != NULL) {
        label->box->base.background = color_39;
        label->box->base.color = (u8) color_38;
        label->box->base.update_mode = 2;
    }
}
CLEAN_AS(func_02070a54, TextLabel_OpenBox)

/* func_02070a98: replace the label's box with one from func_020a9034 (mode 1) in `style` and
 * the two colours, with the font data_021c828c. QUIRK: the last argument is not read.
 * REQUIRES: the box is allocated; the original writes the font to address 0x28 otherwise. */
void TextLabel_OpenStyledBox(TextLabel *label, int style, int a, int b, u8 color_38, u8 color_39, int unused)
{
    (void) unused;
    if (label->box != NULL) {
        TextLabel_CloseBox(label);
    }
    label->box = LabelBox_NewInVram(a, b, BOX_MODE_1);
    TextLabel_SetStyle(label, style, (char) color_38, (char) color_39);
    label->box->base.font = &data_021c828c;
}
CLEAN_AS(func_02070a98, TextLabel_OpenStyledBox)

/* func_02070adc: as TextLabel_OpenStyledBox in mode 2, with the font data_021c82e8 when
 * `other_font` is set (else the box's own). REQUIRES: with `other_font`, the box is allocated
 * (as above). */
void TextLabel_OpenStyledBox2(TextLabel *label, int style, int a, int b, u8 color_38, u8 color_39, int other_font)
{
    if (label->box != NULL) {
        TextLabel_CloseBox(label);
    }
    label->box = LabelBox_NewInVram(a, b, BOX_MODE_2);
    TextLabel_SetStyle(label, style, (char) color_38, (char) color_39);
    if (other_font != 0) {
        label->box->base.font = &data_021c82e8;
    }
}
CLEAN_AS(func_02070adc, TextLabel_OpenStyledBox2)

/* func_02070b24: give the box the style and the two colours. QUIRK: the style is converted
 * (func_02002dc8) even when there is no box. */
void TextLabel_SetStyle(TextLabel *label, int style, char color_38, char color_39)
{
    int box_style = DisplayLayer_PlaneNumber(style);
    LabelBox *box = label->box;
    if (box == NULL) {
        return;
    }
    box->base.layer = box_style;
    label->box->base.screens = DisplayLayer_IsMainScreen((unsigned int) style) != 0 ? TEXT_DRAW_TO_MAIN : TEXT_DRAW_TO_SUB;
    label->box->base.rows_full_width = box_style == 4;
    label->box->base.background = (u8) color_39;
    label->box->base.color = (u8) color_38;
}
CLEAN_AS(func_02070b24, TextLabel_SetStyle)

/* func_02070b84: free the label's box, if any. */
void TextLabel_CloseBox(void *label)
{
    TextLabel *l = label;
    if (l->box != NULL) {
        LabelBox_Free(l->box);
        l->box = NULL;
    }
}
CLEAN_AS(func_02070b84, TextLabel_CloseBox)

/* func_02070b9c (vtable entry 3): the address of the characters. */
int TextLabel_Buffer(int label)
{
    return (int) ((u32) label + offsetof(TextLabel, text));
}
CLEAN_AS(func_02070b9c, TextLabel_Buffer)

/* func_02070ba0 (vtable entry 2) */
int TextLabel_Capacity(void)
{
    return TEXT_LABEL_CAPACITY;
}
CLEAN_AS(func_02070ba0, TextLabel_Capacity)

/* func_02070ba4: QUIRK: a second copy of TextLabel_Destruct that nothing calls. */
TextLabel *TextLabel_DestructCopy(TextLabel *label)
{
    label->vtable = &data_020e179c;
    TextLabel_CloseBox(label);
    TextBase_Destruct((TextBase *) label);
    return label;
}
CLEAN_AS(func_02070ba4, TextLabel_DestructCopy)

/* func_02070bc4 (vtable entry 1) */
TextLabel *TextLabel_DestructDelete(TextLabel *label)
{
    label->vtable = &data_020e179c;
    TextLabel_CloseBox(label);
    TextBase_Destruct((TextBase *) label);
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_02070bc4, TextLabel_DestructDelete)

/* func_02070be8 (vtable entry 0): free the box, then the base. */
TextLabel *TextLabel_Destruct(TextLabel *label)
{
    label->vtable = &data_020e179c;
    TextLabel_CloseBox(label);
    TextBase_Destruct((TextBase *) label);
    return label;
}
CLEAN_AS(func_02070be8, TextLabel_Destruct)

/* func_02070c08: an empty label without a box. */
TextLabel *TextLabel_Construct(TextLabel *label)
{
    TextBase_Construct(label);
    label->vtable = &data_020e179c;
    TextBase_Clear(label);
    label->box = NULL;
    return label;
}
CLEAN_AS(func_02070c08, TextLabel_Construct)

/* func_02070c2c: QUIRK: a second copy of TextLabel_Construct that nothing calls. */
TextLabel *TextLabel_ConstructCopy(TextLabel *label)
{
    TextBase_Construct(label);
    label->vtable = &data_020e179c;
    TextBase_Clear(label);
    label->box = NULL;
    return label;
}
CLEAN_AS(func_02070c2c, TextLabel_ConstructCopy)
