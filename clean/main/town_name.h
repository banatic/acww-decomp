/* A town's number and name, as the state block (state_block.h), the player records, designs and
 * paired towns keep it: a 16-bit number, bit 15 set when made (zero: none), and six 16-bit
 * characters. Two small text classes carry the name: a wide text of six characters and an
 * 8-bit text of 14 bytes (each character two bytes), both deriving from the text bases of
 * text_base.h, with the four vtable entries of a text (TextVtable). */
#ifndef CLEAN_MAIN_TOWN_NAME_H
#define CLEAN_MAIN_TOWN_NAME_H

#include "text_base.h"
#include "types.h"

#define TOWN_NAME_LENGTH 6
#define TOWN_NAME_TEXT_CAPACITY 14

/* 0x0e bytes. */
typedef struct TownName {
    u16 number;                 /* 0x00: 0 for none, else bit 15 set */
    u16 name[TOWN_NAME_LENGTH]; /* 0x02 */
} TownName;

/* The wide text (vtable data_020de67c, 0x1c bytes). */
typedef struct TownNameWideText {
    const TextVtable *vtable;                 /* 0x00 */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x04: the wide text base's */
    u16 chars[TOWN_NAME_LENGTH];              /* 0x0e */
    u8 pad_1a[2];
} TownNameWideText;

/* The 8-bit text (vtable data_020de694, 0x20 bytes). */
typedef struct TownNameText {
    const TextVtable *vtable;                 /* 0x00 */
    u32 length;                               /* 0x04: the text base's */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x08 */
    char chars[TOWN_NAME_TEXT_CAPACITY];      /* 0x12 */
} TownNameText;

int TownNameWideText_Chars(int text);
void TownNameWideText_CopyOut(TownNameWideText *text, u16 *out, int count);
int TownNameWideText_Capacity(void);
TownNameWideText *TownNameWideText_Delete(TownNameWideText *text);
TownNameWideText *TownNameWideText_Destruct(TownNameWideText *text);
TownNameWideText *TownNameWideText_Construct(TownNameWideText *text);
int TownNameText_Chars(int text);
int TownNameText_Capacity(void);
TownNameText *TownNameText_Delete(TownNameText *text);
TownNameText *TownNameText_Destruct(TownNameText *text);
TownNameText *TownNameText_Construct(TownNameText *text);
void TownName_SetNameFromText(TownName *town, TextBase *text);
void TownName_ToText(TownName *town, TextBase *text);
void TownName_Make(TownName *town, const u16 *name);
u16 TownName_NewNumber(TownName *town);
void TownName_SetNumber(u16 *number, int value);
unsigned int TownName_IsSet(const u16 *number);
int TownName_Name(int town);
void TownName_CopyTo(const u16 *src, u16 *dst);
void TownName_Assign(TownName *dst, const TownName *src);
void TownName_Copy(TownName *dst, const TownName *src);
void TownName_Clear(TownName *town);
void TownName_Destruct(void *town);
void TownName_Construct(void *town);

#endif
