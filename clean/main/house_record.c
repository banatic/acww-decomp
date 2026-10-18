/* The record of the player's house (house_record.h). */
#include "house_record.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "room_cells.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "state_block.h"
#include "map_code.h"

static_assert(sizeof(HouseRoom) == 0x450, "HouseRoom");
static_assert(offsetof(HouseRoom, wallpaper) == 0x448 && offsetof(HouseRoom, flags) == 0x44e, "HouseRoom");
static_assert(offsetof(HouseRecord, loan) == 0x1590, "HouseRecord.loan");
static_assert(offsetof(HouseRecord, songs) == 0x1594, "HouseRecord.songs");
static_assert(offsetof(HouseRecord, bits) == 0x15a0, "HouseRecord.bits");
static_assert(sizeof(HouseRecord) == 0x10ad0 - 0xf52c, "HouseRecord");

/* The state block's flag set while an extension built overnight is not yet announced. */
#define HOUSE_RECORD_FLAG_JUST_BUILT 13
/* The house's codes on the town's map (0x5014 + size), and the acres to look for it in. */
#define HOUSE_RECORD_MAP_CODE_FIRST 0x5014
#define HOUSE_RECORD_MAP_CODE_LAST 0x501a
#define HOUSE_RECORD_MAP_ACRE_FLAGS 1
/* The models when the size or the room is none (HouseRecord_SizeModel, HouseRecord_RoomModel). */
#define HOUSE_RECORD_NO_SIZE_MODEL 0x1003
#define HOUSE_RECORD_NO_ROOM_MODEL 0x1002
/* The days of an absence that raise nothing. */
#define HOUSE_RECORD_ABSENCE_FREE_DAYS 6

/* The firmware's owner info, as the SDK's OS_GetOwnerInfo copies it. */
typedef struct HouseRecordOwnerInfo {
    u8 language;
    u8 favorite_color; /* 0-15 */
    u8 birthday[2];
    u16 nickname[10];
    u16 nickname_length;
    u16 comment[26];
    u16 comment_length;
} HouseRecordOwnerInfo;

extern HouseRecord data_021ebcd4;                   /* the house */
extern u8 data_021ed268[HOUSE_RECORD_SONG_BYTES];   /* its songs (data_021ebcd4.songs) */
extern StateBlock data_021dc7a8;                    /* the state block */
extern const int data_020cc9d0[HOUSE_RECORD_SIZES]; /* the loan of the extension from each size */
extern const u16 data_020cc9c0[HOUSE_RECORD_SIZES]; /* a model number by size */
extern const u16 data_020cc9ec[];                   /* the rooms' models: 5 by size */
/* The code of no song HouseRecord_Song answers for a scene without a room: a function-local
 * static of the original, set up the first time (bit 0 of its guard) and registered for
 * destruction with the item code's destructor. */
extern u16 data_021cb4f4;
extern u32 data_021cb4fc;
extern u8 data_021cb564[];

extern void OS_GetOwnerInfo(HouseRecordOwnerInfo *info);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *record);
/* The item code's destructor (nothing to do). */
extern void func_020051b0(void *code);
/* A room record's constructor and destructor, which the array helpers are handed. */
extern void *func_02061470(void *room);
extern void *func_02061444(void *room);

static unsigned int house_record_field(const HouseRecord *house, int shift, u32 mask)
{
    return (house->bits.word >> shift) & mask;
}

static void house_record_set_field(HouseRecord *house, int shift, u32 mask, u32 value)
{
    house->bits.word = (house->bits.word & ~(mask << shift)) | ((value & mask) << shift);
}

/* func_02060974: no song kept. */
void HouseRecord_ClearSongs(u8 *songs)
{
    for (unsigned int i = 0; i < HOUSE_RECORD_SONG_BYTES; i++) {
        songs[i] = 0;
    }
}
CLEAN_AS(func_02060974, HouseRecord_ClearSongs)

/* func_02060984: song item `item` taken out of the house's songs; nothing for another item. */
void HouseRecord_RemoveSong(unsigned int item)
{
    if (item < HOUSE_RECORD_SONG_FIRST || item > HOUSE_RECORD_SONG_LAST) {
        return;
    }
    HouseRecord_ClearSongBit(data_021ed268, item - HOUSE_RECORD_SONG_FIRST);
}
CLEAN_AS(func_02060984, HouseRecord_RemoveSong)

