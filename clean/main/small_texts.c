/* Four small text classes (small_texts.h). */
#include "small_texts.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(Wide10Text, text) == 0xe, "wide text characters");
static_assert(sizeof(Wide10Text) == 0x24, "wide text size");
static_assert(offsetof(Label22Text, text) == 0x12, "label characters");
static_assert(sizeof(Label22Text) == 0x28, "label size");
static_assert(offsetof(CatchphraseWide, text) == 0xe, "wide text characters");
static_assert(sizeof(CatchphraseWide) == 0x18, "wide text size");
static_assert(offsetof(Label10Text, text) == 0x12, "label characters");
static_assert(sizeof(Label10Text) == 0x1c, "label size");

extern const TextVtable data_020e194c; /* the 10-character wide text's vtable */
extern const TextVtable data_020e18d4; /* the 22-character label's vtable */
extern const TextVtable data_020e1934; /* the 4-character wide text's vtable */
extern const TextVtable data_020e1904; /* the 10-character label's vtable */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The text base's constructors and destructors. */
extern void *func_020a88ec(void *text);  /* base of a wide text */
extern void *func_020a887c(void *text);  /* its destructor */
extern void *func_020a8cac(void *label); /* base of a label */
extern void *func_020a8c38(void *label); /* its destructor */

/* ---- Wide text of 10 characters */

/* func_02082060 (vtable entry 3): the address of the characters. */
int Wide10Text_Buffer(int text)
{
    return (int) ((u32) text + offsetof(Wide10Text, text));
}
CLEAN_AS(func_02082060, Wide10Text_Buffer)

/* func_02082064 (vtable entry 2) */
int Wide10Text_Capacity(void)
{
    return WIDE10_TEXT_CAPACITY;
}
CLEAN_AS(func_02082064, Wide10Text_Capacity)

/* func_02082068 (vtable entry 1) */
Wide10Text *Wide10Text_DestructDelete(Wide10Text *text)
{
    text->vtable = &data_020e194c;
    func_020a887c(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02082068, Wide10Text_DestructDelete)

/* func_02082088 (vtable entry 0) */
Wide10Text *Wide10Text_Destruct(Wide10Text *text)
{
    text->vtable = &data_020e194c;
    func_020a887c(text);
    return text;
}
CLEAN_AS(func_02082088, Wide10Text_Destruct)

/* func_020820a0 */
Wide10Text *Wide10Text_Construct(Wide10Text *text)
{
    func_020a88ec(text);
    text->vtable = &data_020e194c;
    return text;
}
CLEAN_AS(func_020820a0, Wide10Text_Construct)

/* ---- Label of 22 characters */

/* func_020820b8 (vtable entry 3): the address of the characters. */
int Label22Text_Buffer(int label)
{
    return (int) ((u32) label + offsetof(Label22Text, text));
}
CLEAN_AS(func_020820b8, Label22Text_Buffer)

/* func_020820bc (vtable entry 2) */
int Label22Text_Capacity(void)
{
    return LABEL22_TEXT_CAPACITY;
}
CLEAN_AS(func_020820bc, Label22Text_Capacity)

/* func_020820c0 (vtable entry 1) */
Label22Text *Label22Text_DestructDelete(Label22Text *label)
{
    label->vtable = &data_020e18d4;
    func_020a8c38(label);
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_020820c0, Label22Text_DestructDelete)

/* func_020820e0 (vtable entry 0) */
Label22Text *Label22Text_Destruct(Label22Text *label)
{
    label->vtable = &data_020e18d4;
    func_020a8c38(label);
    return label;
}
CLEAN_AS(func_020820e0, Label22Text_Destruct)

/* func_020820f8 */
Label22Text *Label22Text_Construct(Label22Text *label)
{
    func_020a8cac(label);
    label->vtable = &data_020e18d4;
    return label;
}
CLEAN_AS(func_020820f8, Label22Text_Construct)

/* ---- Wide text of 4 characters */

/* func_02082110 (vtable entry 3): the address of the characters. */
int CatchphraseWide_Buffer(int text)
{
    return (int) ((u32) text + offsetof(CatchphraseWide, text));
}
CLEAN_AS(func_02082110, CatchphraseWide_Buffer)

/* func_02082114: the first `count` characters (at most four) copied to `dst`.
 * QUIRK: a negative count is not clipped: twice it goes to MI_CpuCopy8 as an unsigned size. */
void CatchphraseWide_CopyOut(CatchphraseWide *text, u16 *dst, int count)
{
    if (count >= CATCHPHRASE_WIDE_CAPACITY) {
        count = CATCHPHRASE_WIDE_CAPACITY;
    }
    MI_CpuCopy8(text->text, dst, (u32) count * 2);
}
CLEAN_AS(func_02082114, CatchphraseWide_CopyOut)

/* func_02082128 (vtable entry 2) */
int CatchphraseWide_Capacity(void)
{
    return CATCHPHRASE_WIDE_CAPACITY;
}
CLEAN_AS(func_02082128, CatchphraseWide_Capacity)

/* func_0208212c (vtable entry 1) */
CatchphraseWide *CatchphraseWide_DestructDelete(CatchphraseWide *text)
{
    text->vtable = &data_020e1934;
    func_020a887c(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0208212c, CatchphraseWide_DestructDelete)

/* func_0208214c (vtable entry 0) */
CatchphraseWide *CatchphraseWide_Destruct(CatchphraseWide *text)
{
    text->vtable = &data_020e1934;
    func_020a887c(text);
    return text;
}
CLEAN_AS(func_0208214c, CatchphraseWide_Destruct)

/* func_02082164 */
CatchphraseWide *CatchphraseWide_Construct(CatchphraseWide *text)
{
    func_020a88ec(text);
    text->vtable = &data_020e1934;
    return text;
}
CLEAN_AS(func_02082164, CatchphraseWide_Construct)

/* ---- Label of 10 characters */

/* func_0208217c (vtable entry 3): the address of the characters. */
int Label10Text_Buffer(int label)
{
    return (int) ((u32) label + offsetof(Label10Text, text));
}
CLEAN_AS(func_0208217c, Label10Text_Buffer)

/* func_02082180 (vtable entry 2) */
int Label10Text_Capacity(void)
{
    return LABEL10_TEXT_CAPACITY;
}
CLEAN_AS(func_02082180, Label10Text_Capacity)

/* func_02082184 (vtable entry 1) */
Label10Text *Label10Text_DestructDelete(Label10Text *label)
{
    label->vtable = &data_020e1904;
    func_020a8c38(label);
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_02082184, Label10Text_DestructDelete)

/* func_020821a4 (vtable entry 0) */
Label10Text *Label10Text_Destruct(Label10Text *label)
{
    label->vtable = &data_020e1904;
    func_020a8c38(label);
    return label;
}
CLEAN_AS(func_020821a4, Label10Text_Destruct)

/* func_020821bc */
Label10Text *Label10Text_Construct(Label10Text *label)
{
    func_020a8cac(label);
    label->vtable = &data_020e1904;
    return label;
}
CLEAN_AS(func_020821bc, Label10Text_Construct)
