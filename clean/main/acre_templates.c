/* The item templates the acres' items are filled from (acre_templates.h). */
#include "acre_templates.h"

#include "clean.h"
#include "villager_house_items.h"
#include "villager_roster.h"

static_assert(sizeof(AcreTemplateRecord) == 4, "AcreTemplateRecord");
static_assert(sizeof(AcreMapTemplate) == 8, "AcreMapTemplate");

extern AcreMapTemplate *data_021c80c8; /* the templates, or 0 */
/* Each set's two file numbers: the variants' sizes, and their records. */
extern const u32 data_020cb764[ACRE_MAP_TEMPLATES][2];
extern u8 data_021e5a2c[]; /* the town's villagers (villager_roster.h) */

/* `size` bytes from `offset` in file `file` read into `dst`. */
extern void func_02064828(u32 file, void *dst, int size, int offset);

#define ACRE_TEMPLATES_RECORDS_FILE 1
#define ACRE_TEMPLATES_RECORD_ALIGN 4
#define ACRE_TEMPLATES_ACRE_SIDE 16
#define ACRE_TEMPLATES_ACRE_TILES (ACRE_TEMPLATES_ACRE_SIDE * ACRE_TEMPLATES_ACRE_SIDE)
/* What a villager's house items use when the villager names no template. */
#define ACRE_TEMPLATES_VILLAGER_SET 2
#define ACRE_TEMPLATES_VILLAGER_VARIANT 0

/* Halfword `index` of a template's first file (any index, as the game reads it). */
static u16 acre_templates_halfword(const void *data, int index)
{
    return *(const u16 *) ((uintptr_t) data + (uintptr_t) (u32) index * 2u);
}

static int acre_templates_is_set(const AcreMapTemplate *templates, int set)
{
    return AcreTemplates_IsSet((int) (uintptr_t) templates, set);
}

/* func_0204d624: the template records of villager `villager`'s house items, from `heap`, their
 * number to *count; 0 without templates. */
int AcreTemplates_VillagerRecords(int *count, int villager, int heap)
{
    if (data_021c80c8 == NULL) {
        return 0;
    }
    return AcreTemplates_VillagerRecordsFrom(data_021c80c8, count, villager, heap);
}
CLEAN_AS(func_0204d624, AcreTemplates_VillagerRecords)

/* func_0204d650: the same from `templates`: the set and variant the villager's record names
 * (VillagerHouseItems_Template; set 2, variant 0 when it names none); 0 for no villager. */
int AcreTemplates_VillagerRecordsFrom(AcreMapTemplate *templates, int *count, int villager, int heap)
{
    u8 *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
    int set = ACRE_TEMPLATES_VILLAGER_SET;
    int variant = ACRE_TEMPLATES_VILLAGER_VARIANT;
    if (record != NULL && VillagerHouseItems_Template(record, &set, &variant)) {
        return (int) (uintptr_t) AcreTemplates_LoadRecords(templates, count, set, variant, (Heap *) (uintptr_t) heap);
    }
    return 0;
}
CLEAN_AS(func_0204d650, AcreTemplates_VillagerRecordsFrom)

/* func_0204d698: the records of a variant read into a block from `heap` (aligned to 4), their
 * number to *count; 0 (the block freed) when the variant has none, its size is not a whole
 * number of records or the set does not exist. */
AcreTemplateRecord *AcreTemplates_LoadRecords(AcreMapTemplate *templates, int *count, int set, int variant, Heap *heap)
{
    int size = AcreTemplates_Size(templates, set, variant);
    if (size <= 0 || size % (int) sizeof(AcreTemplateRecord) != 0 || !acre_templates_is_set(templates, set)) {
        return NULL;
    }
    AcreTemplateRecord *records = Heap_AllocAligned(heap, size, ACRE_TEMPLATES_RECORD_ALIGN);
    if (records == NULL) {
        return NULL;
    }
    if (AcreTemplates_Read(templates, records, set, variant, size)) {
        *count = size / (int) sizeof(AcreTemplateRecord);
        return records;
    }
    Heap_Free(heap, records);
    return NULL;
}
CLEAN_AS(func_0204d698, AcreTemplates_LoadRecords)

/* func_0204d708: the records of a variant put into `items` (an acre's 16 x 16 codes, row by
 * row), read into a block from the back of `heap` that is freed after. Whether the block was
 * made (0 also without `items`, when the variant has no whole records or the set does not
 * exist). */
int AcreTemplates_Fill(AcreMapTemplate *templates, u16 *items, int set, int variant, Heap *heap)
{
    int size = AcreTemplates_Size(templates, set, variant);
    if (items == NULL || size <= 0 || size % (int) sizeof(AcreTemplateRecord) != 0 || !acre_templates_is_set(templates, set)) {
        return 0;
    }
    AcreTemplateRecord *records = Heap_AllocBack(heap, size);
    if (records == NULL) {
        return 0;
    }
    if (AcreTemplates_Read(templates, records, set, variant, size)) {
        int count = size / (int) sizeof(AcreTemplateRecord);
        for (int i = 0; i < count; i++) {
            const AcreTemplateRecord *record = &records[i];
            if (record->x < ACRE_TEMPLATES_ACRE_SIDE && record->z < ACRE_TEMPLATES_ACRE_SIDE) {
                items[record->z * ACRE_TEMPLATES_ACRE_SIDE + record->x] = record->item;
            }
        }
    }
    Heap_Free(heap, records);
    return 1;
}
CLEAN_AS(func_0204d708, AcreTemplates_Fill)

