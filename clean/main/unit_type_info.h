/* What the table of unit types (data_020c907c, 0x1e-byte rows, field_collision.h's
 * CollisionTypeInfo) says of a unit of the current map, and tests of a unit's type itself.
 *
 * A row is looked up by the unit's type (FieldUnits_GetType); types from 0x7c on have no row
 * and each question then has its own answer. The meaning of most fields is not known; they are
 * named by their offset in the row. */
#ifndef CLEAN_MAIN_UNIT_TYPE_INFO_H
#define CLEAN_MAIN_UNIT_TYPE_INFO_H

#include "types.h"

/* The answer of UnitTypeInfo_Kind6fAt for other types. */
#define UNIT_TYPE_INFO_NO_KIND (-1)

int UnitTypeInfo_Kind6fAt(int x, int z);
u16 UnitTypeInfo_Word02(int type);
u16 UnitTypeInfo_Sound(int type);
int UnitTypeInfo_Bytes18At(u8 *out, int x, int z);
int UnitTypeInfo_IsType1eOver08(int x, int z);
int UnitTypeInfo_HasByte17At(int x, int z);
int UnitTypeInfo_Word06At(int x, int z);
u8 UnitTypeInfo_Byte09At(int x, int z);
int UnitTypeInfo_Byte05At(int x, int z);
int UnitTypeInfo_Byte08At(int x, int z);
u8 UnitTypeInfo_Byte04At(int x, int z);
int UnitTypeInfo_GroupAt(int x, int z);
int UnitTypeInfo_IsType03At(int x, int z);

#endif
