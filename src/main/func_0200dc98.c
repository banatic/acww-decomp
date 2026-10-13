/* func_0200dc98 @ 0x0200dc98, 0x794 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    u8 unk_5C[0x32];
    u8 unk_8E[0x134 - 0x8e];
    int unk_134;
    s16 unk_138;
    u8 unk_13A;
    u8 unk_13B;
    int unk_13C;
    u8 unk_140;
    u8 unk_141;
    u8 pad_142[2];
    int unk_144;
    u8 unk_148;
    u8 pad_149[3];
    Vec unk_14C;
    Vec unk_158;
    u8 pad_164[9];
    u8 unk_16D;
    u8 pad_16E[2];
    int unk_170;
    u8 pad_174[0x6f4 - 0x174];
    Vec unk_6F4;
    u8 pad_700[0x7f0 - 0x700];
    int unk_7F0;
} UnkStruct_0200dc98;

typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_0200dc98_2;

extern u8 data_021c75b8;
extern u8 data_021f6c34;
extern u8 data_021f6c38;
extern int data_021c8c9c;
extern void *data_021c80bc;
extern UnkStruct_0200dc98_2 *data_020ccf94;
extern int data_021c67a4;
// The held/trigger words are read again before each group of tests.
extern volatile u16 data_021fbe40[];
extern u16 data_021fbde0;
extern u16 data_021fbde4;
extern const s16 FX_SinCosTable_[];
extern const int data_020d72f4[];
extern const int data_020d7308[];
extern const int data_020d7310[];

extern void func_0200fa1c(Vec *, UnkStruct_0200dc98 *, void *, void *, const void *);
extern int func_0200f290(UnkStruct_0200dc98 *, int);
extern void func_0200f268(UnkStruct_0200dc98 *, int);
extern int func_0200edb0(UnkStruct_0200dc98 *);
extern int func_0200fbe0(UnkStruct_0200dc98 *);
extern int func_020b5d5c(void);
extern void func_020b8db4(void);
extern int func_020ec1e8(void);
extern void func_020eae40(void);
extern void func_0203e110(void);
extern int func_020b6590(void);
extern int func_020b758c(int, Vec *);
extern int func_020b755c(int, Vec *, int *, u8 *);
extern int func_020b7524(int, int, int);
extern u16 *func_0204f5a8(void *, Vec *, int);
extern void func_0204f818(int *, int *, void *);
extern void func_0204f7e0(Vec *, Vec *);
extern int func_0203de78(void);
extern int func_0203e31c(void);
extern int func_0203c57c(int);
extern int func_0203c568(int);
extern void func_0203aa24(int *, int *, Vec *);
extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);
extern int FX_Sqrt(int);
extern int func_020ea9c8(Vec *);
extern int func_020e8ed8(int, int);

void func_0200dc98(UnkStruct_0200dc98 *self)
{
    int va, vb, vc, vd, ve;
    int vf;
    int i;
    int g;
    int h;
    int j;
    int k;
    u8 v30;
    int v34;
    int v38, v3c, v40, v44;
    int v48, v4c;
    Vec v50, v5c, v68;
    Vec w[3];
    Vec v98, va4, vb0;
    int fa, mode, fb;
    int t;
    int m;
    u16 *pp;
    Vec *q;

    fa = 0;
    mode = self->unk_170;
    va = 0;
    vb = 0;
    vc = 0;
    vd = self->unk_141;
    ve = 0;
    func_0200fa1c(&v5c, self, self->unk_5C, self->unk_8E, data_020d7310);
    fb = 0;
    self->unk_140 = 0;
    self->unk_144 = 0;
    self->unk_16D = 0xff;
    if (((data_021c75b8 == 2) ? 1 : fb) == 0) {
        goto end;
    }

    if (func_0200f290(self, 0xb) != 0 || func_0200f290(self, 0x1b) != 0) {
        self->unk_134 = 0;
        self->unk_13A = 0;
        self->unk_13B = 0;
        self->unk_13C = 0;
        self->unk_141 = 0;
        self->unk_148 = 0;
        self->unk_158.x = v5c.x;
        self->unk_158.y = v5c.y;
        self->unk_158.z = v5c.z;
        if (func_0200f290(self, 0x1b) == 0) {
            goto end;
        }
        if (func_020b5d5c() != 1) {
            goto end;
        }
        if (func_0200edb0(self) != 0) {
            goto end;
        }
        func_0200f268(self, 0x1b);
        func_020b8db4();
        if (data_020ccf94->unk_64 == 0) {
            if ((u8) (func_020ec1e8() + 0xfd) <= 1) {
                func_020eae40();
            }
        }
        t = self->unk_7F0;
        if (t == 2 || t == 0x83 || t == 0x28 || t == 8) {
            func_0203e110();
        }
        goto end;
    }

    if (data_021c8c9c != 0) {
        goto tail;
    }
    vc = func_020b758c(func_020b6590(), &v50);
    if (func_020b755c(func_020b6590(), &v68, &v34, &v30) == 0) {
        goto tail;
    }
    fb = 1;
    switch (v34) {
        case 1:
            if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? fb : 0) == 0) {
                break;
            }
            fa = 1;
            v5c.x = v50.x;
            v5c.y = v50.y;
            v5c.z = v50.z;
            break;
        case 2:
        case 3:
        case 6:
        case 7:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? fb : 0) == 0) {
                break;
            }
            va = 1;
            vb = func_020b7524(func_020b6590(), 0, 0);
            v5c.x = v50.x;
            v5c.y = v50.y;
            v5c.z = v50.z;
            break;
        case 5:
            if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? fb : 0) == 0) {
                break;
            }
            self->unk_144 = 1;
            if (func_0200fbe0(self) != 1) {
                self->unk_14C.x = v68.x;
                self->unk_14C.y = v68.y;
                self->unk_14C.z = v68.z;
                q = &self->unk_14C;
                v5c.x = q->x;
                v5c.y = q->y;
                v5c.z = q->z;
                break;
            } else {
                pp = func_0204f5a8(data_021c80bc, &v68, 0);
                m = 0;
                if (*pp >= 0xfc && *pp <= 0xfd) {
                    m = 1;
                }
                if (m != 0) {
                    v38 = 0;
                    v3c = 0;
                    v40 = 0;
                    v44 = 0;
                    func_0204f818(&v38, &v3c, self->unk_5C);
                    func_0204f818(&v40, &v44, &v50);
                    if (v38 != v40) {
                        goto arm50;
                    }
                    if (v3c == v44) {
                        goto arm68;
                    }
                arm50:
                    self->unk_14C.x = v50.x;
                    self->unk_14C.y = v50.y;
                    self->unk_14C.z = v50.z;
                    q = &self->unk_14C;
                    v5c.x = q->x;
                    v5c.y = q->y;
                    v5c.z = q->z;
                    break;
                arm68:
                    self->unk_14C.x = v68.x;
                    self->unk_14C.y = v68.y;
                    self->unk_14C.z = v68.z;
                    q = &self->unk_14C;
                    v5c.x = q->x;
                    v5c.y = q->y;
                    v5c.z = q->z;
                    break;
                } else {
                    self->unk_14C.x = v68.x;
                    self->unk_14C.y = v68.y;
                    self->unk_14C.z = v68.z;
                    q = &self->unk_14C;
                    v5c.x = q->x;
                    v5c.y = q->y;
                    v5c.z = q->z;
                    break;
                }
            }
        case 4:
            if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? fb : 0) == 0) {
                break;
            }
            self->unk_144 = 2;
            self->unk_14C.x = v68.x;
            self->unk_14C.y = v68.y;
            self->unk_14C.z = v68.z;
            q = &self->unk_14C;
            v5c.x = q->x;
            v5c.y = q->y;
            v5c.z = q->z;
            break;
        case 8:
        case 10:
            if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? fb : 0) != 0) {
                ve = 1;
                func_0204f7e0(&v68, &v68);
                v5c.x = v68.x;
                v5c.y = v68.y;
                v5c.z = v68.z;
            }
            self->unk_16D = v30;
            break;
    }

tail:
    if (fa != 0 || (func_0203de78() != 0 && vc == 0)) {
        self->unk_134 = 0;
        self->unk_13A = 0;
        vd = 1;
        self->unk_140 = 1;
        func_0200fa1c(&va4, self, self->unk_5C, self->unk_8E, data_020d72f4);
        v5c.x = va4.x;
        v5c.y = va4.y;
        v5c.z = va4.z;
        mode = 2;
        goto store;
    }
    fa = 0;
    self->unk_140 = 0;
    if (self->unk_170 == 2) {
        if (vc != 0) {
            mode = 2;
        } else {
            mode = 1;
        }
    } else {
        if ((data_021fbe40[0] & 0x2ff3) != 0) {
            mode = 1;
        } else if (vc != 0) {
            mode = 2;
        }
    }
    if (mode == 2) {
        if (self->unk_7F0 >= 0x1d && self->unk_7F0 <= 0x23) {
            g = data_021c67a4;
            w[1].x = self->unk_6F4.x;
            w[1].y = self->unk_6F4.y;
            w[1].z = self->unk_6F4.z;
            h = (int) (u16) (s16) (0x4000 - func_0203c57c(g)) >> 4;
            h = h * 2;
            k = FX_Div(FX_MulFunc(0x1266, FX_SinCosTable_[h]), FX_SinCosTable_[h + 1]);
            j = (int) (u16) func_0203c568(g) >> 4;
            j = j * 2;
            w[2].x = w[1].x - FX_MulFunc(k, FX_SinCosTable_[j]);
            w[2].z = w[1].z - FX_MulFunc(k, FX_SinCosTable_[j + 1]);
            w[0].x = v50.x - w[2].x;
            w[0].z = v50.z - w[2].z;
            // Horizontal magnitude consumes x/z only; y is not initialized.
            t = func_020ea9c8(&w[0]);
        } else {
            w[0].x = v50.x - self->unk_6F4.x;
            w[0].z = v50.z - self->unk_6F4.z;
            // The third argument survives in r2 from the position load.
            func_0203aa24(&v48, &v4c, &self->unk_6F4);
            v48 = v48 + 0x80;
            v4c = v4c + 0x60;
            v98.x = ((u8) data_021fbde0 - v48) << 8;
            v98.y = 0;
            v98.z = ((u8) data_021fbde4 - v4c) << 8;
            t = func_020ea9c8(&v98);
        }
        t = FX_MulFunc(t, 0x4f4);
        if (t >= 0x1000) {
            t = 0x1000;
        } else if (t <= 0x19a) {
            t = 0;
        } else {
            vf = FX_Sqrt(FX_Div((t + 0x39a) << 12, 0x139a) >> 12);
            t = vf;
            vf = vf << 12;
            i = 0;
            do {
                t = FX_MulFunc(t, vf) >> 12;
                i = i + 1;
            } while (i < 3);
            if (t > 0x1000) {
                t = 0x1000;
            } else if (t < 0) {
                t = 0;
            }
        }
        self->unk_134 = t;
        if (t > 0xc32) {
            fa = 1;
        }
        if (t > 0) {
            self->unk_138 = (s16) func_020e8ed8(w[0].x, w[0].z);
        }
        if (fb != 0) {
            goto store13a;
        }
        if ((((data_021f6c38 != 0) && (data_021f6c34 != 0)) ? 1 : 0) == 0) {
            goto store13a;
        }
        ve = 1;
        v5c.x = v50.x;
        v5c.y = v50.y;
        v5c.z = v50.z;
        goto store13a;
    }
    if (func_0203e31c() != 0 || func_0200f290(self, 0x13) != 0) {
        m = 0x2fff;
    } else {
        m = 0x2ff3;
    }
    t = data_021fbe40[0];
    if ((m & t) != 0) {
        mode = 1;
    } else {
        mode = self->unk_170;
    }
    if ((t & 2) != 0 || (t & 0x100) != 0 || (t & 0x200) != 0) {
        fa = 1;
    } else {
        fa = 0;
    }
    t = data_021fbe40[1];
    va = 1;
    if ((t & 1) == 0) {
        va = 0;
    }
    self->unk_140 = (u8) va;
    if ((data_021fbe40[0] & 1) != 0) {
        vd = 1;
    } else {
        vd = 0;
        if ((data_021fbe40[1] & 2) != 0) {
            ve = 1;
            func_0200fa1c(&vb0, self, self->unk_5C, self->unk_8E, data_020d7308);
            v5c.x = vb0.x;
            v5c.y = vb0.y;
            v5c.z = vb0.z;
        }
    }
    t = data_021fbe40[0];
    if ((t & 0x80) != 0 || (t & 0x40) != 0 || (t & 0x10) != 0 || (t & 0x20) != 0) {
        if (fa != 0) {
            self->unk_134 = 0x1000;
        } else {
            self->unk_134 = 0xc32;
        }
        self->unk_138 = (s16) ((const s16 *) data_021fbe40)[2];
    } else {
        self->unk_134 = 0;
    }
store13a:
    self->unk_13A = (u8) fa;
store:
    self->unk_13B = (u8) va;
    self->unk_13C = vb;
    self->unk_141 = (u8) vd;
    self->unk_148 = (u8) ve;
    self->unk_158.x = v5c.x;
    self->unk_158.y = v5c.y;
    self->unk_158.z = v5c.z;
    self->unk_170 = mode;
end:
    return;
}
