#include "../../../clean/main/map_item.h"
#include "diffcheck.h"

#define CODE DIFF_SCRATCH

/* A map object code: mostly the codes the sets cover (0x00-0x10f), sometimes an empty tile or
 * a code of another kind. */
static void a_code(DiffRng *rng, uint32_t args[4])
{
    u16 code;
    switch (diff_range(rng, 0, 9)) {
        case 0:
            code = ITEM_CODE_NONE;
            break;
        case 1:
            code = (u16) diff_range(rng, 0x1000, 0xefff);
            break;
        default:
            code = (u16) diff_range(rng, 0, 0x10f);
            break;
    }
    *(ItemCode *) (uintptr_t) CODE = code;
    args[0] = CODE;
}

static uint32_t in_families(const uint32_t args[4])
{
    return (uint32_t) MapItem_InFamilies((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t in_family_c(const uint32_t args[4])
{
    return (uint32_t) MapItem_InFamilyC((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_c3(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyC3((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_c2(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyC2((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_c1(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyC1((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_c0(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyC0((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t in_family_a(const uint32_t args[4])
{
    return (uint32_t) MapItem_InFamilyA((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_a3(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyA3((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_a2(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyA2((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_a1(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyA1((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_a0(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyA0((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t in_family_b(const uint32_t args[4])
{
    return (uint32_t) MapItem_InFamilyB((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_b3(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyB3((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_b2(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyB2((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_b1(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyB1((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_family_b0(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsFamilyB0((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t short_stage(const uint32_t args[4])
{
    return (uint32_t) MapItem_ShortStage((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t in_short_lines(const uint32_t args[4])
{
    return (uint32_t) MapItem_InShortLines((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_line_d0(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortLineD0((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_line62(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortLine62((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_line2b_or_ff(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortLine2bOrFf((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_line_ff(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortLineFf((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_line2b(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortLine2b((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_stage3(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortStage3((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_stage2(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortStage2((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_short_stage1(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsShortStage1((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t eight_line(const uint32_t args[4])
{
    return (uint32_t) MapItem_EightLine((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line4f(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine4f((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line2f(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine2f((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line47(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine47((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line3f(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine3f((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line37(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine37((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t growth_stage(const uint32_t args[4])
{
    return (uint32_t) MapItem_GrowthStage((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t grows(const uint32_t args[4])
{
    return (uint32_t) MapItem_Grows((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line_c8(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLineC8((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is6d(const uint32_t args[4])
{
    return (uint32_t) MapItem_Is6d((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_group6a(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsGroup6a((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is69(const uint32_t args[4])
{
    return (uint32_t) MapItem_Is69((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_group66(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsGroup66((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line57(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine57((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t in_eight_lines(const uint32_t args[4])
{
    return (uint32_t) MapItem_InEightLines((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line5d(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine5d((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_line26(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsLine26((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_eighth(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsEighth((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_grown(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsGrown((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_stage3(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsStage3((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_stage2(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsStage2((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_stage1(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsStage1((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t is_stage0(const uint32_t args[4])
{
    return (uint32_t) MapItem_IsStage0((const ItemCode *) (uintptr_t) args[0]);
}

DIFF_CHECK(func_0204b3d0, "main", 0x0204b3d0 | 1, 32, 1, a_code, in_families)
DIFF_CHECK(func_0204b430, "main", 0x0204b430 | 1, 32, 1, a_code, in_family_c)
DIFF_CHECK(func_0204b468, "main", 0x0204b468 | 1, 32, 1, a_code, is_family_c3)
DIFF_CHECK(func_0204b4a0, "main", 0x0204b4a0 | 1, 32, 1, a_code, is_family_c2)
DIFF_CHECK(func_0204b4ac, "main", 0x0204b4ac | 1, 32, 1, a_code, is_family_c1)
DIFF_CHECK(func_0204b4b8, "main", 0x0204b4b8 | 1, 32, 1, a_code, is_family_c0)
DIFF_CHECK(func_0204b4c4, "main", 0x0204b4c4 | 1, 32, 1, a_code, in_family_a)
DIFF_CHECK(func_0204b4fc, "main", 0x0204b4fc | 1, 32, 1, a_code, is_family_a3)
DIFF_CHECK(func_0204b520, "main", 0x0204b520 | 1, 32, 1, a_code, is_family_a2)
DIFF_CHECK(func_0204b52c, "main", 0x0204b52c | 1, 32, 1, a_code, is_family_a1)
DIFF_CHECK(func_0204b538, "main", 0x0204b538 | 1, 32, 1, a_code, is_family_a0)
DIFF_CHECK(func_0204b544, "main", 0x0204b544 | 1, 32, 1, a_code, in_family_b)
DIFF_CHECK(func_0204b57c, "main", 0x0204b57c | 1, 32, 1, a_code, is_family_b3)
DIFF_CHECK(func_0204b588, "main", 0x0204b588 | 1, 32, 1, a_code, is_family_b2)
DIFF_CHECK(func_0204b594, "main", 0x0204b594 | 1, 32, 1, a_code, is_family_b1)
DIFF_CHECK(func_0204b5a0, "main", 0x0204b5a0 | 1, 32, 1, a_code, is_family_b0)
DIFF_CHECK(func_0204b5ac, "main", 0x0204b5ac | 1, 32, 1, a_code, short_stage)
DIFF_CHECK(func_0204b5f4, "main", 0x0204b5f4 | 1, 32, 1, a_code, in_short_lines)
DIFF_CHECK(func_0204b620, "main", 0x0204b620 | 1, 32, 1, a_code, is_short_line_d0)
DIFF_CHECK(func_0204b62c, "main", 0x0204b62c | 1, 32, 1, a_code, is_short_line62)
DIFF_CHECK(func_0204b638, "main", 0x0204b638 | 1, 32, 1, a_code, is_short_line2b_or_ff)
DIFF_CHECK(func_0204b65c, "main", 0x0204b65c | 1, 32, 1, a_code, is_short_line_ff)
DIFF_CHECK(func_0204b66c, "main", 0x0204b66c | 1, 32, 1, a_code, is_short_line2b)
DIFF_CHECK(func_0204b678, "main", 0x0204b678 | 1, 32, 1, a_code, is_short_stage3)
DIFF_CHECK(func_0204b6ac, "main", 0x0204b6ac | 1, 32, 1, a_code, is_short_stage2)
DIFF_CHECK(func_0204b6e0, "main", 0x0204b6e0 | 1, 32, 1, a_code, is_short_stage1)
DIFF_CHECK(func_0204b710, "main", 0x0204b710 | 1, 32, 1, a_code, eight_line)
DIFF_CHECK(func_0204b760, "main", 0x0204b760 | 1, 32, 1, a_code, is_line4f)
DIFF_CHECK(func_0204b76c, "main", 0x0204b76c | 1, 32, 1, a_code, is_line2f)
DIFF_CHECK(func_0204b778, "main", 0x0204b778 | 1, 32, 1, a_code, is_line47)
DIFF_CHECK(func_0204b784, "main", 0x0204b784 | 1, 32, 1, a_code, is_line3f)
DIFF_CHECK(func_0204b790, "main", 0x0204b790 | 1, 32, 1, a_code, is_line37)
DIFF_CHECK(func_0204b7a0, "main", 0x0204b7a0 | 1, 32, 1, a_code, growth_stage)
DIFF_CHECK(func_0204b7f8, "main", 0x0204b7f8 | 1, 32, 1, a_code, grows)
DIFF_CHECK(func_0204b860, "main", 0x0204b860 | 1, 32, 1, a_code, is_line_c8)
DIFF_CHECK(func_0204b86c, "main", 0x0204b86c | 1, 32, 0, a_code, is6d)
DIFF_CHECK(func_0204b87c, "main", 0x0204b87c | 1, 32, 1, a_code, is_group6a)
DIFF_CHECK(func_0204b888, "main", 0x0204b888 | 1, 32, 0, a_code, is69)
DIFF_CHECK(func_0204b898, "main", 0x0204b898 | 1, 32, 1, a_code, is_group66)
DIFF_CHECK(func_0204b8a4, "main", 0x0204b8a4 | 1, 32, 1, a_code, is_line57)
DIFF_CHECK(func_0204b8b0, "main", 0x0204b8b0 | 1, 32, 1, a_code, in_eight_lines)
DIFF_CHECK(func_0204b8bc, "main", 0x0204b8bc | 1, 32, 1, a_code, is_line5d)
DIFF_CHECK(func_0204b8c8, "main", 0x0204b8c8 | 1, 32, 1, a_code, is_line26)
DIFF_CHECK(func_0204b8d4, "main", 0x0204b8d4 | 1, 32, 1, a_code, is_eighth)
DIFF_CHECK(func_0204b910, "main", 0x0204b910 | 1, 32, 1, a_code, is_grown)
DIFF_CHECK(func_0204b998, "main", 0x0204b998 | 1, 32, 1, a_code, is_stage3)
DIFF_CHECK(func_0204b9ec, "main", 0x0204b9ec | 1, 32, 1, a_code, is_stage2)
DIFF_CHECK(func_0204ba40, "main", 0x0204ba40 | 1, 32, 1, a_code, is_stage1)
DIFF_CHECK(func_0204ba94, "main", 0x0204ba94 | 1, 32, 1, a_code, is_stage0)
