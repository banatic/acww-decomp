/* furniture_sounds: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223a770 @ 0x0223a770, 0x20 bytes, Thumb
 * func_ov004_0223a760 @ 0x0223a760, 0x10 bytes, Thumb
 * func_ov004_0223a750 @ 0x0223a750, 0x10 bytes, Thumb
 * func_ov004_0223a740 @ 0x0223a740, 0x10 bytes, Thumb
 * func_ov004_0223a730 @ 0x0223a730, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_0223a770;

extern UnkStruct_0223a770 data_ov004_02247fb4[];
extern UnkStruct_0223a770 data_ov004_02247ce4;

UnkStruct_0223a770 *func_ov004_0223a770(int i)
{
    if (i < 0x6e9) {
        return &data_ov004_02247fb4[i];
    }
    return &data_ov004_02247ce4;
}

u16 func_ov004_0223a760(void *a)
{
    return *(u16 *) func_ov004_0223a770((int) a);
}

int func_ov004_0223a750(void *self)
{
    return *(unsigned short *) ((char *) (void *) func_ov004_0223a770((int) self) + 0x2);
}

int func_ov004_0223a740(void *self)
{
    return *(unsigned short *) ((char *) (void *) func_ov004_0223a770((int) self) + 0x4);
}

int func_ov004_0223a730(void *self)
{
    return *(unsigned short *) ((char *) (void *) func_ov004_0223a770((int) self) + 0x6);
}
