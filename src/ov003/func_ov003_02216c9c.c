/* func_ov003_02216c9c @ 0x02216c9c, 0x1c0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef char *va_list;

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_02216c9c {
    int pad_00[0x98 / 4];
    int unk_98;
    int pad_9C[(0x7f0 - 0x9c) / 4];
    int unk_7F0;
    int pad_7F4[2];
    int unk_7FC;
    int unk_800;
};

extern int func_0200fc90(struct UnkStruct_02216c9c *self);
extern int func_0200f290(struct UnkStruct_02216c9c *self, int k);
extern int func_ov003_0220d040(struct UnkStruct_02216c9c *self, va_list ap, u8 *mode, Pair *p);
extern int func_02073908(void *a, int b);
extern void *data_020ccf94;

extern int func_ov003_02216bc4(struct UnkStruct_02216c9c *self, int a, int b);
extern int func_ov003_02216410(struct UnkStruct_02216c9c *self, int b, Pair *c, int d, short e);
extern int func_ov003_02216698(struct UnkStruct_02216c9c *self, int b, int c, Pair *d, int e, short f);
extern int func_ov003_02216ab8(struct UnkStruct_02216c9c *self, int b, int c, Pair *d, int e, short f);
extern int func_02008258(struct UnkStruct_02216c9c *self, int a);
extern int func_0200d4e8(struct UnkStruct_02216c9c *self, int a, int b, int c);

int func_ov003_02216c9c(struct UnkStruct_02216c9c *self, int a1)
{
    va_list ap;
    int st;
    u8 mode;
    Pair pair;

    if (self->unk_98 != 0) {
        return -1;
    }

    st = func_0200fc90(self);
    mode = 0;
    if (st != 0xb) {
        if (func_0200f290(self, 0x14) != 0) {
            if (st != 0xa) {
                mode = 1;
            } else {
                mode = 2;
            }
        }
    }

    pair.a = 0;
    pair.b = 0;
    ap = (va_list) &a1;
    st = func_ov003_0220d040(self, ap, &mode, &pair);

    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        mode = 0;
    }

    switch (st) {
        case 0:
            break;
        case 1:
            func_ov003_02216bc4(self, 6, -1);
            break;
        case 2:
        case 3:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 1, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216698(self, mode != 0, st == 3, &t, 6, -1);
            }
            break;
        case 4:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 0, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216ab8(self, mode != 0, 0, &t, 6, -1);
            }
            break;
        case 5:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 6:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 1, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216ab8(self, mode != 0, 1, &t, 6, -1);
            }
            break;
    }
    return st;
}
