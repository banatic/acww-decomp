/* Maps made of acres: the town (data_021c80c0, 6 x 6 acres built from the town's layout,
 * town_layout.h), the five rooms of the player's house (data_021c80e0, one acre each, from the
 * records at data_021ebcd4), and one map whose single acre gets its items from a villager
 * (data_021c80cc). Each acre is a 0x28-byte record (func_02037f5c builds one); each map has an
 * entry of its own in the table at data_021c31ec (its `slot`), which func_02030ddc sets up and
 * func_02030bac releases.
 *
 * Also here: the item templates the acres' items are filled from (data_021c80c8, four files
 * loaded whole), and the questions "where does building X stand on the map", answered with the
 * tile and the point in front of it. */
#ifndef CLEAN_MAIN_ACRE_MAP_H
#define CLEAN_MAIN_ACRE_MAP_H

#include "autoload_2/vector.h"
#include "types.h"

#define ACRE_MAP_ACRE_SIZE 0x28
#define ACRE_MAP_ROOMS 5

/* The table slots of the maps. */
#define ACRE_MAP_SLOT_TOWN 1
#define ACRE_MAP_SLOT_FIRST_ROOM 2 /* room i takes slot 2 + i */
#define ACRE_MAP_SLOT_VILLAGER 7

/* The item code of an empty tile. */
#define ACRE_MAP_ITEM_NONE 0xfff1

typedef struct AcreMap {
    u8 *acres;      /* 0x00: acres_wide x acres_high records of ACRE_MAP_ACRE_SIZE bytes, row by row */
    int acres_wide; /* 0x04 */
    int acres_high; /* 0x08 */
    int tiles_wide; /* 0x0c: 16 tiles to an acre */
    int tiles_high; /* 0x10 */
    int world_wide; /* 0x14: in world units (data_020ca0ec to an acre) */
    int world_high; /* 0x18: (data_020ca0e8 to an acre) */
    int slot;       /* 0x1c: its entry of the table at data_021c31ec */
} AcreMap;

/* The map whose acre is filled from a villager's record. */
typedef struct AcreMapVillager {
    AcreMap map;
    u16 *items; /* 0x20: the acre's 256 item codes */
} AcreMapVillager;

/* What an acre is built from (func_0204f86c makes an array of them). */
typedef struct AcreMapSource {
    int model;   /* 0x00: the acre's model number */
    u16 *items;  /* 0x04: its 16 x 16 item codes */
    int unk_08;  /* 0x08: always 0 here */
    void *extra; /* 0x0c: the town's 0x20-byte record of the acre, or 0 */
} AcreMapSource;

/* One item template: a file loaded whole and its size in halfwords. */
typedef struct AcreMapTemplate {
    void *data;
    u32 halfwords;
} AcreMapTemplate;

#define ACRE_MAP_TEMPLATES 4

int AcreMap_LoadTemplates(AcreMapTemplate *templates, u32 heap);
void AcreMap_FreeTemplateSet(int heap);
int AcreMap_CreateTemplateSet(int heap);
void AcreMap_ClearTemplates(AcreMapTemplate *templates);

void AcreMap_FreeVillagerMap(int heap);
void AcreMap_ReleaseVillager(AcreMapVillager *map, void *heap);
int AcreMap_CreateVillagerMap(int villager, int heap);
int AcreMap_BuildVillager(AcreMapVillager *map, int villager, int heap);
int AcreMap_FillVillagerItems(void *items, void *villager, void *heap);
AcreMapSource *AcreMap_MakeVillagerSource(int items, int villager, int heap);
void AcreMap_InitVillager(AcreMapVillager *map);

void AcreMap_FreeAcres(void *map, void *heap);
int AcreMap_BuildRoom(AcreMap *map, int room, int heap);
void AcreMap_ReleaseRoomSlot(unsigned int *map);
void AcreMap_LoadRoomData(AcreMap *map);
void AcreMap_LoadRoomsData(void);
void AcreMap_SetRoomModel(int *map, int room);
void AcreMap_SetRoomsModels(void);
void AcreMap_FreeRooms(int heap);
int AcreMap_CreateRooms(void *heap);
int AcreMap_RoomByNumber(int number);
int AcreMap_Room(int room);
void AcreMap_InitRoom(AcreMap *map);

int AcreMap_FindBuilding5020(int map, int position);
int AcreMap_FindBuilding5000Front(int map, int *position, int *tile_x, int *tile_z);
int AcreMap_HasBuilding500b(int map, int position, int tile_x, int tile_z);
int AcreMap_HasBuilding5014(int map, int position, int tile_x, int tile_z);
int AcreMap_HasBuilding5000(int map, int position, int tile_x, int tile_z);
void AcreMap_FindBuildingPoint(u16 *out, void *map, int *position, int *tile_x, int *tile_z, u16 first, u16 last, u32 flags);
void AcreMap_FindItem(u16 *out, void *map, u32 position, int *tile_x, int *tile_z, u16 first, u16 last, u32 flags);
int AcreMap_SetBuildingInAcre(int map, int acre_x, int acre_z, int x, int z, int item);
int AcreMap_SetBuildingAt(int map, int tile_x, int tile_z, int item);
int AcreMap_ClearBuildingAt(int map, int item, int tile_x, int tile_z);

unsigned int AcreMap_Town(void);
void AcreMap_ReleaseTownSlot(AcreMap *map);
void AcreMap_LoadTownData(AcreMap *map);
void AcreMap_SetTownModels(AcreMap *map);
void AcreMap_FreeTownAcres(void *map, void *heap);
int AcreMap_BuildTown(AcreMap *map, int heap);
void AcreMap_FreeTown(void *heap);
int AcreMap_CreateTown(void *heap);
void AcreMap_InitTown(AcreMap *map);

/* A map's size in acres. */
typedef struct AcreMapSize {
    int wide;
    int high;
} AcreMapSize;

int AcreMap_Build(AcreMap *map, AcreMapSource *sources, const AcreMapSize *size, void *heap);
void AcreMap_Release(AcreMap *map, void *heap);
void AcreMap_Init(AcreMap *map);
AcreMapSource *AcreMap_MakeSources(int count, int heap);
void AcreMap_InitSource(AcreMapSource *source);

#endif
