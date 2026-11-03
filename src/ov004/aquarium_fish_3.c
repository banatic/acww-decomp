/* aquarium_fish_3: 17 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022361c4 @ 0x022361c4, 0x128 bytes, Thumb
 * func_ov004_02236168 @ 0x02236168, 0x5c bytes, Thumb
 * func_ov004_02236110 @ 0x02236110, 0x58 bytes, Thumb
 * func_ov004_022360ac @ 0x022360ac, 0x64 bytes, Thumb
 * func_ov004_02236078 @ 0x02236078, 0x34 bytes, Thumb
 * func_ov004_02235fe4 @ 0x02235fe4, 0x94 bytes, Thumb
 * func_ov004_02235fe0 @ 0x02235fe0, 0x2 bytes, Thumb
 * func_ov004_02235f10 @ 0x02235f10, 0xd0 bytes, Thumb
 * func_ov004_02235eac @ 0x02235eac, 0x64 bytes, Thumb
 * func_ov004_02235e58 @ 0x02235e58, 0x54 bytes, Thumb
 * func_ov004_02235ddc @ 0x02235ddc, 0x7c bytes, Thumb
 * func_ov004_02235c54 @ 0x02235c54, 0x188 bytes, Thumb
 * func_ov004_02235b28 @ 0x02235b28, 0x12c bytes, Thumb
 * func_ov004_02235ac4 @ 0x02235ac4, 0x64 bytes, Thumb
 * func_ov004_02235a18 @ 0x02235a18, 0xac bytes, Thumb
 * func_ov004_022359c8 @ 0x022359c8, 0x50 bytes, Thumb
 * func_ov004_0223592c @ 0x0223592c, 0x9c bytes, Thumb
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))

struct UnkStruct_02235fe4 {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x164 - 0x15c];
    u8 unk_164;
    u8 pad_165[0x1a8 - 0x165];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
    u8 pad_1C2[0x1ee - 0x1c2];
    u8 unk_1EE;
    u8 pad_1EF[0x20c - 0x1ef];
    int unk_20C;
    int unk_210;
    u8 pad_214[0x24c - 0x214];
    s16 unk_24C;
    u8 pad_24E[0x253 - 0x24e];
    u8 unk_253;
};

struct UnkStruct_02235f10 {
    u8 pad_00[0x158];
    int unk_158;
    int unk_15C;
    u8 pad_160[0x1ac - 0x160];
    int unk_1AC;
    u8 pad_1B0[0x1c2 - 0x1b0];
    s16 unk_1C2;
    u8 pad_1C4[0x1ca - 0x1c4];
    signed char unk_1CA;
    u8 pad_1CB[0x1cc - 0x1cb];
    int unk_1CC;
    u8 pad_1D0[0x1e8 - 0x1d0];
    u8 unk_1E8;
    u8 pad_1E9[0x1ee - 0x1e9];
    u8 unk_1EE;
    u8 pad_1EF[0x1f1 - 0x1ef];
    u8 unk_1F1;
    u8 pad_1F2[0x202 - 0x1f2];
    u8 unk_202;
    u8 unk_203;
    u8 unk_204;
    u8 unk_205;
    u8 pad_206[0x228 - 0x206];
    int unk_228;
    u8 pad_22C[0x23c - 0x22c];
    int unk_23C;
};

typedef struct {
    int x, y, z;
} Vec;

struct UnkStruct_02235a18 {
    u8 pad_00[0x1a8];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
};

struct UnkStruct_02235a18_2 {
    struct UnkStruct_02235a18 *p;
};

struct UnkStruct_0223592c {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c0 - 0x160];
    s16 unk_1C0;
    s16 unk_1C2;
    u8 pad_1C4[0x1ee - 0x1c4];
    u8 unk_1EE;
    u8 pad_1EF[0x20c - 0x1ef];
    int unk_20C;
    u8 pad_210[0x22f - 0x210];
    u8 unk_22F;
};

extern short func_ov004_02239474(int, int);
extern int func_ov004_02239460(int, int);
extern int func_ov004_02239bb4(void *, int, int);
extern void func_020e8a94(void *p, int a, int b, int c);
extern u8 data_ov004_02247928[];
extern u8 *data_ov004_022594d4[];
extern u8 data_ov004_02247927[];
extern u8 data_ov004_02247924[];
extern void func_ov004_0223635c(void *, void *);
extern int func_020e89dc(short *, int, int);
extern int func_0200322c(Vec *, Vec *);

void func_ov004_02235b28(unsigned char *self);
void func_ov004_02235ac4(char *self);
void func_ov004_022359c8(char *a, char **bp);

void func_ov004_022361c4(unsigned char *self)
{
    *(int *) (self + 0x20c) = 0;
    if (self[0x1fd] == 2) {
        *(short *) (self + 0x1c2) += func_ov004_02239474(180, 150);
        ++self[0x1eb];
    } else {
        *(short *) (self + 0x1c2) += func_ov004_02239474(*(unsigned short *) (self + 0x230), 0);
        self[0x1eb] = 0;
    }
    *(int *) (self + 0x158) = 0;
    self[0x202] = func_ov004_02239460(self[0x205], self[0x204]);
    self[0x203] = func_ov004_02239460(self[0x207], self[0x206]);
    *(int *) (self + 0x23c) = 0;
    if (self[0x1e8] == *(int *) (self + 0x15c)) {
        if (*(int *) (self + 0x1ac) >= *(int *) (self + 0x1cc)) {
            *(signed char *) (self + 0x1ca) = -1;
        } else if (*(int *) (self + 0x1ac) <= *(int *) (self + 0x228)) {
            *(signed char *) (self + 0x1ca) = 1;
        } else {
            *(signed char *) (self + 0x1ca) = func_ov004_02239460(0, 2) > 0 ? 1 : -1;
        }
    }
    self[0x24e] = 0;
    self[0x1ee] = 3;
    self[0x22f] = 1;
}

void func_ov004_02236168(char *self)
{
    *(int *) (self + 0x20c) = *(int *) (self + 0x214) * *(int *) (self + 0x158);
    func_ov004_02239bb4(self + 0x1a8, *(int *) (self + 0x20c), *(s16 *) (self + 0x1c0));
    if (*(int *) (self + 0x20c) >= *(int *) (self + 0x210)) {
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x1ee) = 4;
    }
}

void func_ov004_02236110(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x20c) = *(int *) (self + 0x210);
    func_ov004_02239bb4(self + 0x1a8, *(int *) (self + 0x20c), *(short *) (self + 0x1c0));
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x202)) {
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x5;
    }
}

void func_ov004_022360ac(char *self)
{
    *(int *) (self + 0x20c) = *(int *) (self + 0x210) - *(int *) (self + 0x218) * *(int *) (self + 0x158);
    func_ov004_02239bb4(self + 0x1a8, *(int *) (self + 0x20c), *(s16 *) (self + 0x1c0));
    if (*(int *) (self + 0x20c) <= 0) {
        *(int *) (self + 0x20c) = 0;
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x1ee) = 6;
    }
}

void *func_ov004_02236078(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x20c) = 0x0;
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x203)) {
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x2;
        return self;
    }
    return self;
}

void func_ov004_02235fe4(struct UnkStruct_02235fe4 *self)
{
    if (self->unk_158 <= 0x28) {
        if ((u8) (self->unk_164 + 0xfc) <= 1) {
            func_020e8a94(&self->unk_1C0, self->unk_24C, 3, 0xaaa);
        } else {
            func_020e8a94(&self->unk_1C0, self->unk_24C, 2, 0x4000);
        }
        self->unk_20C = self->unk_210;
        func_ov004_02239bb4(&self->unk_1A8, self->unk_20C, self->unk_1C0);
    } else {
        self->unk_253 = 0;
        self->unk_1EE = 2;
    }
}

void func_ov004_02235fe0(void) {}

void func_ov004_02235f10(struct UnkStruct_02235f10 *self)
{
    int v;

    self->unk_158 = 1;
    self->unk_202 = func_ov004_02239460(self->unk_205, self->unk_204);
    self->unk_203 = 0;
    self->unk_23C = 0;
    if (self->unk_1F1 != 0) {
        self->unk_1C2 = self->unk_1C2 + (int) func_ov004_02239474(0x1e, 0xf);
    }
    if (self->unk_1E8 == self->unk_15C) {
        if (self->unk_1AC >= self->unk_1CC) {
            self->unk_1CA = -1;
        } else if (self->unk_1AC <= self->unk_228) {
            self->unk_1CA = 1;
        } else {
            if (func_ov004_02239460(0, 2) > 0) {
                v = 1;
            } else {
                v = -1;
            }
            self->unk_1CA = v;
        }
    }
    self->unk_1EE = 3;
}

void func_ov004_02235eac(void *self)
{
    int *p;

    p = (int *) ((char *) self + 0x20c);
    *p = *(int *) ((char *) self + 0x210) - *(int *) ((char *) self + 0x218) * *(int *) ((char *) self + 0x158);
    func_ov004_02239bb4((char *) self + 0x1a8, *p, *(short *) ((char *) self + 0x1c0));
    if (*(int *) ((char *) self + 0x20c) <= 0xf6) {
        *(int *) ((char *) self + 0x20c) = 0xf6;
        *(int *) ((char *) self + 0x158) = 3;
        *((char *) self + 0x1ee) = 2;
    }
}

void func_ov004_02235e58(char *self)
{
    s16 v = *(s16 *) (self + 0x1c0);
    int a = v < 0 ? -v : v;
    if (a > 0x5554) {
        if (v >= 0) {
            *(s16 *) (self + 0x1c0) = 0x5554;
        } else {
            *(s16 *) (self + 0x1c0) = (s16) 0xffffaaac;
        }
    } else if (a < 0x2aac) {
        if (v >= 0) {
            *(s16 *) (self + 0x1c0) = 0x2aac;
        } else {
            *(s16 *) (self + 0x1c0) = (s16) 0xffffd554;
        }
    }
}

void func_ov004_02235ddc(char *self)
{
    int lim, hi, v;
    if (*(u8 *) (self + 0x1c8) == 1) {
        lim = 0;
        hi = 0x22;
    } else {
        lim = -2;
        hi = 0x24;
    }
    v = *(int *) (self + 0x1a8) >> 12;
    if (v <= lim) {
        *(s16 *) (self + 0x1c0) = 0x4000;
        *(int *) (self + 0x1ac) = (data_ov004_02247928[*(int *) (self + 0x15c) * 0x11] << 12) >> 6;
    } else if (v >= hi) {
        *(s16 *) (self + 0x1c0) = (s16) 0xffffc000;
        *(int *) (self + 0x1ac) = (data_ov004_02247928[*(int *) (self + 0x15c) * 0x11] << 12) >> 6;
    }
}

void func_ov004_02235c54(u8 *self)
{
    if (self[0x1ee] == 1) {
        return;
    }
    if (self[0x40]) {
        if (!self[0x1f1]) {
            func_ov004_02235ac4((char *) self);
            self[0x1ca] = 1;
            return;
        }
        if (self[0x252] != self[0x1e8]) {
            self[0x252] = self[0x1e8];
            self[0x254] = 0;
        } else {
            u8 ticks;
            self[0x254]++;
            ticks = self[0x254];
            if (ticks >= 125) {
                u8 *other = data_ov004_022594d4[self[0x1e8]];
                if (!other) {
                    return;
                }
                if (data_ov004_02247927[W(self, 0x15c) * 17] <= data_ov004_02247927[W(other, 0x15c) * 17]) {
                    func_ov004_0223635c(self, other + 0x1a8);
                    self[0x254] = 0;
                    return;
                }
                if (ticks >= 145) {
                    func_ov004_0223635c(self, other + 0x1a8);
                    self[0x254] = 0;
                    return;
                }
            }
        }
        if (self[0x1ee] == 6 || (self[0x1ee] == 5 && W(self, 0x15c) >= 35)) {
            self[0x1ee] = 2;
        }
        if ((self[0x1ea] & 8) || (self[0x1ea] & 16)) {
            if (self[0x1ee] != 4 && data_ov004_02247924[W(self, 0x15c) * 17] <= data_ov004_02247924[self[0x1e8] * 17]) {
                self[0x1ee] = 4;
                W(self, 0x158) = 0;
            }
        }
        if (self[0x1ea] >= 64) {
            if (!self[0x1c9]) {
                func_ov004_02235b28((unsigned char *) self);
            }
        } else if (self[0x1ea] & 32) {
            self[0x1ca] = 1;
            self[0x1c9] = 1;
        }
        func_020e89dc((short *) (self + 0x1c0), S(self, 0x1ec), 0x38e);
    } else {
        func_ov004_02235ac4((char *) self);
    }
}

void func_ov004_02235b28(unsigned char *self)
{
    int own;
    unsigned char **slot;
    Vec *position;
    unsigned char *other;
    int angle;
    int theirs;
    slot = &((unsigned char * *) data_ov004_022594d4)[self[0x1e8]];
    other = *slot;
    if (other) {
        position = (Vec *) (other + 0x1a8);
        own = *(short *) (self + 0x1c0);
        if (own < 0) {
            own = -own;
        }
        angle = *(short *) (other + 0x1c0);
        theirs = angle < 0 ? -angle : angle;
        if (own >= 0x4000 && theirs >= 0x4000) {
            if (*(int *) (self + 0x1b0) > position->z) {
                *(short *) (self + 0x1ec) = angle + 0x8000;
            } else if (!other[0x1c9]) {
                other[0x1c9] = 1;
                (*slot)[0x1e9] = *(int *) (self + 0x15c);
                *(short *) (*slot + 0x1ec) = *(short *) (self + 0x1c0) + 0x8000;
            }
            func_ov004_022359c8((char *) self, (char **) slot);
        } else if (own <= 0x4000 && theirs <= 0x4000) {
            if (*(int *) (self + 0x1b0) < position->z) {
                *(short *) (self + 0x1ec) = angle + 0x8000;
            } else if (!other[0x1c9]) {
                other[0x1c9] = 1;
                (*slot)[0x1e9] = *(int *) (self + 0x15c);
                *(short *) (*slot + 0x1ec) = *(short *) (self + 0x1c0) + 0x8000;
            }
            func_ov004_022359c8((char *) self, (char **) slot);
        } else {
            int target = func_0200322c(position, (Vec *) (self + 0x1a8));
            if ((short) (target - *(short *) (self + 0x1c0)) < 0) {
                *(short *) (self + 0x1ec) = target - 0x4000;
            } else {
                *(short *) (self + 0x1ec) = target + 0x4000;
            }
        }
    }
}

void func_ov004_02235ac4(char *self)
{
    u8 i;
    *(u8 *) (self + 0x1ea) = 0;
    *(u8 *) (self + 0x1c9) = 0;
    *(s16 *) (self + 0x1ec) = *(s16 *) (self + 0x1c0);
    i = *(u8 *) (self + 0x1e8);
    if (i != *(volatile int *) (self + 0x15c)) {
        char *e = ((char * *) data_ov004_022594d4)[i];
        if (e != 0) {
            *(u8 *) (e + 0x1c9) = 0;
        }
        *(u8 *) (self + 0x1e8) = (u8) * (volatile int *) (self + 0x15c);
        *(u8 *) (self + 0x1e9) = (u8) * (volatile int *) (self + 0x15c);
    }
}

int func_ov004_02235a18(struct UnkStruct_02235a18 *self, struct UnkStruct_02235a18_2 *e)
{
    // DECLS
    int d;
    int a;
    struct UnkStruct_02235a18 *o;
    int y;
    int x;
    // ENDDECLS

    o = e->p;
    a = o->unk_1C0;
    d = (s16) (func_0200322c((Vec *) (&self->unk_1A8), (Vec *) (&o->unk_1A8)) - 0x4000);
    x = (s16) (self->unk_1C0 - d);
    y = (s16) (a - d);
    if (x * y < 0) {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 0x40;
        }
        return 0x80;
    } else if (x < 0) {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 8;
        }
        return 0x10;
    } else {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 2;
        }
        return 4;
    }
}

void func_ov004_022359c8(char *a, char **bp)
{
    if (*(int *) (a + 0x1cc) < *(int *) (*bp + 0x1cc)) {
        *(a + 0x1ca) = -1;
        if (*(unsigned char *) (*bp + 0x1c9) == 0) {
            *(*bp + 0x1ca) = 1;
        }
    } else {
        *(a + 0x1ca) = 1;
        if (*(unsigned char *) (*bp + 0x1c9) == 0) {
            *(*bp + 0x1ca) = -1;
        }
    }
}

void func_ov004_0223592c(struct UnkStruct_0223592c *self)
{
    int ok;

    if ((self->unk_20C <= 0x99a && self->unk_1EE == 5) || self->unk_1EE == 1 || self->unk_22F == 0) {
        return;
    }
    if (data_ov004_02247924[self->unk_15C * 0x11] >= 4) {
        ok = func_020e89dc((short *) (&self->unk_1C0), self->unk_1C2, 0x88) != 0;
    } else {
        ok = func_020e89dc((short *) (&self->unk_1C0), self->unk_1C2, 0x16c) != 0;
    }
    if (ok) {
        self->unk_22F = 0;
    }
}