/* func_020609bc: bit `song` of the songs cleared; nothing past the songs. */
void HouseRecord_ClearSongBit(u8 *songs, unsigned int song)
{
    if (song < HOUSE_RECORD_SONGS) {
        songs[song >> 3] &= (u8) ~(1u << (song & 7));
    }
}
CLEAN_AS(func_020609bc, HouseRecord_ClearSongBit)

/* func_020609dc: song item `item` added to the house's songs; nothing for another item. */
void HouseRecord_AddSong(unsigned int item)
{
    if (item >= HOUSE_RECORD_SONG_FIRST && item <= HOUSE_RECORD_SONG_LAST) {
        HouseRecord_SetSongBit(data_021ed268, item - HOUSE_RECORD_SONG_FIRST);
    }
}
CLEAN_AS(func_020609dc, HouseRecord_AddSong)

/* func_02060a14: bit `song` of the songs set; nothing past the songs. */
void HouseRecord_SetSongBit(u8 *songs, unsigned int song)
{
    if (song < HOUSE_RECORD_SONGS) {
        songs[song >> 3] |= (u8) (1u << (song & 7));
    }
}
CLEAN_AS(func_02060a14, HouseRecord_SetSongBit)

/* func_02060a34: whether the house keeps song item `item`; 0 for another item. */
int HouseRecord_HasSong(unsigned int item)
{
    if (item >= HOUSE_RECORD_SONG_FIRST && item <= HOUSE_RECORD_SONG_LAST) {
        return HouseRecord_TestSongBit(data_021ed268, item - HOUSE_RECORD_SONG_FIRST);
    }
    return 0;
}
CLEAN_AS(func_02060a34, HouseRecord_HasSong)

/* func_02060a70: whether bit `song` of the songs is set; 0 past the songs. */
int HouseRecord_TestSongBit(const u8 *songs, unsigned int song)
{
    if (song < HOUSE_RECORD_SONGS) {
        return (songs[song >> 3] >> (song & 7)) & 1;
    }
    return 0;
}
CLEAN_AS(func_02060a70, HouseRecord_TestSongBit)

/* func_02060a90: the songs' destructor, which does nothing. */
void HouseRecord_DestructSongs(int songs)
{
    (void) songs;
}
CLEAN_AS(func_02060a90, HouseRecord_DestructSongs)

/* func_02060a94: the songs' constructor, which does nothing. */
void HouseRecord_ConstructSongs(void *songs)
{
    (void) songs;
}
CLEAN_AS(func_02060a94, HouseRecord_ConstructSongs)

/* func_02060a98: HouseRecord_SongPlayedElsewhere for the current scene. */
int HouseRecord_CurrentSongPlayedElsewhere(const u16 *song)
{
    return HouseRecord_SongPlayedElsewhere(SceneQuery_Current(), song);
}
CLEAN_AS(func_02060a98, HouseRecord_CurrentSongPlayedElsewhere)

/* func_02060aac: whether a room of the house other than scene `scene`'s plays *song; 0 when
 * the scene is not a room of the house. */
