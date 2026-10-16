/* The wide text and the label as long as a memory's texts (villager_memory_text.h). */
#include "villager_memory_text.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(VillagerMemoryWide, text) == 0xe, "wide text characters");
static_assert(sizeof(VillagerMemoryWide) == 0x24, "wide text size");
static_assert(offsetof(VillagerMemoryLabel, text) == 0x12, "label characters");
static_assert(sizeof(VillagerMemoryLabel) == 0x28, "label size");

extern const TextVtable data_020e18ec; /* the wide text's vtable */
extern const TextVtable data_020e191c; /* the label's vtable */

/* The text base's constructors and destructors. */
extern void *func_020a88ec(void *text);  /* base of a wide text */
extern void *func_020a887c(void *text);  /* its destructor */
extern void *func_020a8cac(void *label); /* base of a label */
extern void *func_020a8c38(void *label); /* its destructor */

/* ---- Wide text of 10 characters */

/* func_02081fb0 (vtable entry 3): the address of the characters. */
int VillagerMemoryWide_Buffer(int text)
{
    return (int) ((u32) text + offsetof(VillagerMemoryWide, text));
}
CLEAN_AS(func_02081fb0, VillagerMemoryWide_Buffer)

/* func_02081fb4 (vtable entry 2) */
int VillagerMemoryWide_Capacity(void)
{
    return VILLAGER_MEMORY_WIDE_CAPACITY;
}
CLEAN_AS(func_02081fb4, VillagerMemoryWide_Capacity)

/* func_02081fb8 (vtable entry 1) */
VillagerMemoryWide *VillagerMemoryWide_DestructDelete(VillagerMemoryWide *text)
{
    text->vtable = &data_020e18ec;
    func_020a887c(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02081fb8, VillagerMemoryWide_DestructDelete)

/* func_02081fd8 (vtable entry 0) */
void *VillagerMemoryWide_Destruct(void *text)
{
    ((VillagerMemoryWide *) text)->vtable = &data_020e18ec;
    func_020a887c(text);
    return text;
}
CLEAN_AS(func_02081fd8, VillagerMemoryWide_Destruct)

/* func_02081ff0 */
void *VillagerMemoryWide_Construct(void *text)
{
    func_020a88ec(text);
    ((VillagerMemoryWide *) text)->vtable = &data_020e18ec;
    return text;
}
CLEAN_AS(func_02081ff0, VillagerMemoryWide_Construct)

/* ---- Label of 22 characters */

/* func_02082008 (vtable entry 3): the address of the characters. */
int VillagerMemoryLabel_Buffer(int label)
{
    return (int) ((u32) label + offsetof(VillagerMemoryLabel, text));
}
CLEAN_AS(func_02082008, VillagerMemoryLabel_Buffer)

/* func_0208200c (vtable entry 2) */
int VillagerMemoryLabel_Capacity(void)
{
    return VILLAGER_MEMORY_LABEL_CAPACITY;
}
CLEAN_AS(func_0208200c, VillagerMemoryLabel_Capacity)

/* func_02082010 (vtable entry 1) */
void *VillagerMemoryLabel_DestructDelete(void *label)
{
    ((VillagerMemoryLabel *) label)->vtable = &data_020e191c;
    func_020a8c38(label);
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_02082010, VillagerMemoryLabel_DestructDelete)

/* func_02082030 (vtable entry 0) */
void *VillagerMemoryLabel_Destruct(void *label)
{
    ((VillagerMemoryLabel *) label)->vtable = &data_020e191c;
    func_020a8c38(label);
    return label;
}
CLEAN_AS(func_02082030, VillagerMemoryLabel_Destruct)

/* func_02082048 */
void *VillagerMemoryLabel_Construct(void *label)
{
    func_020a8cac(label);
    ((VillagerMemoryLabel *) label)->vtable = &data_020e191c;
    return label;
}
CLEAN_AS(func_02082048, VillagerMemoryLabel_Construct)
