/* What the table of unit types says of a unit (unit_type_info.h). */
#include "unit_type_info.h"

#include "clean.h"
#include "field_collision.h"
#include "itcm/field_units.h"

extern const CollisionTypeInfo data_020c907c[];
/* The four bytes UnitTypeInfo_Bytes18At gives for a type without a row. */
extern const u8 data_020c9048[4];

/* Unit types the tests below look for. */
#define UNIT_TYPE_03 0x03
#define UNIT_TYPE_07 0x07
#define UNIT_TYPE_08 0x08
#define UNIT_TYPE_0B 0x0b
#define UNIT_TYPE_12 0x12
#define UNIT_TYPE_1D 0x1d
#define UNIT_TYPE_1E 0x1e
#define UNIT_TYPE_6F 0x6f
#define UNIT_TYPE_70 0x70

/* Row `type` of the table, its address computed as the ARM does, in 32 bits (for any type the
 * callers let through). */
static const CollisionTypeInfo *unit_type_row(int type)
{
    return (const CollisionTypeInfo *) (uintptr_t) ((u32) (uintptr_t) data_020c907c + (u32) type * sizeof(CollisionTypeInfo));
}

/* The halfword at `offset` (even) of a row. */
static u16 unit_type_word(const CollisionTypeInfo *row, u32 offset)
{
    return *(const u16 *) (const void *) (row->unk_00 + offset);
}

/* func_02031478: 0 for a unit of type 0x6f, 1 for type 0x70, else UNIT_TYPE_INFO_NO_KIND. */
int UnitTypeInfo_Kind6fAt(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    if (type >= UNIT_TYPE_6F && type <= UNIT_TYPE_70) {
        return type - UNIT_TYPE_6F;
    }
    return UNIT_TYPE_INFO_NO_KIND;
}
CLEAN_AS(func_02031478, UnitTypeInfo_Kind6fAt)

/* func_02031914: the halfword at 2 of row `type`, 0xffff from 0x7c on.
 * QUIRK: a negative type is not refused; the row is read before the table. */
u16 UnitTypeInfo_Word02(int type)
{
    if (type < COLLISION_TYPE_COUNT) {
        return unit_type_word(unit_type_row(type), 2);
    }
    return 0xffff;
}
CLEAN_AS(func_02031914, UnitTypeInfo_Word02)

/* func_02031930: the sound of row `type` (its halfword at 0, ground_sound.h), 0xffff from 0x7c
 * on.
 * QUIRK: a negative type is not refused; the row is read before the table. */
u16 UnitTypeInfo_Sound(int type)
{
    if (type < COLLISION_TYPE_COUNT) {
        return unit_type_word(unit_type_row(type), 0);
    }
    return 0xffff;
}
CLEAN_AS(func_02031930, UnitTypeInfo_Sound)

/* func_0203194c: the bytes 0x18 to 0x1b of the row of unit (x, z) go to `out`, and the result
 * is 1; for a type without a row the four bytes at data_020c9048 do, and the result is 0. */
int UnitTypeInfo_Bytes18At(u8 *out, int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    if (type < COLLISION_TYPE_COUNT) {
        const CollisionTypeInfo *row = unit_type_row(type);
        for (int i = 0; i < 4; i++) {
            out[i] = row->unk_16[2 + i];
        }
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        out[i] = data_020c9048[i];
    }
    return 0;
}
CLEAN_AS(func_0203194c, UnitTypeInfo_Bytes18At)

/* func_02031a48: whether unit (x, z) is of type 0x1e and the unit after it on Z of type 8. */
int UnitTypeInfo_IsType1eOver08(int x, int z)
{
    return FieldUnits_GetType(x, z) == UNIT_TYPE_1E && FieldUnits_GetType(x, z + 1) == UNIT_TYPE_08;
}
CLEAN_AS(func_02031a48, UnitTypeInfo_IsType1eOver08)

/* func_02031a74: whether byte 0x17 of the row of unit (x, z) is set (no for a type without a
 * row). */
int UnitTypeInfo_HasByte17At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type < COLLISION_TYPE_COUNT && unit_type_row(type)->unk_16[1] != 0;
}
CLEAN_AS(func_02031a74, UnitTypeInfo_HasByte17At)

/* func_02031aa0: the halfword at 6 of the row of unit (x, z), signed, as 1 when above 0; -1 for
 * a type without a row. */
int UnitTypeInfo_Word06At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    if (type >= COLLISION_TYPE_COUNT) {
        return -1;
    }
    s16 value = (s16) unit_type_word(unit_type_row(type), 6);
    return value > 0 ? 1 : value;
}
CLEAN_AS(func_02031aa0, UnitTypeInfo_Word06At)

/* func_02031acc: byte 9 of the row of unit (x, z); 2 for a type without a row. */
u8 UnitTypeInfo_Byte09At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type < COLLISION_TYPE_COUNT ? unit_type_row(type)->unk_00[9] : 2;
}
CLEAN_AS(func_02031acc, UnitTypeInfo_Byte09At)

/* func_02031af0: byte 5 of the row of unit (x, z); 0 for a type without a row. */
int UnitTypeInfo_Byte05At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type < COLLISION_TYPE_COUNT ? unit_type_row(type)->unk_00[5] : 0;
}
CLEAN_AS(func_02031af0, UnitTypeInfo_Byte05At)

/* func_02031b14: byte 8 of the row of unit (x, z); 0 for a type without a row. */
int UnitTypeInfo_Byte08At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type < COLLISION_TYPE_COUNT ? unit_type_row(type)->unk_00[8] : 0;
}
CLEAN_AS(func_02031b14, UnitTypeInfo_Byte08At)

/* func_02031b38: byte 4 of the row of unit (x, z); 0 for a type without a row. */
u8 UnitTypeInfo_Byte04At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type < COLLISION_TYPE_COUNT ? unit_type_row(type)->unk_00[4] : 0;
}
CLEAN_AS(func_02031b38, UnitTypeInfo_Byte04At)

/* func_02031b5c: 1 for a unit of type 8; 2 for type 7 or 0x0b to 0x12; else 0. */
int UnitTypeInfo_GroupAt(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    if (type == UNIT_TYPE_08) {
        return 1;
    }
    if (type == UNIT_TYPE_07 || (type >= UNIT_TYPE_0B && type <= UNIT_TYPE_12)) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_02031b5c, UnitTypeInfo_GroupAt)

/* func_02031b84: whether unit (x, z) is of type 3 or 0x1d (what CollisionMap_RetypeToPlain
 * turns type 3 into). */
int UnitTypeInfo_IsType03At(int x, int z)
{
    int type = FieldUnits_GetType(x, z);
    return type == UNIT_TYPE_03 || type == UNIT_TYPE_1D;
}
CLEAN_AS(func_02031b84, UnitTypeInfo_IsType03At)