int HouseRecord_SongPlayedElsewhere(int scene, const u16 *song)
{
    HouseRecord *house = &data_021ebcd4;
    HouseRoom *room = HouseRecord_RoomOfScene(house, scene);
    if (room == NULL) {
        return 0;
    }
    for (int i = 0; i < HOUSE_RECORD_ROOMS; i++) {
        HouseRoom *other = HouseRecord_Room(house, i);
        if (other != room && *HouseRecord_RoomSong(other) == *song) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02060aac, HouseRecord_SongPlayedElsewhere)

/* func_02060afc: the current scene's room plays no song. */
void HouseRecord_StopCurrentSong(void)
{
    u16 none = HOUSE_RECORD_NO_ITEM;
    HouseRecord_SetCurrentSong(&none);
}
CLEAN_AS(func_02060afc, HouseRecord_StopCurrentSong)

/* func_02060b18: scene `scene`'s room plays no song; whether the scene has a room. */
int HouseRecord_StopSong(int scene)
{
    u16 none = HOUSE_RECORD_NO_ITEM;
    return HouseRecord_SetSong(scene, &none);
}
CLEAN_AS(func_02060b18, HouseRecord_StopSong)

/* func_02060b34: HouseRecord_SetSong for the current scene. */
int HouseRecord_SetCurrentSong(const u16 *song)
{
    return HouseRecord_SetSong(SceneQuery_Current(), song);
}
CLEAN_AS(func_02060b34, HouseRecord_SetCurrentSong)

/* func_02060b48: scene `scene`'s room plays *song; whether the scene has a room. */
int HouseRecord_SetSong(int scene, const u16 *song)
{
    HouseRoom *room = HouseRecord_RoomOfScene(&data_021ebcd4, scene);
    if (room != NULL) {
        HouseRecord_RoomSetSong(room, song);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02060b48, HouseRecord_SetSong)

/* func_02060b70: HouseRecord_Song for the current scene. */
u16 *HouseRecord_CurrentSong(void)
{
    return HouseRecord_Song(SceneQuery_Current());
}
CLEAN_AS(func_02060b70, HouseRecord_CurrentSong)

/* func_02060b84: the song scene `scene`'s room plays, or a code of no song when the scene is
 * not a room of the house. */
u16 *HouseRecord_Song(int scene)
{
    HouseRoom *room = HouseRecord_RoomOfScene(&data_021ebcd4, scene);
    if (room != NULL) {
        return HouseRecord_RoomSong(room);
    }
    if (!(data_021cb4fc & 1)) {
        data_021cb4f4 = HOUSE_RECORD_NO_ITEM;
        __register_global_object(&data_021cb4f4, (void *) (uintptr_t) func_020051b0, data_021cb564);
        data_021cb4fc |= 1;
    }
    return &data_021cb4f4;
}
CLEAN_AS(func_02060b84, HouseRecord_Song)

/* func_02060be0: whether any room has its lights on. */
int HouseRecord_AnyLit(const HouseRecord *house)
{
    return house_record_field(house, HOUSE_RECORD_LIT_SHIFT, HOUSE_RECORD_LIT_MASK) != 0;
}
CLEAN_AS(func_02060be0, HouseRecord_AnyLit)

/* func_02060bf8: scene `scene`'s room's lights turned on (`lit`) or off; whether the scene is
 * a room of the house. */
int HouseRecord_SetLit(HouseRecord *house, int scene, int lit)
{
    unsigned int bit = HouseRecord_LitBit((unsigned int) scene);
    if (bit == 0) {
        return 0;
    }
    unsigned int rooms = house_record_field(house, HOUSE_RECORD_LIT_SHIFT, HOUSE_RECORD_LIT_MASK);
    rooms = lit ? rooms | bit : rooms & ~bit;
    house_record_set_field(house, HOUSE_RECORD_LIT_SHIFT, HOUSE_RECORD_LIT_MASK, rooms);
    return 1;
}
CLEAN_AS(func_02060bf8, HouseRecord_SetLit)

/* func_02060c60: scene `scene`'s room's bit (1 << room), 0 when it is not a room of the house.
 * QUIRK: the shift is the ARM's by a register (by its low byte; 32 and over give 0), kept to a
 * byte. */
unsigned char HouseRecord_LitBit(unsigned int scene)
{
    int room = SceneKinds_HouseRoomIndex(scene);
    if (room == -1) {
        return 0;
    }
    unsigned int shift = (unsigned int) room & 0xff;
    return (unsigned char) (shift < 32 ? 1u << shift : 0);
}
CLEAN_AS(func_02060c60, HouseRecord_LitBit)

/* func_02060c80: the next extension ordered (HouseRecord_Order) with look `look`; whether it
 * was. */
int HouseRecord_OrderWithLook(HouseRecord *house, int look)
{
    if (HouseRecord_Order(house)) {
        house_record_set_field(house, HOUSE_RECORD_ORDERED_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK, (u32) look);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02060c80, HouseRecord_OrderWithLook)

/* func_02060cbc: whether an extension was built and its loan is still to be announced: no
 * extension ordered, nothing owed and the state block's flag 13 set. */
int HouseRecord_JustBuilt(HouseRecord *house)
{
    unsigned int size = HouseRecord_Size(house);
    if (house_record_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK) != size) {
        return 0;
    }
    if (HouseRecord_Loan(house) != 0) {
        return 0;
    }
    return StateBlock_TestFlag((u32 *) &data_021dc7a8, HOUSE_RECORD_FLAG_JUST_BUILT);
}
CLEAN_AS(func_02060cbc, HouseRecord_JustBuilt)

/* func_02060cf4: once nothing is owed, the loan of the house's size's extension. */
void HouseRecord_TakeNextLoan(HouseRecord *house)
{
    if (HouseRecord_Loan(house) != 0) {
        return;
    }
    unsigned int size = HouseRecord_Size(house);
    if (size >= HOUSE_RECORD_SIZES) {
        return;
    }
    HouseRecord_SetLoan(house, data_020cc9d0[size]);
}
CLEAN_AS(func_02060cf4, HouseRecord_TakeNextLoan)

/* func_02060d24: the loan, 0 for a negative amount. */
void HouseRecord_SetLoan(HouseRecord *house, int loan)
{
    house->loan = loan < 0 ? 0 : loan;
}
CLEAN_AS(func_02060d24, HouseRecord_SetLoan)

/* func_02060d3c */
int HouseRecord_Loan(const HouseRecord *house)
{
    return house->loan;
}
CLEAN_AS(func_02060d3c, HouseRecord_Loan)

/* func_02060d48: an absence of `days` days raises the house's cockroach count by the days past
 * six, to at most 10.
 * QUIRK: the sum is the ARM's 32-bit one; a count wrapped negative by an absurd number of days
 * is kept, as its low byte. */
void HouseRecord_AddRoachesForAbsence(HouseRecord *house, int days)
{
    if (days > HOUSE_RECORD_ABSENCE_FREE_DAYS) {
        int count = (int) ((u32) house->bits.bytes[HOUSE_RECORD_ROACHES_BYTE] + (u32) (days - HOUSE_RECORD_ABSENCE_FREE_DAYS));
        if (count > HOUSE_RECORD_MAX_ROACHES) {
            count = HOUSE_RECORD_MAX_ROACHES;
        }
        house->bits.bytes[HOUSE_RECORD_ROACHES_BYTE] = (u8) count;
    }
}
CLEAN_AS(func_02060d48, HouseRecord_AddRoachesForAbsence)

/* func_02060d64 */
void HouseRecord_SetRoaches(HouseRecord *house, unsigned char count)
{
    house->bits.bytes[HOUSE_RECORD_ROACHES_BYTE] = count;
}
CLEAN_AS(func_02060d64, HouseRecord_SetRoaches)

/* func_02060d70 */
unsigned char HouseRecord_Roaches(const HouseRecord *house)
{
    return house->bits.bytes[HOUSE_RECORD_ROACHES_BYTE];
}
CLEAN_AS(func_02060d70, HouseRecord_Roaches)

/* func_02060d7c: the model number the house's size gives (0x1003 for sizes 0-2, 0x1008 from
 * 3), 0x1003 past the sizes.
 * QUIRK: the argument is not used; it is always the house at data_021ebcd4. */
unsigned short HouseRecord_SizeModel(void *unused)
{
    (void) unused;
    int size = (int) HouseRecord_Size(&data_021ebcd4);
    if (size < HOUSE_RECORD_SIZES) {
        return data_020cc9c0[size];
    }
    return HOUSE_RECORD_NO_SIZE_MODEL;
}
CLEAN_AS(func_02060d7c, HouseRecord_SizeModel)

/* func_02060da8: the model of room `room` (0-4) at the house's size; 0x1002 for room -1 or
 * past the sizes.
 * QUIRK: the first argument is not used; it is always the house at data_021ebcd4.
 * REQUIRES: room is -1 or 0-4; another reads past its size's row of the table. */
unsigned short HouseRecord_RoomModel(int unused, int room)
{
    (void) unused;
    if (room == -1) {
        return HOUSE_RECORD_NO_ROOM_MODEL;
    }
    int size = (int) HouseRecord_Size(&data_021ebcd4);
    if (size >= HOUSE_RECORD_SIZES) {
        return HOUSE_RECORD_NO_ROOM_MODEL;
    }
    return data_020cc9ec[size * HOUSE_RECORD_ROOMS + room];
}
CLEAN_AS(func_02060da8, HouseRecord_RoomModel)

/* func_02060de4: the house's look (0-15, the low nibble of `look`); always 1. */
int HouseRecord_SetLook(HouseRecord *house, unsigned char look)
{
    house_record_set_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK, look);
    return 1;
}
CLEAN_AS(func_02060de4, HouseRecord_SetLook)

/* func_02060e10: the look shown (0-15). */
unsigned int HouseRecord_ShownLook(const HouseRecord *house)
{
    return house_record_field(house, HOUSE_RECORD_SHOWN_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK);
}
CLEAN_AS(func_02060e10, HouseRecord_ShownLook)

/* func_02060e28: the next extension ordered (the size ordered one more than the size), when
 * none is and the house is not at its last size; whether it was. The size is read anew for
 * each of the three uses, as in the original. */
int HouseRecord_Order(HouseRecord *house)
{
    unsigned int size = HouseRecord_Size(house);
    if (house_record_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK) != size) {
        return 0;
    }
    if ((int) HouseRecord_Size(house) >= HOUSE_RECORD_LAST_SIZE) {
        return 0;
    }
    u8 ordered = (u8) (HouseRecord_Size(house) + 1);
    house_record_set_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK, ordered);
    return 1;
}
CLEAN_AS(func_02060e28, HouseRecord_Order)