/* func_0204d7a8: an acre's items (all empty, from `heap` aligned to `align`) filled from a
 * variant; 0 (the items freed) when they cannot be, or without templates. */
int AcreTemplates_NewItems(int set, int variant, int heap, int align)
{
    if (data_021c80c8 == NULL) {
        return 0;
    }
    u16 *items = AcreTemplates_EmptyItems(heap, align);
    if (items != NULL && !AcreTemplates_Fill(data_021c80c8, items, set, variant, (Heap *) (uintptr_t) heap)) {
        Heap_Free((Heap *) (uintptr_t) heap, items);
        items = NULL;
    }
    return (int) (uintptr_t) items;
}
CLEAN_AS(func_0204d7a8, AcreTemplates_NewItems)

/* func_0204d7f8: AcreTemplates_Fill on the templates; 0 without them. */
int AcreTemplates_FillItems(int items, int set, int variant, int heap)
{
    if (data_021c80c8 == NULL) {
        return 0;
    }
    return AcreTemplates_Fill(data_021c80c8, (u16 *) (uintptr_t) (u32) items, set, variant, (Heap *) (uintptr_t) heap);
}
CLEAN_AS(func_0204d7f8, AcreTemplates_FillItems)

/* func_0204d828: `size` bytes of the variant's records read from the set's second file, from
 * the variant's offset (AcreTemplates_Offset). Always 1.
 * REQUIRES: 0 <= set < 4 (its callers check it with AcreTemplates_IsSet). */
int AcreTemplates_Read(AcreMapTemplate *templates, void *dst, int set, int variant, int size)
{
    int offset = AcreTemplates_Offset(templates, set, variant);
    func_02064828(data_020cb764[set][ACRE_TEMPLATES_RECORDS_FILE], dst, size, offset);
    return 1;
}
CLEAN_AS(func_0204d828, AcreTemplates_Read)

/* func_0204d858: an acre's 256 item codes from `heap` (aligned to `align`), all empty
 * (0xfff1); 0 when the heap is full. */
u16 *AcreTemplates_EmptyItems(int heap, int align)
{
    u16 *items = Heap_AllocAligned((Heap *) (uintptr_t) heap, ACRE_TEMPLATES_ACRE_TILES * sizeof(u16), align);
    if (items != NULL) {
        for (int i = 0; i < ACRE_TEMPLATES_ACRE_TILES; i++) {
            items[i] = ACRE_MAP_ITEM_NONE;
        }
    }
    return items;
}
CLEAN_AS(func_0204d858, AcreTemplates_EmptyItems)

/* func_0204d888: whether the templates are loaded and the variant has records. */
int AcreTemplates_HasVariant(int set, int variant)
{
    if (data_021c80c8 == NULL) {
        return 0;
    }
    return AcreTemplates_Size(data_021c80c8, set, variant) > 0;
}
CLEAN_AS(func_0204d888, AcreTemplates_HasVariant)

/* func_0204d8b0: the size in bytes of a variant's records (its halfword in the set's first
 * file); 0 for a set that does not exist or is not loaded, or a variant past the file. */
u16 AcreTemplates_Size(const AcreMapTemplate *templates, int set, int variant)
{
    if (!acre_templates_is_set(templates, set)) {
        return 0;
    }
    const AcreMapTemplate *entry = &templates[set];
    if (entry->data == NULL || variant >= (int) entry->halfwords) {
        return 0;
    }
    return acre_templates_halfword(entry->data, variant);
}
CLEAN_AS(func_0204d8b0, AcreTemplates_Size)

/* func_0204d8e4: the offset of a variant's records in the set's second file: the sizes of the
 * variants before it; 0 as for AcreTemplates_Size. */
int AcreTemplates_Offset(const AcreMapTemplate *templates, int set, int variant)
{
    u32 offset = 0;
    if (!acre_templates_is_set(templates, set)) {
        return 0;
    }
    const AcreMapTemplate *entry = &templates[set];
    if (entry->data != NULL && variant < (int) entry->halfwords) {
        for (int i = 0; i < variant; i++) {
            offset += acre_templates_halfword(entry->data, i);
        }
    }
    return (int) offset;
}
CLEAN_AS(func_0204d8e4, AcreTemplates_Offset)

/* func_0204d924: whether `set` is one of the four sets.
 * QUIRK: `templates` is not used. */
int AcreTemplates_IsSet(int templates, int set)
{
    (void) templates;
    return set >= 0 && set < ACRE_MAP_TEMPLATES;
}
CLEAN_AS(func_0204d924, AcreTemplates_IsSet)

/* func_0204d934: the sets' first files freed to `heap`.
 * QUIRK: it only steps to the next set after freeing one, so it stops at the first set that is
 * not loaded; AcreMap_LoadTemplates leaves every set after a failed one unloaded, so nothing is
 * left behind. */
void AcreTemplates_FreeAll(AcreMapTemplate *templates, int heap)
{
    AcreMapTemplate *entry = templates;
    for (int i = 0; i < ACRE_MAP_TEMPLATES; i++) {
        if (entry->data != NULL) {
            Heap_Free((Heap *) (uintptr_t) heap, entry->data);
            entry->data = NULL;
            entry->halfwords = 0;
            entry++;
        }
    }
}
CLEAN_AS(func_0204d934, AcreTemplates_FreeAll)
