/* func_0200f434 @ 0x0200f434, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0200f434;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_0200f434 unk_5C;
    UnkStruct_0200f434 unk_68;
    u8 pad_74[0x8e - 0x74];
    s16 unk_8E;
} UnkStruct_0200f434_2;

extern s16 FX_SinCosTable_[];
extern int func_0200f5e4(UnkStruct_0200f434_2 *a, UnkStruct_0200f434 *t, s16 *ang);
extern int func_020ea990(UnkStruct_0200f434 *p, UnkStruct_0200f434 *q);
extern int func_020e8ed8(int dx, int dz);
extern int func_020e8b4c(int a, int b);
extern int FX_MulFunc(int a, int b);

int func_0200f434(UnkStruct_0200f434_2 *a, UnkStruct_0200f434 *b)
{
    UnkStruct_0200f434 *q;
    UnkStruct_0200f434 *w;
    s16 ang;
    UnkStruct_0200f434 t;

    q = &a->unk_5C;
    if (func_0200f5e4(a, &t, &ang) != 0) {
        if (func_020ea990(&t, b) >= 0x4000) {
            ang = func_020e8ed8(b->x - q->x, b->z - q->z);
            t.x = b->x - FX_MulFunc(0x2000, FX_SinCosTable_[((u16) ang >> 4) * 2]);
            t.z = b->z - FX_MulFunc(0x2000, FX_SinCosTable_[((u16) ang >> 4) * 2 + 1]);
        } else {
            ang = a->unk_8E;
        }
    } else {
        return 1;
    }
    if (func_020ea990(q, &t) <= 0x200) {
        if (func_020e8b4c(a->unk_8E, ang) < 0x100) {
            return 1;
        }
    }
    if (func_020ea990(q, &t) >= 0xe000) {
        w = &a->unk_68;
        a->unk_68.x = t.x;
        w->y = t.y;
        w->z = t.z;
        q->x = a->unk_68.x;
        q->y = w->y;
        q->z = w->z;
        a->unk_8E = ang;
        return 1;
    } else {
        return 0;
    }
}