/* func_02060e78: the house's size (0-6). */
unsigned int HouseRecord_Size(const HouseRecord *house)
{
    return house_record_field(house, HOUSE_RECORD_SIZE_SHIFT, HOUSE_RECORD_SIZE_MASK);
}
CLEAN_AS(func_02060e78, HouseRecord_Size)

/* func_02060e88: whether an extension is ordered (the size ordered is not the size). */
int HouseRecord_IsExtending(const HouseRecord *house)
{
    unsigned int size = HouseRecord_Size(house);
    return house_record_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK) != size;
}
CLEAN_AS(func_02060e88, HouseRecord_IsExtending)

/* func_02060eac: room `room`'s acre map source, from `heap`, with the room's model; NULL when
 * there is no such room or no room for it. */
AcreMapSource *HouseRecord_RoomSource(HouseRecord *house, int room, int heap)
{
    AcreMapSource *source = NULL;
    HouseRoom *record = HouseRecord_Room(house, room);
    if (record != NULL) {
        source = HouseRecord_RoomMakeSource(record, heap);
        if (source != NULL) {
            source->model = HouseRecord_RoomModel((int) (uintptr_t) house, room);
        }
    }
    return source;
}
CLEAN_AS(func_02060eac, HouseRecord_RoomSource)

/* func_02060ee0: room `room`'s record, NULL past the rooms. */
HouseRoom *HouseRecord_Room(HouseRecord *house, int room)
{
    if (HouseRecord_IsRoom(room)) {
        return &house->rooms[room];
    }
    return NULL;
}
CLEAN_AS(func_02060ee0, HouseRecord_Room)

