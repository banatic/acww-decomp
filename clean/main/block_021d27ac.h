/* The object at data_021d27ac (func_0208602c gives it; constructed and destroyed by
 * __sinit_020c6194): a word of flags and seven parts whose own functions (0x02087a64 to
 * 0x020881a8) set them up. The spawner's placers and checks read parts 0x04, 0x0c, 0x24, 0x30
 * and 0x31 (spawner.h); StateBlock_FinishStart resets the object (Block021d27ac_Reset) and sets
 * flag 8 when the player qualifies (Block021d27ac_NoteGoldenToolDue).
 *
 * The flags, each named by its writer:
 *   0  the house loan paid off (ov054 post_clerk_talk.c); ov003's field actor then takes the
 *      player's walk out as kind 2
 *   1  the gardens judged (ov083 turtle_gardens_talk.c)
 *   2, 3  the fireworks turtle's greeting and fortune (ov084), 4 the countdown turtle's fortune
 *      (ov086)
 *   5  Nook's part-time job done (ov050 NookClerkTalk_JobEnd); the player walks out as kind 3
 *   7  the barber paid (ov053)
 *   8  a golden tool due: the player has every fish without the golden rod 0x1375 or every
 *      insect without the golden net 0x1377 (player flags 0x21, 0x22), so the spawner makes the
 *      turtle that hands it over (ov080 turtle_talk.h, Spawner_Profile56Allowed)
 *   9  the owl's greeting (ov047 owl_talk.c)
 *   10 the giraffe not paid (ov070 giraffe_talk.c)
 *
 * The flag functions take a word of 32 flags; a flag of 32 or more is never set. */
#ifndef CLEAN_MAIN_BLOCK_021D27AC_H
#define CLEAN_MAIN_BLOCK_021D27AC_H

#include "types.h"

#define BLOCK_021D27AC_FLAGS 32
#define BLOCK_021D27AC_FLAG_LOAN_PAID_OFF 0
#define BLOCK_021D27AC_FLAG_NOOK_JOB_DONE 5
#define BLOCK_021D27AC_FLAG_GOLDEN_TOOL_DUE 8 /* see Block021d27ac_NoteGoldenToolDue */

/* The parts' sizes are the distances between them; the last ends before data_021d27e0. */
typedef struct Block021d27ac {
    u32 flags;      /* 0x00 */
    u8 part_04[8];  /* 0x04 */
    u8 part_0c[12]; /* 0x0c */
    u8 part_18[8];  /* 0x18 */
    u8 part_20[4];  /* 0x20 */
    u8 part_24[12]; /* 0x24 */
    u8 part_30;     /* 0x30 */
    u8 part_31[3];  /* 0x31 */
} Block021d27ac;

Block021d27ac *Block021d27ac_Get(void);
void Block021d27ac_NoteGoldenToolDue(Block021d27ac *self);
u8 *Block021d27ac_Part04(Block021d27ac *self);
u8 *Block021d27ac_Part31(Block021d27ac *self);
u8 *Block021d27ac_Part24(Block021d27ac *self);
u8 *Block021d27ac_Part0c(Block021d27ac *self);
u8 *Block021d27ac_Part30(Block021d27ac *self);
u8 *Block021d27ac_Part20(Block021d27ac *self);
u8 *Block021d27ac_Part18(Block021d27ac *self);
void Block021d27ac_ClearFlag(u32 *flags, u32 flag);
void Block021d27ac_SetFlag(u32 *flags, u32 flag);
int Block021d27ac_TestFlag(u32 *flags, u32 flag);
void Block021d27ac_Reset(Block021d27ac *self);
Block021d27ac *Block021d27ac_Destruct(Block021d27ac *self);
Block021d27ac *Block021d27ac_Construct(Block021d27ac *self);

#endif
