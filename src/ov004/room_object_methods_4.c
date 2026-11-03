/* room_object_methods_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022114cc @ 0x022114cc, 0x2c bytes, Thumb
 * func_ov004_022114a0 @ 0x022114a0, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022114cc UnkStruct_022114cc;

struct UnkStruct_022114cc {
    void (**vt)(UnkStruct_022114cc *, int, void *);
};

typedef struct UnkStruct_022114a0 UnkStruct_022114a0;

struct UnkStruct_022114a0 {
    void (**vt)(UnkStruct_022114a0 *, int, void *);
};

void func_ov004_022114a0(char *self);

void func_ov004_022114cc(char *self)
{
    UnkStruct_022114cc *o = *(UnkStruct_022114cc **) (*(char **) (self + 4) + 0x2c);
    if (o != 0) {
        o->vt[26](o, *(u8 *) (*(char **) self + 1), self);
    }
    *(void **) (self + 0x24) = (void *) func_ov004_022114a0;
    *(u8 *) (self + 0x92) = 2;
}

void func_ov004_022114a0(char *self)
{
    UnkStruct_022114a0 *o = *(UnkStruct_022114a0 **) (*(char **) (self + 4) + 0x2c);
    if (o != 0) {
        o->vt[27](o, *(u8 *) (*(char **) self + 1), self);
    }
    *(void **) (self + 0x24) = (void *) func_ov004_022114cc;
    *(u8 *) (self + 0x92) = 1;
}