/* func_02060f04: scene `scene`'s room's record, NULL when the scene is not a room of the
 * house. */
HouseRoom *HouseRecord_RoomOfScene(HouseRecord *house, int scene)
{
    if (SceneKinds_IsHouseRoom((unsigned int) scene)) {
        return HouseRecord_Room(house, SceneKinds_HouseRoomIndex((unsigned int) scene));
    }
    return NULL;
}
CLEAN_AS(func_02060f04, HouseRecord_RoomOfScene)

/* func_02060f30: whether `room` is one of the five. */
int HouseRecord_IsRoom(int room)
{
    return room >= 0 && room < HOUSE_RECORD_ROOMS;
}
CLEAN_AS(func_02060f30, HouseRecord_IsRoom)

/* func_02060f40: the first loan, and no cockroaches. */
void HouseRecord_Reset(HouseRecord *house)
{
    house->loan = HOUSE_RECORD_FIRST_LOAN;
    house->bits.bytes[HOUSE_RECORD_ROACHES_BYTE] = 0;
}
CLEAN_AS(func_02060f40, HouseRecord_Reset)

/* func_02060f5c, on a new day: the look shown becomes the house's look; then an extension
 * ordered is built when the house's code on the town's map can take the new size: the size
 * becomes the size ordered, the look (and the look shown) the look ordered, the rooms get
 * their models and data again and the state block's flag 13 is set. */
void HouseRecord_Build(HouseRecord *house)
{
    unsigned int look = house_record_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK);
    if (house_record_field(house, HOUSE_RECORD_SHOWN_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK) != look) {
        house_record_set_field(house, HOUSE_RECORD_SHOWN_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK, look);
    }
    unsigned int ordered = house_record_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK);
    if (ordered == HouseRecord_Size(house)) {
        return;
    }
    if (!HouseRecord_PlaceOnMap((int) ordered)) {
        return;
    }
    house_record_set_field(house, HOUSE_RECORD_SIZE_SHIFT, HOUSE_RECORD_SIZE_MASK,
                           house_record_field(house, HOUSE_RECORD_ORDERED_SHIFT, HOUSE_RECORD_ORDERED_MASK));
    house_record_set_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK,
                           house_record_field(house, HOUSE_RECORD_ORDERED_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK));
    house_record_set_field(house, HOUSE_RECORD_SHOWN_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK,
                           house_record_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK));
    AcreMap_SetRoomsModels();
    AcreMap_LoadRoomsData();
    StateBlock_SetFlag((u32 *) &data_021dc7a8, HOUSE_RECORD_FLAG_JUST_BUILT);
}
CLEAN_AS(func_02060f5c, HouseRecord_Build)

/* func_02061008: the house's tile on the town's map (the first code 0x5014-0x501a in layer 0
 * of an acre with flag 1) given the code of size `size`; whether it was found and set. */
