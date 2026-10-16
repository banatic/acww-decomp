/* The record of the player's house (data_021ebcd4, at 0xf52c in the state block, 0x15a4
 * bytes): its five rooms, the loan, the songs kept in the house and a word of bits.
 *
 * - A room's record (0x450 bytes) holds its two layers of items, its cells (room_cells.h),
 *   its wallpaper, carpet and song item codes and a flag bit for each of the first two
 *   (room_interior.h). The rooms are the scenes 1-5 (scene_kinds.h), room = scene - 1.
 * - The loan is what the player still owes for the house: 19,800 at first, and for each size
 *   the loan of the next extension (data_020cc9d0) once the last one is paid.
 * - The songs (70 bits, one per song item 0x1323-0x1368) are the songs the house's music
 *   collection holds: overlay 109 adds one, overlay 144 takes one out.
 * - The word at 0x15a0 holds the house's size (0-6), the size ordered (the next extension,
 *   built on the next new day), the look shown and the look of the house (0-15, the roof's
 *   colour; at first the console owner's favourite colour), the look ordered with the
 *   extension, which rooms have their lights on, and in its top byte a count (0-10) the days
 *   of an absence past six raise, which the indoor overlay (4) reads and writes back.
 *
 * Built (the extension done overnight), the house's code on the town's map becomes that of its
 * new size (0x5014 + size) and the state block's flag 13 is set until Nook has told the player
 * the new loan (overlay 50). */
#ifndef CLEAN_MAIN_HOUSE_RECORD_H
#define CLEAN_MAIN_HOUSE_RECORD_H

#include "acre_map.h" /* AcreMapSource */
#include "types.h"

#define HOUSE_RECORD_ROOMS 5
#define HOUSE_RECORD_SIZES 7 /* sizes 0-6 */
#define HOUSE_RECORD_LAST_SIZE 6
#define HOUSE_RECORD_SONGS 70 /* the song items 0x1323-0x1368 */
#define HOUSE_RECORD_SONG_BYTES 9
#define HOUSE_RECORD_SONG_FIRST 0x1323
#define HOUSE_RECORD_SONG_LAST 0x1368
#define HOUSE_RECORD_NO_ITEM 0xfff1
#define HOUSE_RECORD_FIRST_LOAN 19800
#define HOUSE_RECORD_MAX_ABSENCE 10

/* HouseRecord.bits */
#define HOUSE_RECORD_SIZE_SHIFT 0 /* bits 0-2: the size */
#define HOUSE_RECORD_SIZE_MASK 7u
#define HOUSE_RECORD_ORDERED_SHIFT 3 /* bits 3-5: the size ordered */
#define HOUSE_RECORD_ORDERED_MASK 7u
#define HOUSE_RECORD_SHOWN_LOOK_SHIFT 6    /* bits 6-9: the look shown */
#define HOUSE_RECORD_LOOK_SHIFT 10         /* bits 10-13: the house's look */
#define HOUSE_RECORD_ORDERED_LOOK_SHIFT 14 /* bits 14-17: the look ordered with the extension */
#define HOUSE_RECORD_LOOK_MASK 0xfu
#define HOUSE_RECORD_LIT_SHIFT 18 /* bits 18-23: a bit per room (1 << room) whose lights are on */
#define HOUSE_RECORD_LIT_MASK 0x3fu
#define HOUSE_RECORD_ABSENCE_BYTE 3 /* bits 24-31, read and written as a byte */

typedef struct HouseRoom {
    u16 items[2][256]; /* 0x000: the two layers of 16 x 16 item codes */
    u8 cells[0x48];    /* 0x400: RoomCells */
    u16 wallpaper;     /* 0x448 */
    u16 carpet;        /* 0x44a */
    u16 song;          /* 0x44c: the song the room's music plays, HOUSE_RECORD_NO_ITEM for none */
    u8 flags;          /* 0x44e: bit 0 the wallpaper's, bit 1 the carpet's */
    u8 pad_44f;
} HouseRoom;

