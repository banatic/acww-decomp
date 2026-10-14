/* Sets of map object codes: see map_item.h for their shapes. */
#include "map_item.h"

/* func_0204b3d0: a code of the three families, or one of 0x1a, 0x1d, 0x1e, 0x88 and 0xa4.
 * 0x1a, 0x88 and 0xa4 are the code after the last line of families A, B and C. */
BOOL MapItem_InFamilies(const ItemCode *item)
{
    if (MapItem_InFamilyB(item) || MapItem_InFamilyA(item) || MapItem_InFamilyC(item)) {
        return TRUE;
    }
    switch (ItemCode_Get(item)) {
        case 0x1a:
        case 0x1d:
        case 0x1e:
        case 0x88:
        case 0xa4:
            return TRUE;
        default:
            return FALSE;
    }
}

/* func_0204b430 */
BOOL MapItem_InFamilyC(const ItemCode *item)
{
    return MapItem_IsFamilyC0(item) || MapItem_IsFamilyC1(item) || MapItem_IsFamilyC2(item) || MapItem_IsFamilyC3(item);
}

/* func_0204b468. QUIRK: the line takes in 0xa5, two past its end, but not 0xa4 between. */
BOOL MapItem_IsFamilyC3(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x9c, 0xa3) || *item == 0xa5;
}

/* func_0204b4a0 */
BOOL MapItem_IsFamilyC2(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x96, 0x9b);
}

/* func_0204b4ac */
BOOL MapItem_IsFamilyC1(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x90, 0x95);
}

/* func_0204b4b8 */
BOOL MapItem_IsFamilyC0(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x8a, 0x8f);
}

/* func_0204b4c4 */
BOOL MapItem_InFamilyA(const ItemCode *item)
{
    return MapItem_IsFamilyA0(item) || MapItem_IsFamilyA1(item) || MapItem_IsFamilyA2(item) || MapItem_IsFamilyA3(item);
}

/* func_0204b4fc. QUIRK: the line takes in 0x1c, three past its end; 0x1a and 0x1b between are
 * not in it. */
BOOL MapItem_IsFamilyA3(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x12, 0x19) || *item == 0x1c;
}

/* func_0204b520 */
BOOL MapItem_IsFamilyA2(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x0c, 0x11);
}

/* func_0204b52c */
BOOL MapItem_IsFamilyA1(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x06, 0x0b);
}

/* func_0204b538 */
BOOL MapItem_IsFamilyA0(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x00, 0x05);
}

/* func_0204b544. Unlike families A and C, no code past the last line belongs to it. */
BOOL MapItem_InFamilyB(const ItemCode *item)
{
    return MapItem_IsFamilyB0(item) || MapItem_IsFamilyB1(item) || MapItem_IsFamilyB2(item) || MapItem_IsFamilyB3(item);
}

/* func_0204b57c */
BOOL MapItem_IsFamilyB3(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x80, 0x87);
}

/* func_0204b588 */
BOOL MapItem_IsFamilyB2(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x7a, 0x7f);
}

/* func_0204b594 */
BOOL MapItem_IsFamilyB1(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x74, 0x79);
}

/* func_0204b5a0 */
BOOL MapItem_IsFamilyB0(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x6e, 0x73);
}

/* func_0204b5ac: the stage of a short line's code, 1-4, or -1 for other codes.
 * QUIRK: numbered from 1, where MapItem_GrowthStage numbers from 0. */
int MapItem_ShortStage(const ItemCode *item)
{
    if (!MapItem_InShortLines(item)) {
        return -1;
    }
    if (MapItem_IsShortStage1(item)) {
        return 1;
    }
    if (MapItem_IsShortStage2(item)) {
        return 2;
    }
    if (MapItem_IsShortStage3(item)) {
        return 3;
    }
    return 4;
}

/* func_0204b5f4 */
BOOL MapItem_InShortLines(const ItemCode *item)
{
    return MapItem_IsShortLine2bOrFf(item) || MapItem_IsShortLine62(item) || MapItem_IsShortLineD0(item);
}

/* func_0204b620 */
BOOL MapItem_IsShortLineD0(const ItemCode *item)
{
    return ItemCode_InRange(item, 0xd0, 0xd3);
}

/* func_0204b62c */
BOOL MapItem_IsShortLine62(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x62, 0x65);
}

/* func_0204b638 */
BOOL MapItem_IsShortLine2bOrFf(const ItemCode *item)
{
    return MapItem_IsShortLine2b(item) || MapItem_IsShortLineFf(item);
}

/* func_0204b65c */
BOOL MapItem_IsShortLineFf(const ItemCode *item)
{
    return ItemCode_InRange(item, 0xff, 0x102);
}

/* func_0204b66c */
BOOL MapItem_IsShortLine2b(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x2b, 0x2e);
}

/* func_0204b678: the third code of a short line. */
BOOL MapItem_IsShortStage3(const ItemCode *item)
{
    switch (ItemCode_Get(item)) {
        case 0x2d:
        case 0x64:
        case 0xd2:
        case 0x101:
            return TRUE;
        default:
            return FALSE;
    }
}

/* func_0204b6ac: the second code of a short line. */
BOOL MapItem_IsShortStage2(const ItemCode *item)
{
    switch (ItemCode_Get(item)) {
        case 0x2c:
        case 0x63:
        case 0xd1:
        case 0x100:
            return TRUE;
        default:
            return FALSE;
    }
}

/* func_0204b6e0: the first code of a short line. */
BOOL MapItem_IsShortStage1(const ItemCode *item)
{
    switch (ItemCode_Get(item)) {
        case 0x2b:
        case 0x62:
        case 0xd0:
        case 0xff:
            return TRUE;
        default:
            return FALSE;
    }
}