int HouseRecord_PlaceOnMap(int size)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    u16 first = HOUSE_RECORD_MAP_CODE_FIRST;
    u16 last = HOUSE_RECORD_MAP_CODE_LAST;
    int acre_x;
    int acre_z;
    int x;
    int z;
    if (AcreTile_FindItemAnyFlag(map, &acre_x, &acre_z, &x, &z, &first, &last, HOUSE_RECORD_MAP_ACRE_FLAGS, 0)) {
        int tile_x;
        int tile_z;
        AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
        u16 code = MapCode_PlayerHouse((unsigned int) size);
        if (AcreTile_SetItem(map, &code, tile_x, tile_z, 0)) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02061008, HouseRecord_PlaceOnMap)

/* func_0206108c: a new house: each room set up, size 0, no song, and the look (and the look
 * shown) the console owner's favourite colour; no look ordered.
 * QUIRK: the size ordered is left as it was. */
void HouseRecord_Init(HouseRecord *house)
{
    HouseRecordOwnerInfo info;

    for (int i = 0; i < HOUSE_RECORD_ROOMS; i++) {
        HouseRecord_RoomInit(&house->rooms[i], i);
    }
    house_record_set_field(house, HOUSE_RECORD_SIZE_SHIFT, HOUSE_RECORD_SIZE_MASK, 0);
    HouseRecord_ClearSongs(house->songs);
    OS_GetOwnerInfo(&info);
    house_record_set_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK, info.favorite_color);
    house_record_set_field(house, HOUSE_RECORD_SHOWN_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK,
                           house_record_field(house, HOUSE_RECORD_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK));
    house_record_set_field(house, HOUSE_RECORD_ORDERED_LOOK_SHIFT, HOUSE_RECORD_LOOK_MASK, 0);
}
CLEAN_AS(func_0206108c, HouseRecord_Init)

/* func_02061118: the destructor: the songs, then the rooms. Returns the house. */
HouseRecord *HouseRecord_Destruct(HouseRecord *house)
{
    HouseRecord_DestructSongs((int) (uintptr_t) house->songs);
    __cxa_vec_cleanup(house->rooms, HOUSE_RECORD_ROOMS, sizeof(HouseRoom), (void (*)(void *))(uintptr_t) func_02061444);
    return house;
}
CLEAN_AS(func_02061118, HouseRecord_Destruct)

/* func_02061144: the constructor: the rooms, then the songs. Returns the house. */
HouseRecord *HouseRecord_Construct(HouseRecord *house)
{
    __cxa_vec_ctor(house->rooms, HOUSE_RECORD_ROOMS, sizeof(HouseRoom), (void (*)(void *))(uintptr_t) func_02061470,
                   (void (*)(void *))(uintptr_t) func_02061444);
    HouseRecord_ConstructSongs(house->songs);
    return house;
}
CLEAN_AS(func_02061144, HouseRecord_Construct)

/* func_0206117c */
void HouseRecord_RoomSetSong(HouseRoom *room, const u16 *song)
{
    room->song = *song;
}
CLEAN_AS(func_0206117c, HouseRecord_RoomSetSong)

/* func_02061188 */
u16 *HouseRecord_RoomSong(HouseRoom *room)
{
    return &room->song;
}
CLEAN_AS(func_02061188, HouseRecord_RoomSong)

/* func_02061194: the room's carpet and its flag (bit 0 of `flag`). */
void HouseRecord_RoomSetCarpet(HouseRoom *room, const u16 *carpet, int flag)
{
    room->carpet = *carpet;
    room->flags = (u8) ((room->flags & ~HOUSE_ROOM_CARPET_FLAG) | ((flag & 1) << 1));
}
CLEAN_AS(func_02061194, HouseRecord_RoomSetCarpet)

/* func_020611bc: the room's wallpaper and its flag (bit 0 of `flag`). */
void HouseRecord_RoomSetWallpaper(HouseRoom *room, const u16 *wallpaper, int flag)
{
    room->wallpaper = *wallpaper;
    room->flags = (u8) ((room->flags & ~HOUSE_ROOM_WALLPAPER_FLAG) | (flag & 1));
}
CLEAN_AS(func_020611bc, HouseRecord_RoomSetWallpaper)

/* func_020611e8: the room's carpet, its flag to *flag unless `flag` is NULL. */
u16 *HouseRecord_RoomCarpet(HouseRoom *room, unsigned int *flag)
{
    if (flag != NULL) {
        *flag = (room->flags & HOUSE_ROOM_CARPET_FLAG) >> 1;
    }
    return &room->carpet;
}
CLEAN_AS(func_020611e8, HouseRecord_RoomCarpet)