#define HOUSE_ROOM_WALLPAPER_FLAG 0x01
#define HOUSE_ROOM_CARPET_FLAG 0x02

typedef struct HouseRecord {
    HouseRoom rooms[HOUSE_RECORD_ROOMS]; /* 0x0000 */
    int loan;                            /* 0x1590 */
    u8 songs[HOUSE_RECORD_SONG_BYTES];   /* 0x1594: data_021ed268 */
    u8 pad_159d[3];
    union {
        u32 word;
        u8 bytes[4];
    } bits; /* 0x15a0 */
} HouseRecord;

void HouseRecord_ClearSongs(u8 *songs);
void HouseRecord_RemoveSong(unsigned int item);
void HouseRecord_ClearSongBit(u8 *songs, unsigned int song);
void HouseRecord_AddSong(unsigned int item);
void HouseRecord_SetSongBit(u8 *songs, unsigned int song);
int HouseRecord_HasSong(unsigned int item);
int HouseRecord_TestSongBit(const u8 *songs, unsigned int song);
void HouseRecord_DestructSongs(int songs);
void HouseRecord_ConstructSongs(void *songs);
int HouseRecord_CurrentSongPlayedElsewhere(const u16 *song);
int HouseRecord_SongPlayedElsewhere(int scene, const u16 *song);
void HouseRecord_StopCurrentSong(void);
int HouseRecord_StopSong(int scene);
int HouseRecord_SetCurrentSong(const u16 *song);
int HouseRecord_SetSong(int scene, const u16 *song);
u16 *HouseRecord_CurrentSong(void);
u16 *HouseRecord_Song(int scene);
int HouseRecord_AnyLit(const HouseRecord *house);
int HouseRecord_SetLit(HouseRecord *house, int scene, int lit);
unsigned char HouseRecord_LitBit(unsigned int scene);
int HouseRecord_OrderWithLook(HouseRecord *house, int look);
int HouseRecord_JustBuilt(HouseRecord *house);
void HouseRecord_TakeNextLoan(HouseRecord *house);
void HouseRecord_SetLoan(HouseRecord *house, int loan);
int HouseRecord_Loan(const HouseRecord *house);
void HouseRecord_AddAbsence(HouseRecord *house, int days);
void HouseRecord_SetAbsence(HouseRecord *house, unsigned char count);
unsigned char HouseRecord_Absence(const HouseRecord *house);
unsigned short HouseRecord_SizeModel(void *unused);
unsigned short HouseRecord_RoomModel(int unused, int room);
int HouseRecord_SetLook(HouseRecord *house, unsigned char look);
unsigned int HouseRecord_ShownLook(const HouseRecord *house);
int HouseRecord_Order(HouseRecord *house);
unsigned int HouseRecord_Size(const HouseRecord *house);
int HouseRecord_IsExtending(const HouseRecord *house);
AcreMapSource *HouseRecord_RoomSource(HouseRecord *house, int room, int heap);
HouseRoom *HouseRecord_Room(HouseRecord *house, int room);
HouseRoom *HouseRecord_RoomOfScene(HouseRecord *house, int scene);
int HouseRecord_IsRoom(int room);
void HouseRecord_Reset(HouseRecord *house);
void HouseRecord_Build(HouseRecord *house);
int HouseRecord_PlaceOnMap(int size);
void HouseRecord_Init(HouseRecord *house);
HouseRecord *HouseRecord_Destruct(HouseRecord *house);
HouseRecord *HouseRecord_Construct(HouseRecord *house);
void HouseRecord_RoomSetSong(HouseRoom *room, const u16 *song);
u16 *HouseRecord_RoomSong(HouseRoom *room);
void HouseRecord_RoomSetCarpet(HouseRoom *room, const u16 *carpet, int flag);
void HouseRecord_RoomSetWallpaper(HouseRoom *room, const u16 *wallpaper, int flag);
u16 *HouseRecord_RoomCarpet(HouseRoom *room, unsigned int *flag);

#endif
