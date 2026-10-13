/* func_02090db0 @ 0x02090db0, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    u16 v;
    struct {
        u16 r : 5;
        u16 g : 5;
        u16 b : 5;
        u16 a : 1;
    } c;
} UnkStruct_02090db0;

typedef struct {
    u8 pad_00[0x50];
    u8 unk_50;
} UnkStruct_02090db0_2;
typedef struct {
    UnkStruct_02090db0_2 *p;
} UnkStruct_02090db0_3;
typedef struct {
    u8 pad_00[0x18];
    UnkStruct_02090db0_3 *unk_18;
    u8 pad_1C[0x5a - 0x1c];
    u16 unk_5A;
} UnkStruct_02090db0_4;

extern u16 func_02065858(void);
extern u16 func_020b7074(void);
extern u16 func_02090ed4(UnkStruct_02090db0_4 *);
extern u16 func_02090ebc(void);

void func_02090db0(UnkStruct_02090db0_4 *a0)
{
    volatile UnkStruct_02090db0 v0;
    volatile UnkStruct_02090db0 v2;
    volatile UnkStruct_02090db0 v4;
    volatile UnkStruct_02090db0 v6;
    volatile UnkStruct_02090db0 v8;
    volatile UnkStruct_02090db0 va;
    volatile UnkStruct_02090db0 vc;
    volatile UnkStruct_02090db0 ve;
    u8 flags;

    flags = a0->unk_18->p->unk_50;
    if (flags & 0x80) {
        v4.v = func_02065858();
        va = v4;
        v6 = va;
        if (flags & 0x40) {
            v8.v = func_020b7074();
        } else if (flags & 0x20) {
            v2.v = func_02090ed4(a0);
            vc = v2;
            v8 = vc;
        } else if (flags & 8) {
            v0.v = func_02090ebc();
            ve = v0;
            v8 = ve;
        } else {
            v8.v = 0x7fff;
        }
        v6.c.r = v8.c.r * v6.c.r / 31;
        v6.c.g = v8.c.g * v6.c.g / 31;
        v6.c.b = v8.c.b * v6.c.b / 31;
        a0->unk_5A = v6.v;
    }
}
