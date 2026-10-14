/* Sets of map object codes (kind 0, the codes the town's tiles hold; 0xfff1 is an empty tile).
 *
 * Families: three families of four lines each, the same shape in every family (6, 6, 6 and 8
 * codes), plus a few codes after each family's last line:
 *
 *   family A: 0x00-0x05, 0x06-0x0b, 0x0c-0x11, 0x12-0x19
 *   family B: 0x6e-0x73, 0x74-0x79, 0x7a-0x7f, 0x80-0x87
 *   family C: 0x8a-0x8f, 0x90-0x95, 0x96-0x9b, 0x9c-0xa3
 *
 * Growth lines: codes that step through stages. func_0204a150 moves a code one stage on (code
 * + 1) unless it is at the last stage (MapItem_IsGrown), and moves a line's eighth code back
 * three to its last stage. The lines are 0x26-0x2a, five lines of eight at 0x2f-0x56, 0x57-0x5b,
 * 0x5d-0x61 and 0xc8-0xcf; 0x66-0x6d are codes at their last stage only.
 *
 * Short lines: four lines of four codes, 0x2b-0x2e, 0x62-0x65, 0xd0-0xd3 and 0xff-0x102,
 * numbered by stage from 1. */
#ifndef CLEAN_MAIN_MAP_ITEM_H
#define CLEAN_MAIN_MAP_ITEM_H

#include "item_code.h"
#include "types.h"

/* func_0204b3d0 */
BOOL MapItem_InFamilies(const ItemCode *item);
/* func_0204b430 */
BOOL MapItem_InFamilyC(const ItemCode *item);
/* func_0204b468 */
BOOL MapItem_IsFamilyC3(const ItemCode *item);
/* func_0204b4a0 */
BOOL MapItem_IsFamilyC2(const ItemCode *item);
/* func_0204b4ac */
BOOL MapItem_IsFamilyC1(const ItemCode *item);
/* func_0204b4b8 */
BOOL MapItem_IsFamilyC0(const ItemCode *item);
/* func_0204b4c4 */
BOOL MapItem_InFamilyA(const ItemCode *item);
/* func_0204b4fc */
BOOL MapItem_IsFamilyA3(const ItemCode *item);
/* func_0204b520 */
BOOL MapItem_IsFamilyA2(const ItemCode *item);
/* func_0204b52c */
BOOL MapItem_IsFamilyA1(const ItemCode *item);
/* func_0204b538 */
BOOL MapItem_IsFamilyA0(const ItemCode *item);
/* func_0204b544 */
BOOL MapItem_InFamilyB(const ItemCode *item);
/* func_0204b57c */
BOOL MapItem_IsFamilyB3(const ItemCode *item);
/* func_0204b588 */
BOOL MapItem_IsFamilyB2(const ItemCode *item);
/* func_0204b594 */
BOOL MapItem_IsFamilyB1(const ItemCode *item);
/* func_0204b5a0 */
BOOL MapItem_IsFamilyB0(const ItemCode *item);

/* func_0204b5ac */
int MapItem_ShortStage(const ItemCode *item);
/* func_0204b5f4 */
BOOL MapItem_InShortLines(const ItemCode *item);
/* func_0204b620 */
BOOL MapItem_IsShortLineD0(const ItemCode *item);
/* func_0204b62c */
BOOL MapItem_IsShortLine62(const ItemCode *item);
/* func_0204b638 */
BOOL MapItem_IsShortLine2bOrFf(const ItemCode *item);
/* func_0204b65c */
BOOL MapItem_IsShortLineFf(const ItemCode *item);
/* func_0204b66c */
BOOL MapItem_IsShortLine2b(const ItemCode *item);
/* func_0204b678 */
BOOL MapItem_IsShortStage3(const ItemCode *item);
/* func_0204b6ac */
BOOL MapItem_IsShortStage2(const ItemCode *item);
/* func_0204b6e0 */
BOOL MapItem_IsShortStage1(const ItemCode *item);

/* func_0204b710 */
int MapItem_EightLine(const ItemCode *item);
/* func_0204b760 */
BOOL MapItem_IsLine4f(const ItemCode *item);
/* func_0204b76c */
BOOL MapItem_IsLine2f(const ItemCode *item);
/* func_0204b778 */
BOOL MapItem_IsLine47(const ItemCode *item);
/* func_0204b784 */
BOOL MapItem_IsLine3f(const ItemCode *item);
/* func_0204b790 */
BOOL MapItem_IsLine37(const ItemCode *item);

/* func_0204b7a0 */
int MapItem_GrowthStage(const ItemCode *item);
/* func_0204b7f8 */
BOOL MapItem_Grows(const ItemCode *item);
/* func_0204b860 */
BOOL MapItem_IsLineC8(const ItemCode *item);
/* func_0204b86c */
BOOL MapItem_Is6d(const ItemCode *item);
/* func_0204b87c */
BOOL MapItem_IsGroup6a(const ItemCode *item);
/* func_0204b888 */
BOOL MapItem_Is69(const ItemCode *item);
/* func_0204b898 */
BOOL MapItem_IsGroup66(const ItemCode *item);
/* func_0204b8a4 */
BOOL MapItem_IsLine57(const ItemCode *item);
/* func_0204b8b0 */
BOOL MapItem_InEightLines(const ItemCode *item);
/* func_0204b8bc */
BOOL MapItem_IsLine5d(const ItemCode *item);
/* func_0204b8c8 */
BOOL MapItem_IsLine26(const ItemCode *item);
/* func_0204b8d4 */
BOOL MapItem_IsEighth(const ItemCode *item);
/* func_0204b910 */
BOOL MapItem_IsGrown(const ItemCode *item);
/* func_0204b998 */
BOOL MapItem_IsStage3(const ItemCode *item);
/* func_0204b9ec */
BOOL MapItem_IsStage2(const ItemCode *item);
/* func_0204ba40 */
BOOL MapItem_IsStage1(const ItemCode *item);
/* func_0204ba94 */
BOOL MapItem_IsStage0(const ItemCode *item);

#endif
