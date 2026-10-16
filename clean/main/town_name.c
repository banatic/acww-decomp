/* A town's number and name, and its two text classes (town_name.h). */
#include "town_name.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "main_random.h"

static_assert(sizeof(TownName) == 0x0e && offsetof(TownName, name) == 0x02, "TownName layout");
static_assert(sizeof(TownNameWideText) == 0x1c && offsetof(TownNameWideText, chars) == 0x0e, "TownNameWideText layout");
static_assert(sizeof(TownNameText) == 0x20 && offsetof(TownNameText, chars) == 0x12, "TownNameText layout");

extern const u8 data_020de67c[]; /* the wide text's vtable */
extern const u8 data_020de694[]; /* the 8-bit text's vtable */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* A new town's number is a random 15-bit number with bit 15 set. */
#define TOWN_NAME_NUMBER_RANGE 0x7fff
#define TOWN_NAME_NUMBER_MADE 0x8000

/* ---- the wide text */

/* func_02064124 (vtable slot 3): the address of the characters. */
int TownNameWideText_Chars(int text)
{
    return text + (int) offsetof(TownNameWideText, chars);
}
CLEAN_AS(func_02064124, TownNameWideText_Chars)

/* func_02064128: the first `count` characters copied to `out`. */
void TownNameWideText_CopyOut(TownNameWideText *text, u16 *out, int count)
{
    MI_CpuCopy8(text->chars, out, (u32) count << 1);
}
CLEAN_AS(func_02064128, TownNameWideText_CopyOut)

/* func_02064134 (vtable slot 2): the capacity. */
int TownNameWideText_Capacity(void)
{
    return TOWN_NAME_LENGTH;
}
CLEAN_AS(func_02064134, TownNameWideText_Capacity)

/* func_02064138 (vtable slot 1): destructs and frees. */
TownNameWideText *TownNameWideText_Delete(TownNameWideText *text)
{
    text->vtable = (const TextVtable *) data_020de67c;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02064138, TownNameWideText_Delete)

/* func_02064158 (vtable slot 0): the destructor. */
TownNameWideText *TownNameWideText_Destruct(TownNameWideText *text)
{
    text->vtable = (const TextVtable *) data_020de67c;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_02064158, TownNameWideText_Destruct)

/* func_02064170: the constructor. */
TownNameWideText *TownNameWideText_Construct(TownNameWideText *text)
{
    TextBase_WideConstruct(text);
    text->vtable = (const TextVtable *) data_020de67c;
    return text;
}
CLEAN_AS(func_02064170, TownNameWideText_Construct)

/* ---- the 8-bit text */

/* func_02064188 (vtable slot 3): the address of the characters. */
int TownNameText_Chars(int text)
{
    return text + (int) offsetof(TownNameText, chars);
}
CLEAN_AS(func_02064188, TownNameText_Chars)

/* func_0206418c (vtable slot 2): the capacity. */
int TownNameText_Capacity(void)
{
    return TOWN_NAME_TEXT_CAPACITY;
}
CLEAN_AS(func_0206418c, TownNameText_Capacity)

/* func_02064190 (vtable slot 1): destructs and frees. */
TownNameText *TownNameText_Delete(TownNameText *text)
{
    text->vtable = (const TextVtable *) data_020de694;
    TextBase_Destruct((TextBase *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02064190, TownNameText_Delete)

/* func_020641b0 (vtable slot 0): the destructor. */
TownNameText *TownNameText_Destruct(TownNameText *text)
{
    text->vtable = (const TextVtable *) data_020de694;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_020641b0, TownNameText_Destruct)

/* func_020641c8: the constructor. */
TownNameText *TownNameText_Construct(TownNameText *text)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020de694;
    return text;
}
CLEAN_AS(func_020641c8, TownNameText_Construct)

/* ---- the town */

/* func_020641e0: the name set from an 8-bit text, through a wide text. */
void TownName_SetNameFromText(TownName *town, TextBase *text)
{
    TownNameWideText wide;
    TownNameWideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) &wide, text);
    TownNameWideText_CopyOut(&wide, town->name, TOWN_NAME_LENGTH);
    TownNameWideText_Destruct(&wide);
}
CLEAN_AS(func_020641e0, TownName_SetNameFromText)

/* func_02064210: the name written into an 8-bit text, through a wide text. */
void TownName_ToText(TownName *town, TextBase *text)
{
    TownNameWideText wide;
    TownNameWideText_Construct(&wide);
    TextBase_SetWide(&wide, town->name, TOWN_NAME_LENGTH);
    TextBase_WideToBytes(text, (WideTextBase *) &wide, 0, 0);
    TownNameWideText_Destruct(&wide);
}
CLEAN_AS(func_02064210, TownName_ToText)

/* func_02064244: a new town: cleared, given the six characters at `name` and a new number. */
void TownName_Make(TownName *town, const u16 *name)
{
    TownName_Clear(town);
    MI_CpuCopy8(name, town->name, sizeof(town->name));
    town->number = TownName_NewNumber(town);
}
CLEAN_AS(func_02064244, TownName_Make)

/* func_0206426c: a new number at random (the town is not read). */
u16 TownName_NewNumber(TownName *town)
{
    (void) town;
    return (u16) (MainRandom_Below(TOWN_NAME_NUMBER_RANGE) | TOWN_NAME_NUMBER_MADE);
}
CLEAN_AS(func_0206426c, TownName_NewNumber)

/* func_02064290: the number set. */
void TownName_SetNumber(u16 *number, int value)
{
    *number = (u16) value;
}
CLEAN_AS(func_02064290, TownName_SetNumber)

/* func_02064294: whether the town has a number. */
unsigned int TownName_IsSet(const u16 *number)
{
    return *number != 0;
}
CLEAN_AS(func_02064294, TownName_IsSet)

/* func_020642a4: the address of the name. */
int TownName_Name(int town)
{
    return town + (int) offsetof(TownName, name);
}
CLEAN_AS(func_020642a4, TownName_Name)

/* func_020642a8: `src` copied to `dst`: the number, then the name. */
void TownName_CopyTo(const u16 *src, u16 *dst)
{
    *dst = *src;
    MI_CpuCopy8(src + 1, dst + 1, TOWN_NAME_LENGTH * sizeof(u16));
}
CLEAN_AS(func_020642a8, TownName_CopyTo)

/* func_020642bc: `src` assigned to `dst`: the number, then the name. */
void TownName_Assign(TownName *dst, const TownName *src)
{
    dst->number = src->number;
    MI_CpuCopy8(src->name, dst->name, sizeof(dst->name));
}
CLEAN_AS(func_020642bc, TownName_Assign)

/* func_020642d0: `src` copied to `dst` in one copy. */
void TownName_Copy(TownName *dst, const TownName *src)
{
    MI_CpuCopy8(src, dst, sizeof(TownName));
}
CLEAN_AS(func_020642d0, TownName_Copy)

/* func_020642e0: no name, then no number. */
void TownName_Clear(TownName *town)
{
    MI_CpuFill8(town->name, 0, sizeof(town->name));
    town->number = 0;
}
CLEAN_AS(func_020642e0, TownName_Clear)

/* func_020642f8: the destructor: nothing to do. */
void TownName_Destruct(void *town)
{
    (void) town;
}
CLEAN_AS(func_020642f8, TownName_Destruct)

/* func_020642fc: the constructor: nothing to do. */
void TownName_Construct(void *town)
{
    (void) town;
}
CLEAN_AS(func_020642fc, TownName_Construct)