/* The room's codes when first set up, by room: function-local statics of the original, each
 * set up the first time (bit 0 of their guard) and registered for destruction with the item
 * code's destructor. */
extern u16 data_021cb504[]; /* wallpapers: 0x113e for each room */
extern u32 data_021cb500;
extern u16 data_021cb510[]; /* carpets: 0x1182 for each room */
extern u32 data_021cb4f8;
extern u8 data_021cb570[], data_021cb594[], data_021cb588[], data_021cb57c[], data_021cb51c[];
extern u8 data_021cb528[], data_021cb534[], data_021cb540[], data_021cb54c[], data_021cb558[];
/* An item code's constructor (nothing), and a layer's destructor and constructor, which the
 * array helpers are handed. */
extern void func_02034ce0(void *code);
extern void *func_020614e4(void *layer);
extern int func_02061504(int layer);

#define HOUSE_ROOM_FIRST_WALLPAPER 0x113e
#define HOUSE_ROOM_FIRST_CARPET 0x1182
#define HOUSE_ROOM_LAYERS 2
#define HOUSE_ROOM_LAYER_CELLS 256
#define HOUSE_ROOM_LAYER_WIDTH 16
/* The first room's starting furniture, and the switch of the cell on top of it. */
#define HOUSE_ROOM_START_LOWER 0x3808       /* layer 0 at (6, 10) */
#define HOUSE_ROOM_START_LOWER_RIGHT 0x374c /* layer 0 at (9, 10) */
#define HOUSE_ROOM_START_UPPER 0x382c       /* layer 1 at (6, 10) */
#define HOUSE_ROOM_START_RIGHT_X 9
#define HOUSE_ROOM_FIRST_SCENE 1

/* func_02061204: the room's wallpaper, its flag to *flag unless `flag` is NULL. */
u16 *HouseRecord_RoomWallpaper(HouseRoom *room, int *flag)
{
    if (flag != NULL) {
        *flag = room->flags & HOUSE_ROOM_WALLPAPER_FLAG;
    }
    return &room->wallpaper;
}
CLEAN_AS(func_02061204, HouseRecord_RoomWallpaper)

/* func_02061220: the room's cells. */
struct RoomCells *HouseRecord_RoomCells(HouseRoom *room)
{
    return (RoomCells *) room->cells;
}
CLEAN_AS(func_02061220, HouseRecord_RoomCells)

/* func_0206122c: an acre map source for the room, from `heap` (NULL when there is no room for
 * it): its items the room's layer 0, the word after them its layer 1, and no extra record. */
AcreMapSource *HouseRecord_RoomMakeSource(HouseRoom *room, int heap)
{
    AcreMapSource *source = AcreMap_MakeSources(1, heap);
    if (source != NULL) {
        AcreMap_InitSource(source);
    }
    if (source != NULL) {
        source->items = HouseRecord_RoomLayer(room->items[0]);
        source->unk_08 = (int) (uintptr_t) HouseRecord_RoomLayer(room->items[1]);
        source->extra = NULL;
    }
    return source;
}
CLEAN_AS(func_0206122c, HouseRecord_RoomMakeSource)

/* func_0206126c: room `index` set up: both layers empty, its cells reset, its first wallpaper
 * and carpet and no song. The first room also gets its starting furniture, and the switch of
 * the cell (6, 10) on top is turned off in scene 1 (the first room's).
 * REQUIRES: `index` is 0-4 (it indexes the two tables of five). */
