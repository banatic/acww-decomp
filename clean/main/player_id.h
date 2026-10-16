/* A player's id (DesignCreator of design.h, 0x1e bytes): the player's town (TownName of
 * town_name.h: its number and name), the player's number (bit 15 set when made, zero: none),
 * the player's six 16-bit characters and a signed byte at 0x1c (2 when cleared; tables that
 * select by it take 2 as any value). A player's record holds its own at 0x247e; designs keep
 * their creator's.
 *
 * Two small text classes carry a player's name, as town_name.h's carry a town's: a wide text of
 * six characters (vtable data_020e2f54) and an 8-bit text of 14 bytes (vtable data_020e2f6c),
 * deriving from the text bases of text_base.h. */
#ifndef CLEAN_MAIN_PLAYER_ID_H
#define CLEAN_MAIN_PLAYER_ID_H

#include "design.h"
#include "text_base.h"
#include "town_name.h"
#include "types.h"

#define PLAYER_ID_NAME_LENGTH 6
#define PLAYER_ID_TEXT_CAPACITY 14

/* The wide text (0x1c bytes). */
typedef struct PlayerIdWideText {
    const TextVtable *vtable;                 /* 0x00 */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x04: the wide text base's */
    u16 chars[PLAYER_ID_NAME_LENGTH];         /* 0x0e */
    u8 pad_1a[2];
} PlayerIdWideText;

/* The 8-bit text (0x20 bytes). */
typedef struct PlayerIdText {
    const TextVtable *vtable;                 /* 0x00 */
    u32 length;                               /* 0x04: the text base's */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x08 */
    char chars[PLAYER_ID_TEXT_CAPACITY];      /* 0x12 */
} PlayerIdText;

int PlayerIdWideText_Chars(int text);
void PlayerIdWideText_CopyOut(PlayerIdWideText *text, u16 *out, int count);
int PlayerIdWideText_Capacity(void *text);
PlayerIdWideText *PlayerIdWideText_Delete(PlayerIdWideText *text);
PlayerIdWideText *PlayerIdWideText_Destruct(PlayerIdWideText *text);
PlayerIdWideText *PlayerIdWideText_Construct(PlayerIdWideText *text);
int PlayerIdText_Chars(int text);
int PlayerIdText_Capacity(void *text);
PlayerIdText *PlayerIdText_Delete(PlayerIdText *text);
PlayerIdText *PlayerIdText_Destruct(PlayerIdText *text);
PlayerIdText *PlayerIdText_Construct(PlayerIdText *text);
int PlayerId_IndexInTown(DesignCreator *player);
int PlayerId_WhichTown(DesignCreator *player);
void PlayerId_SetTown(DesignCreator *player, const TownName *town);
TownName *PlayerId_Town(DesignCreator *player);
void PlayerId_SetNameFromText(DesignCreator *player, TextBase *text);
void *PlayerId_NameToText(DesignCreator *player, TextBase *text);
int PlayerId_Name(int player);
void PlayerId_SetName(DesignCreator *player, const u16 *name);
int PlayerId_Byte1c(const s8 *player);
void PlayerId_SetByte1c(u8 *player, int value);
void PlayerId_SetNumber(u16 *player, int number);
int PlayerId_Number(const u16 *player);
u16 PlayerId_NewNumber(void);
int PlayerId_NewNumberNotIn(const u16 *numbers, int count);
int PlayerId_NumberIsIn(u16 number, const u16 *numbers, int count);
void PlayerId_Make(DesignCreator *player, const u16 *name, u16 number, u8 byte_1c, const TownName *town);
int PlayerId_SamePlayer(const DesignCreator *a, const DesignCreator *b);
int PlayerId_IsSet(DesignCreator *player);
void PlayerId_CopyTo(const DesignCreator *src, DesignCreator *dst);
void PlayerId_Assign(DesignCreator *dst, const DesignCreator *src);
void PlayerId_Clear(DesignCreator *player);
void PlayerId_Copy(DesignCreator *dst, const DesignCreator *src);
int PlayerId_Destruct(DesignCreator *player);
int PlayerId_CopyConstruct(DesignCreator *dst, DesignCreator *src);
DesignCreator *PlayerId_Construct(DesignCreator *player);

#endif
