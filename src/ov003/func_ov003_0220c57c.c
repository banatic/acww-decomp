/* func_ov003_0220c57c @ 0x0220c57c, 0x3b8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

// arr[1] is the output of func_0200fa1c, arr[2] is the saved copy, arr[0] is unused.

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    Vec unk_5C; // 0x5c
    u8 pad_68[0x140 - 0x68];
    u8 unk_140; // 0x140
    u8 pad_141[3];
    int unk_144; // 0x144
    u8 unk_148;  // 0x148
    u8 pad_149[0x158 - 0x149];
    Vec unk_158; // 0x158
    u8 pad_164[0x170 - 0x164];
    int unk_170; // 0x170
    u8 pad_174[0x6f4 - 0x174];
    int unk_6F4; // 0x6f4
    u8 pad_6F8[0x6fc - 0x6f8];
    int unk_6FC; // 0x6fc
} UnkStruct_0220c57c;

extern int data_021c80bc;
extern int data_ov003_02236608[];

extern int func_0200fbe0(UnkStruct_0220c57c *);
extern int func_0201005c(UnkStruct_0220c57c *, Vec *, int);
extern int func_02010004(UnkStruct_0220c57c *, int);
extern int func_ov003_0220c3d0(UnkStruct_0220c57c *, int, Vec *);
extern int func_ov003_0220d1a8(UnkStruct_0220c57c *, int *);
extern void func_0204f818(int *, int *, Vec *);
extern u16 *func_0204f5e0(int, int, int, int, int, int);
extern int func_02031614(Vec *);
extern int func_020ba310(void);
extern void func_ov003_0220ea40(UnkStruct_0220c57c *, int, int);
extern void func_0200fa1c(Vec *, UnkStruct_0220c57c *, Vec *, s16 *, int *);
extern int func_020e8ed8(int, int);

int func_ov003_0220c57c(UnkStruct_0220c57c *self)
{
    int ev;
    int lx;
    int ly;
    int gx;
    int gy;
    int qx;
    int qy;
    int h;
    int f;
    int e;
    int d;
    int c;
    int fl[3];
    int g;
    u16 t;
    u16 *rec;
    s16 ang;
    Vec arr[3];
    Vec z;
    Vec v1;
    Vec v2;
    Vec v3;
    int *p158;
    int *p15c;
    int *p160;

    ev = func_0200fbe0(self);
    if (self->unk_140 != 0) {
        z.x = 0;
        z.y = 0;
        z.z = 0;
        if (func_ov003_0220c3d0(self, ev, &z) != 0) {
            return 1;
        }
    }
    if (func_0201005c(self, &self->unk_158, ev) == 0) {
        if (self->unk_144 == 1 || self->unk_148 != 0) {
            if (func_02010004(self, ev) == 0) {
                goto tail;
            }
            return 1;
        }
        goto tail;
    }

    switch (self->unk_144) {
        case 1:
            if (self->unk_144 != 0) {
                if (func_ov003_0220d1a8(self, &ev) != 0) {
                    return 1;
                }
            }
            if (ev == 2 || ev == 1 || ev == 0xa || ev == 0) {
                if (self->unk_144 != 0) {
                    if (ev == 0xa) {
                        v1.x = self->unk_158.x;
                        v1.y = self->unk_158.y;
                        v1.z = self->unk_158.z;
                        if (func_ov003_0220c3d0(self, 0, &v1) != 0) {
                            return 1;
                        }
                    } else {
                        v2.x = self->unk_158.x;
                        v2.y = self->unk_158.y;
                        v2.z = self->unk_158.z;
                        if (func_ov003_0220c3d0(self, ev, &v2) != 0) {
                            return 1;
                        }
                    }
                }
            }
            break;
        case 2:
            if (ev == 4) {
                z.x = 0;
                z.y = 0;
                z.z = 0;
                if (func_ov003_0220c3d0(self, ev, &z) != 0) {
                    return 1;
                }
            }
    }

    if (self->unk_170 == 2 && ev == 5) {
        func_0204f818(&gx, &gy, &self->unk_158);
        lx = gx;
        ly = gy;
        qx = lx >> 4;
        qy = ly >> 4;
        rec = func_0204f5e0(data_021c80bc, qx, qy, lx - (qx << 4), ly - (qy << 4), 0);
        if (rec != 0) {
            g = 1;
            h = 1;
            f = 1;
            e = 1;
            d = 1;
            c = 1;
            fl[2] = 1;
            fl[1] = 0;
            t = rec[0];
            if (t <= 5) {
                fl[1] = 1;
            }
            if (fl[1] == 0) {
                if (!(t >= 6 && t <= 0xb)) {
                    fl[2] = 0;
                }
            }
            if (fl[2] == 0) {
                if (!(t >= 0xc && t <= 0x11)) {
                    c = 0;
                }
            }
            if (c == 0) {
                if (!((t >= 0x12 && t <= 0x19) || t == 0x1c)) {
                    d = 0;
                }
            }
            if (d == 0) {
                if (!((t >= 0x8a && t <= 0x8f) || (t >= 0x90 && t <= 0x95) || (t >= 0x96 && t <= 0x9b) ||
                      (t >= 0x9c && t <= 0xa3) || t == 0xa5)) {
                    e = 0;
                }
            }
            if (e == 0) {
                if (t != 0x1a) {
                    f = 0;
                }
            }
            if (f == 0) {
                if (t != 0xa4) {
                    h = 0;
                }
            }
            if (h == 0) {
                if (t != 0x1d) {
                    g = 0;
                }
            }
            if (g != 0) {
                goto doit;
            }
            if (t >= 0x6e && t <= 0x73) {
                goto doit;
            }
            if (t >= 0x74 && t <= 0x79) {
                goto doit;
            }
            if (t >= 0x7a && t <= 0x7f) {
                goto doit;
            }
            if (t >= 0x80 && t <= 0x87) {
                goto doit;
            }
            if (t == 0x88) {
                goto doit;
            }
            if (t != 0x89) {
                goto nodoit;
            }
        doit:
            z.x = 0;
            z.y = 0;
            z.z = 0;
            if (func_ov003_0220c3d0(self, ev, &z) != 0) {
                return 1;
            }
        nodoit:;
        }
    }

    if (self->unk_148 != 0) {
        if (func_02010004(self, ev) != 0) {
            return 1;
        }
    }
    if (self->unk_170 != 2) {
        goto tail;
    }

    switch (ev) {
        case 1:
            ang = (s16) func_020e8ed8(self->unk_158.x - self->unk_6F4, self->unk_158.z - self->unk_6FC);
            func_0200fa1c(&arr[1], self, &self->unk_5C, &ang, data_ov003_02236608);
            if (func_0201005c(self, &arr[1], ev) == 0) {
                goto tail;
            }
            p158 = &self->unk_158.x;
            arr[2].x = *p158;
            p15c = &self->unk_158.y;
            arr[2].y = *p15c;
            p160 = &self->unk_158.z;
            arr[2].z = *p160;
            *p158 = arr[1].x;
            *p15c = arr[1].y;
            *p160 = arr[1].z;
            z.x = 0;
            z.y = 0;
            z.z = 0;
            if (func_ov003_0220c3d0(self, ev, &z) != 0) {
                self->unk_158.x = arr[2].x;
                self->unk_158.y = arr[2].y;
                self->unk_158.z = arr[2].z;
                return 1;
            }
            self->unk_158.x = arr[2].x;
            self->unk_158.y = arr[2].y;
            self->unk_158.z = arr[2].z;
            goto tail;
        case 5:
            z.x = 0;
            z.y = 0;
            z.z = 0;
            if (func_ov003_0220c3d0(self, ev, &z) != 0) {
                return 1;
            }
            goto tail;
        case 3:
            if (func_02031614(&self->unk_158) == 0) {
                goto tail;
            }
            v3.x = self->unk_158.x;
            v3.y = self->unk_158.y;
            v3.z = self->unk_158.z;
            if (func_ov003_0220c3d0(self, ev, &v3) != 0) {
                return 1;
            }
            goto tail;
    }

tail:
    if (ev == 0 && self->unk_140 != 0 && func_020ba310() != 0) {
        func_ov003_0220ea40(self, 6, -1);
        return 1;
    }
    return 0;
}