/* func_0204b710: which of the lines of eight at 0x2f-0x56 the code is on: 1 for 0x3f, 2 for
 * 0x47, 3 for 0x2f, 4 for 0x4f; 0 for the line at 0x37 and every other code. */
int MapItem_EightLine(const ItemCode *item)
{
    if (MapItem_IsLine37(item)) {
        return 0;
    }
    if (MapItem_IsLine3f(item)) {
        return 1;
    }
    if (MapItem_IsLine47(item)) {
        return 2;
    }
    if (MapItem_IsLine2f(item)) {
        return 3;
    }
    if (MapItem_IsLine4f(item)) {
        return 4;
    }
    return 0;
}

/* func_0204b760 */
BOOL MapItem_IsLine4f(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x4f, 0x56);
}

/* func_0204b76c */
BOOL MapItem_IsLine2f(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x2f, 0x36);
}

/* func_0204b778 */
BOOL MapItem_IsLine47(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x47, 0x4e);
}

/* func_0204b784 */
BOOL MapItem_IsLine3f(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x3f, 0x46);
}

/* func_0204b790 */
BOOL MapItem_IsLine37(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x37, 0x3e);
}

/* func_0204b7a0: the stage of a growing code, 0-3, or 4 for the last stage and the codes past
 * it (the fifth to eighth of a line of eight, and 0x66-0x6d); -1 for other codes. */
int MapItem_GrowthStage(const ItemCode *item)
{
    if (!MapItem_Grows(item)) {
        return -1;
    }
    if (MapItem_IsStage0(item)) {
        return 0;
    }
    if (MapItem_IsStage1(item)) {
        return 1;
    }
    if (MapItem_IsStage2(item)) {
        return 2;
    }
    if (MapItem_IsStage3(item)) {
        return 3;
    }
    return 4;
}

/* func_0204b7f8: a code of a growth line, or one of 0x66-0x6d. */
BOOL MapItem_Grows(const ItemCode *item)
{
    return MapItem_IsLine26(item) || MapItem_IsLine5d(item) || MapItem_InEightLines(item) || MapItem_IsLine57(item) ||
           MapItem_IsGroup66(item) || MapItem_Is69(item) || MapItem_IsGroup6a(item) || MapItem_Is6d(item) ||
           MapItem_IsLineC8(item);
}

/* func_0204b860 */
BOOL MapItem_IsLineC8(const ItemCode *item)
{
    return ItemCode_InRange(item, 0xc8, 0xcf);
}

/* func_0204b86c */
BOOL MapItem_Is6d(const ItemCode *item)
{
    return *item == 0x6d;
}

/* func_0204b87c */
BOOL MapItem_IsGroup6a(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x6a, 0x6c);
}

/* func_0204b888 */
BOOL MapItem_Is69(const ItemCode *item)
{
    return *item == 0x69;
}

/* func_0204b898 */
BOOL MapItem_IsGroup66(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x66, 0x68);
}

/* func_0204b8a4 */
BOOL MapItem_IsLine57(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x57, 0x5b);
}

/* func_0204b8b0: the five lines of eight. */
BOOL MapItem_InEightLines(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x2f, 0x56);
}

/* func_0204b8bc */
BOOL MapItem_IsLine5d(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x5d, 0x61);
}

/* func_0204b8c8 */
BOOL MapItem_IsLine26(const ItemCode *item)
{
    return ItemCode_InRange(item, 0x26, 0x2a);
}

/* func_0204b8d4: the eighth code of a line of eight, which func_0204a150 moves back to the
 * line's last stage. */
BOOL MapItem_IsEighth(const ItemCode *item)
{
    switch (ItemCode_Get(item)) {
        case 0x36:
        case 0x3e:
        case 0x46:
        case 0x4e:
        case 0x56:
        case 0xcf:
            return TRUE;
        default:
            return FALSE;
    }
}

/* func_0204b910: a growth line's last stage (its fifth code), or one of 0x66-0x6d. */
BOOL MapItem_IsGrown(const ItemCode *item)
{
    int code = ItemCode_Get(item);
    if (code >= 0x66 && code <= 0x6d) {
        return TRUE;
    }
    switch (code) {
        case 0x2a:
        case 0x33:
        case 0x3b:
        case 0x43:
        case 0x4b:
        case 0x53:
        case 0x5b:
        case 0x61:
        case 0xcc:
            return TRUE;
        default:
            return FALSE;
    }
}

/* The first code of each growth line; stage n is the code n after it. */
static BOOL is_stage(const ItemCode *item, int stage)
{
    static const u8 line_starts[] = {0x26, 0x2f, 0x37, 0x3f, 0x47, 0x4f, 0x57, 0x5d, 0xc8};
    int code = ItemCode_Get(item);
    for (unsigned i = 0; i < sizeof(line_starts); i++) {
        if (code == line_starts[i] + stage) {
            return TRUE;
        }
    }
    return FALSE;
}

/* func_0204b998 */
BOOL MapItem_IsStage3(const ItemCode *item)
{
    return is_stage(item, 3);
}

/* func_0204b9ec */
BOOL MapItem_IsStage2(const ItemCode *item)
{
    return is_stage(item, 2);
}

/* func_0204ba40 */
BOOL MapItem_IsStage1(const ItemCode *item)
{
    return is_stage(item, 1);
}

/* func_0204ba94 */
BOOL MapItem_IsStage0(const ItemCode *item)
{
    return is_stage(item, 0);
}
