/* Three small parts of the object at data_021d27ac (block_021d27ac.h) and their functions.
 *
 * Part 0x18: a date and time. Overlay 50 sets it to 23:00:00 of today (when it is invalid, and
 * at other points of its flow) and asks whether it has passed.
 *
 * Part 0x20: a halfword and a byte that overlay 48 sets together (the byte to 2) and reads
 * back while the byte is 1 or 2, clearing the byte; overlay 4 tests the byte for 1.
 *
 * Part 0x30: a byte StateBlock_StartMode2 sets to 1 (in scene 6, for a player record with
 * flag 2 and without flag 0x23) and the ends of the other start modes clear; while it is set
 * the spawner's check of code 0xd011 answers in scene 0 (Spawner_CheckD011). */
#ifndef CLEAN_MAIN_BLOCK_021D27AC_PARTS_H
#define CLEAN_MAIN_BLOCK_021D27AC_PARTS_H

#include "calendar.h"
#include "types.h"

/* The time part 0x18 is set to. */
#define BLOCK_021D27AC_PART18_HOUR 23

typedef struct Block021d27acPart20 {
    u16 value; /* 0x00 */
    u8 kind;   /* 0x02 */
    u8 unused_03;
} Block021d27acPart20;

int Block021d27acPart20_Value(const Block021d27acPart20 *part);
void Block021d27acPart20_SetValue(Block021d27acPart20 *part, int value);
int Block021d27acPart20_Kind(const Block021d27acPart20 *part);
void Block021d27acPart20_SetKind(Block021d27acPart20 *part, int kind);
void Block021d27acPart20_ClearKind(Block021d27acPart20 *part);
void Block021d27acPart20_Construct(Block021d27acPart20 *part);
void Block021d27acPart20_Destruct(Block021d27acPart20 *part);

void Block021d27acPart30_Set(u8 *part, int value);
int Block021d27acPart30_IsSet(const u8 *part);
void Block021d27acPart30_Clear(u8 *part);
void Block021d27acPart30_Construct(u8 *part);
void Block021d27acPart30_Destruct(u8 *part);

int Block021d27acPart18_HasPassed(const DateTime *part);
void Block021d27acPart18_SetToday(DateTime *part);
DateTime *Block021d27acPart18_Get(DateTime *part);
void Block021d27acPart18_Clear(DateTime *part);
void Block021d27acPart18_Construct(DateTime *part);
void Block021d27acPart18_Destruct(DateTime *part);

#endif
