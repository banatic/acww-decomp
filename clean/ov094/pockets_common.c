/* Overlay 094's menu sounds and item tests (pockets_common.h). */
#include "pockets_common.h"

#include "clean.h"
#include "main/sound.h"

#define POCKETS_SOUND_0C 0x0c
#define POCKETS_SOUND_0D 0x0d
#define POCKETS_SOUND_0E 0x0e

/* func_ov094_022999c0: sound 0xd. */
void PocketsSound_Play0d(void)
{
    SoundSys_PlaySe(POCKETS_SOUND_0D);
}
CLEAN_AS(func_ov094_022999c0, PocketsSound_Play0d)

/* func_ov094_022999cc: sound 0xc. */
void PocketsSound_Play0c(void)
{
    SoundSys_PlaySe(POCKETS_SOUND_0C);
}
CLEAN_AS(func_ov094_022999cc, PocketsSound_Play0c)

/* func_ov094_022999d8: sound 0xe. */
void PocketsSound_Play0e(void)
{
    SoundSys_PlaySe(POCKETS_SOUND_0E);
}
CLEAN_AS(func_ov094_022999d8, PocketsSound_Play0e)

static int in_range(unsigned int item, unsigned int first, unsigned int last)
{
    return item >= first && item <= last;
}

/* func_ov094_022999e4: whether the pockets scene of the town (PocketsTown_CanUseItem) lets
 * `item` be used: not an insect or a fish (0x12b0-0x131f), not 0x137c and not a worn item
 * (0x1408-0x1428, 0x1471-0x1491); 1 for every other code. */
int PocketsItem_CanUse(unsigned int item)
{
    if (in_range(item, 0x12e8, 0x131f) || in_range(item, 0x12b0, 0x12e7)) {
        return 0;
    }
    if (item == 0x137c || in_range(item, 0x1408, 0x1428) || in_range(item, 0x1471, 0x1491)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov094_022999e4, PocketsItem_CanUse)

/* func_ov094_02299a54: whether `item` is 0x155d (a letter refuses it, PocketsScreen_CheckDrop). */
int PocketsItem_Is155d(u16 item)
{
    return item == 0x155d;
}
CLEAN_AS(func_ov094_02299a54, PocketsItem_Is155d)

/* func_ov094_02299a70: whether `item` is 0x155f or 0x1560. */
int PocketsItem_IsDayItem(u16 item)
{
    return in_range(item, 0x155f, 0x1560);
}
CLEAN_AS(func_ov094_02299a70, PocketsItem_IsDayItem)

/* func_ov094_02299a90: whether `item` is one of 0x155f-0x1564. */
int PocketsItem_IsIn155fTo1564(u16 item)
{
    return in_range(item, 0x155f, 0x1560) || in_range(item, 0x1561, 0x1564);
}
CLEAN_AS(func_ov094_02299a90, PocketsItem_IsIn155fTo1564)

/* func_ov094_02299b04: whether `item` is one a letter refuses with answer 4
 * (PocketsScreen_CheckDrop): 0x1531-0x1541 (the counted items 0x1531-0x153a among them),
 * 0x154a-0x1553, or an insect or a fish (0x12b0-0x131f). */
int PocketsItem_InLetterRefusedRanges(unsigned int item)
{
    return in_range(item, 0x1531, 0x153a) || in_range(item, 0x153b, 0x1541) || in_range(item, 0x154a, 0x1553) ||
           in_range(item, 0x12e8, 0x131f) || in_range(item, 0x12b0, 0x12e7);
}
CLEAN_AS(func_ov094_02299b04, PocketsItem_InLetterRefusedRanges)