void HouseRecord_RoomInit(HouseRoom *room, int index)
{
    for (int layer = 0; layer < HOUSE_ROOM_LAYERS; layer++) {
        HouseRecord_ClearLayer(room->items[layer]);
    }
    RoomCells_Reset((RoomCells *) room->cells);

    if ((data_021cb500 & 1) == 0) {
        u8 *records[HOUSE_RECORD_ROOMS] = {data_021cb570, data_021cb594, data_021cb588, data_021cb57c, data_021cb51c};
        for (int i = 0; i < HOUSE_RECORD_ROOMS; i++) {
            data_021cb504[i] = HOUSE_ROOM_FIRST_WALLPAPER;
            __register_global_object(&data_021cb504[i], (void *) (uintptr_t) func_020051b0, records[i]);
        }
        data_021cb500 |= 1;
    }
    room->wallpaper = data_021cb504[index];

    if ((data_021cb4f8 & 1) == 0) {
        u8 *records[HOUSE_RECORD_ROOMS] = {data_021cb528, data_021cb534, data_021cb540, data_021cb54c, data_021cb558};
        for (int i = 0; i < HOUSE_RECORD_ROOMS; i++) {
            data_021cb510[i] = HOUSE_ROOM_FIRST_CARPET;
            __register_global_object(&data_021cb510[i], (void *) (uintptr_t) func_020051b0, records[i]);
        }
        data_021cb4f8 |= 1;
    }
    room->carpet = data_021cb510[index];
    room->song = HOUSE_RECORD_NO_ITEM;

    if (index != 0) {
        return;
    }
    u16 *lower = HouseRecord_RoomLayer(room->items[0]);
    u16 *upper = HouseRecord_RoomLayer(room->items[1]);
    int cell = HOUSE_ROOM_START_CELL_Y * HOUSE_ROOM_LAYER_WIDTH + HOUSE_ROOM_START_CELL_X;
    if (lower != NULL) {
        lower[cell] = HOUSE_ROOM_START_LOWER;
        lower[HOUSE_ROOM_START_CELL_Y * HOUSE_ROOM_LAYER_WIDTH + HOUSE_ROOM_START_RIGHT_X] = HOUSE_ROOM_START_LOWER_RIGHT;
    }
    if (upper != NULL) {
        upper[cell] = HOUSE_ROOM_START_UPPER;
        RoomCells_SetSwitch(HOUSE_ROOM_START_CELL_X, HOUSE_ROOM_START_CELL_Y, 1, 0, HOUSE_ROOM_FIRST_SCENE);
    }
}
CLEAN_AS(func_0206126c, HouseRecord_RoomInit)

/* func_02061444: the destructor: the cells, then the two layers. Returns the room. */
HouseRoom *HouseRecord_RoomDestruct(HouseRoom *room)
{
    RoomCells_Destruct((RoomCells *) room->cells);
    __cxa_vec_cleanup(room->items, HOUSE_ROOM_LAYERS, sizeof(room->items[0]), (void (*)(void *))(uintptr_t) func_020614e4);
    return room;
}
CLEAN_AS(func_02061444, HouseRecord_RoomDestruct)

/* func_02061470: the constructor: the two layers, the cells, and no wallpaper, carpet or song.
 * Returns the room. */
HouseRoom *HouseRecord_RoomConstruct(HouseRoom *room)
{
    __cxa_vec_ctor(room->items, HOUSE_ROOM_LAYERS, sizeof(room->items[0]), (void (*)(void *))(uintptr_t) func_02061504,
                   (void (*)(void *))(uintptr_t) func_020614e4);
    RoomCells_Construct((RoomCells *) room->cells);
    room->wallpaper = HOUSE_RECORD_NO_ITEM;
    room->carpet = HOUSE_RECORD_NO_ITEM;
    room->song = HOUSE_RECORD_NO_ITEM;
    return room;
}
CLEAN_AS(func_02061470, HouseRecord_RoomConstruct)

/* func_020614c4: a layer's codes (the layer itself). */
u16 *HouseRecord_RoomLayer(u16 *layer)
{
    return layer;
}
CLEAN_AS(func_020614c4, HouseRecord_RoomLayer)

/* func_020614c8: every code of the layer set to nothing. */
void HouseRecord_ClearLayer(u16 *layer)
{
    for (int i = 0; i < HOUSE_ROOM_LAYER_CELLS; i++) {
        layer[i] = HOUSE_RECORD_NO_ITEM;
    }
}
CLEAN_AS(func_020614c8, HouseRecord_ClearLayer)

/* func_020614e4: a layer's destructor (each code's, last first). Returns the layer. */
u16 *HouseRecord_DestructLayer(u16 *layer)
{
    __cxa_vec_cleanup(layer, HOUSE_ROOM_LAYER_CELLS, sizeof(u16), (void (*)(void *))(uintptr_t) func_020051b0);
    return layer;
}
CLEAN_AS(func_020614e4, HouseRecord_DestructLayer)

/* func_02061504: a layer's constructor (each code nothing). Returns the layer. */
int HouseRecord_ConstructLayer(int layer)
{
    __cxa_vec_ctor((void *) (uintptr_t) layer, HOUSE_ROOM_LAYER_CELLS, sizeof(u16),
                   (void (*)(void *))(uintptr_t) func_02034ce0, (void (*)(void *))(uintptr_t) func_020051b0);
    return layer;
}
CLEAN_AS(func_02061504, HouseRecord_ConstructLayer)
