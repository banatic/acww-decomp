/* The item templates the acres' items are filled from (data_021c80c8, AcreMapTemplate of
 * acre_map.h; AcreMap_CreateTemplateSet loads them). There are four sets, each two files
 * (data_020cb764): the first, loaded whole, is a list of halfwords, the size in bytes of each
 * variant's records; the second holds the records of every variant one after the other, read
 * a variant at a time. A record is four bytes (AcreTemplateRecord): an item code and the tile
 * of the acre it goes on.
 *
 * Set 0 serves the outdoor scenes and set 1 the rooms (scene_map.h); a villager's house items
 * name their set and variant (VillagerHouseItems_Template, set 2 by default). */
#ifndef CLEAN_MAIN_ACRE_TEMPLATES_H
#define CLEAN_MAIN_ACRE_TEMPLATES_H

#include "acre_map.h"
#include "autoload_2/heap.h"
#include "types.h"

/* One record of a template: item `item` on tile (x, z) of the acre (records with a tile past
 * 15 are skipped). */
typedef struct AcreTemplateRecord {
    u16 item;
    u8 x;
    u8 z;
} AcreTemplateRecord;

int AcreTemplates_VillagerRecords(int *count, int villager, int heap);
int AcreTemplates_VillagerRecordsFrom(AcreMapTemplate *templates, int *count, int villager, int heap);
AcreTemplateRecord *AcreTemplates_LoadRecords(AcreMapTemplate *templates, int *count, int set, int variant, Heap *heap);
int AcreTemplates_Fill(AcreMapTemplate *templates, u16 *items, int set, int variant, Heap *heap);
int AcreTemplates_NewItems(int set, int variant, int heap, int align);
int AcreTemplates_FillItems(int items, int set, int variant, int heap);
int AcreTemplates_Read(AcreMapTemplate *templates, void *dst, int set, int variant, int size);
u16 *AcreTemplates_EmptyItems(int heap, int align);
int AcreTemplates_HasVariant(int set, int variant);
u16 AcreTemplates_Size(const AcreMapTemplate *templates, int set, int variant);
int AcreTemplates_Offset(const AcreMapTemplate *templates, int set, int variant);
int AcreTemplates_IsSet(int templates, int set);
void AcreTemplates_FreeAll(AcreMapTemplate *templates, int heap);

#endif
