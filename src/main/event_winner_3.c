/* event_winner_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02086d24 @ 0x02086d24, 0x18c bytes, Thumb
 * func_020868e8 @ 0x020868e8, 0x43c bytes, Thumb
 * func_020868c0 @ 0x020868c0, 0x28 bytes, Thumb
 * func_020868a0 @ 0x020868a0, 0x20 bytes, Thumb
 * func_02086874 @ 0x02086874, 0x2c bytes, Thumb
 * func_0208683c @ 0x0208683c, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x1e];
    unsigned short unk_1E;
    char pad_20[0x1e];
    unsigned short unk_3E;
    int unk_40;
    unsigned char unk_44;
    unsigned char unk_45;
    unsigned char unk_46;
    unsigned char unk_47;
} UnkStruct_02086d24;

typedef struct {
    u16 unk_00;
    u8 pad_02[0x1e - 2];
    u16 unk_1E;
    u8 pad_20[0x3e - 0x20];
    u16 unk_3E;
    int unk_40;
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
} UnkStruct_020868e8;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09[3];
    u8 unk_0C[8];
    int unk_14;
    int unk_18;
} Rec;

typedef struct {
    Rec r;
    int bB1[0x10];
    int bB2[0x10];
    int bB3[0x10];
    int bA[8];
    int bC[0xa];
    int big[0x40];
} Locals;

struct UnkStruct_020868c0 {
    char pad_00[0x1e];
    char unk_1E[0x10];
    char unk_2E[0x10];
    unsigned short unk_3E;
};

extern int func_020951bc(void *);
extern int func_02003704(void *);
extern void func_0209f100(void *, int);
extern int func_0209f150(void *, int);
extern void *func_02094fd4(void *);
extern void *func_02095074(void *, void *);
extern int func_02003618(void *, void *);
extern int func_0203d7b0(int, int);
extern int func_0203d79c(int, int);
extern int func_0203d7c4(int, void *);
extern void *func_020b5630(void *);
extern int func_020b4508(void *, int, int);
extern int func_020b45d0(void *, int, int, int, int, int);
extern void *func_020b5618(void *);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern void *func_02062f90(void *, unsigned short *);
extern void *func_02062f4c(void *);
extern int func_020644cc(int);
extern void *func_02077f14(int, int);
extern void *func_02094fbc(void *);
extern char data_021dc7a8[];
extern int data_020e1fbc[];
extern int data_020e1fcc[];
extern void func_0209df64(u8 *);
extern void func_0209dfd8(u8 *, u8 *, int, int, int);
extern void func_0209e474(int *);
extern void func_0209e140(int *, int);
extern int func_0209e3ac(int *, u8 *, int);
extern int func_0209e380(void *, void *);
extern int func_0203fdc4(int);
extern void func_02066694(void *);
extern void *func_02098844(unsigned int, int);
extern int func_02099a28(unsigned int);
extern void *func_02099670(void *);
extern int func_02088b48(void *);
extern int func_02088b30(void *);
extern UnkStruct_020868e8 *func_02099870(void *);
extern int memcmp(void *, void *, int);
extern int func_0209518c(UnkStruct_020868e8 *, UnkStruct_020868e8 *);
extern int func_02088ab8(void *);
extern void func_02088aa0(void *);
extern void func_02066024(void *, Rec *, int, const void *, const void *, UnkStruct_020868e8 *);
extern unsigned short func_02065ed0(void *, u16, int);
extern int func_02097a54(void *);
extern void func_02066688(void *);
extern unsigned char data_020e1f5c[];
extern unsigned char data_020e1f64[];
extern unsigned char data_021dc7bc[];
extern void *func_0209529c(void *obj);
extern int func_02003780(void *ptr);
extern int func_02003750(char *ptr);
extern int func_0209526c(char *ptr);
extern void func_02095238(void *);
extern void func_02003738(void *);

void func_02086874(void *param);

void func_02086d24(UnkStruct_02086d24 *self)
{
    unsigned short tmp;
    int bufA[0x8];
    int bufB[0x10];
    int bufC[0xa];
    int ok;
    int k;

    if (func_020951bc(self) == 0) {
        if (func_02003704(&self->unk_1E) == 0) {
            func_0209f100(data_021dc7a8, 0xf);
            return;
        }
    }
    if (self->unk_47 != 1 && self->unk_47 != 2 && self->unk_47 != 3) {
        return;
    }
    if (func_0209f150(data_021dc7a8, 0xf) == 0) {
        return;
    }

    func_02094fd4(bufA);
    if (func_020951bc(self) != 0) {
        func_02095074(self, bufA);
    } else {
        func_02003618(&self->unk_1E, bufA);
    }

    if ((unsigned char) (self->unk_47 + 0xff) <= 1) {
        func_0203d7b0(0, self->unk_45);
        func_0203d79c(1, self->unk_44);
        func_0203d7c4(4, bufA);
        if (self->unk_40 > 0) {
            func_020b5630(bufB);
            if (self->unk_47 == 1) {
                func_020b4508(bufB, self->unk_40, 1);
            } else {
                func_020b45d0(bufB, self->unk_40 >> 12, 3, 0, 0, 0);
            }
            func_0203d7c4(3, bufB);
            func_020b5618(bufB);
        }
        if (func_0204bcdc(&self->unk_3E) != 0) {
            tmp = 0xfff1;
            if (func_0204bc64(&self->unk_3E) == func_0204bc64(&tmp)) {
                ok = 1;
            } else {
                ok = 0;
            }
        } else {
            if (self->unk_3E == 0xfff1) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok == 0) {
            func_02062f90(bufC, &self->unk_3E);
            func_0203d7c4(2, bufC);
            func_02062f4c(bufC);
        }
    } else {
        func_0203d7c4(0, bufA);
    }

    if ((unsigned char) (self->unk_47 + 0xff) <= 1) {
        k = func_020644cc(3);
    } else {
        k = func_020644cc(2);
    }
    func_02077f14(k, data_020e1fbc[self->unk_47]);
    func_0209f100(data_021dc7a8, 0xf);
    func_02094fbc(bufA);
}

static __inline int P1(UnkStruct_020868e8 *self, Rec *r)
{
    int tt;
    r->unk_04 = 0xfff1;
    tt = func_0204bc64((unsigned short *) (&self->unk_3E));
    if (tt == func_0204bc64((unsigned short *) (&r->unk_04))) {
        return 1;
    }
    return 0;
}

static __inline int P2(UnkStruct_020868e8 *self)
{
    if (self->unk_3E == 0xfff1) {
        return 1;
    }
    return 0;
}

void func_020868e8(UnkStruct_020868e8 *self)
{
    int i;
    int res;
    int z0;
    int z1;
    int t;
    int z4;
    UnkStruct_020868e8 *q;
    int z5;
    Locals L;
    int rc;
    void *obj;
    void *r7;
    int ok;

    if (func_020951bc((void *) self) == 0) {
        if (func_02003704((void *) (&self->unk_1E)) == 0) {
            return;
        }
    }
    if (self->unk_47 != 1 && self->unk_47 != 2 && self->unk_47 != 3) {
        return;
    }
    func_0209df64(&L.r.unk_06);
    if (self->unk_46 == 0) {
        return;
    }
    if (self->unk_45 == 0) {
        return;
    }
    if (self->unk_44 == 0) {
        return;
    }
    func_0209dfd8(L.r.unk_0C, &self->unk_44, 6, 0, 0);
    L.r.unk_14 = 0;
    L.r.unk_18 = 0;
    func_0209e474(&L.r.unk_14);
    if (((u8 *) &L.r)[0x16] < 6) {
        func_0209e140(&L.r.unk_14, 1);
        ((u8 *) &L.r)[0x16] = 6;
        ((u8 *) &L.r)[0x15] = 0;
        ((u8 *) &L.r)[0x14] = 0;
    }
    rc = func_0209e3ac(&L.r.unk_14, L.r.unk_0C, 0x38);
    if ((rc == 1 && func_0209e380(L.r.unk_0C, &L.r.unk_14) >= 0xa) ||
        (rc == -1 && func_0209e380(&L.r.unk_14, L.r.unk_0C) >= 0xa)) {
        func_02086874((void *) self);
        func_0209f100(data_021dc7a8, 0xf);
        return;
    }
    if (self->unk_47 != 3) {
        if (self->unk_46 != L.r.unk_08 || self->unk_45 != L.r.unk_07 || self->unk_44 != L.r.unk_06) {
            goto go;
        }
        return;
    }
    t = func_0203fdc4(0xe);
    func_0209e474(&L.r.unk_14);
    if (t != -1) {
        if (t < 7) {
            return;
        }
        if (t == 7 && ((u8 *) &L.r)[0x16] < 6) {
            return;
        }
    }
    if (rc == 1 && func_0209e380(L.r.unk_0C, &L.r.unk_14) < 1) {
        return;
    }
go:
    if (self->unk_47 == 3 && func_020951bc((void *) self) == 0) {
        func_02086d24((UnkStruct_02086d24 *) self);
        func_02086874((void *) self);
        return;
    }
    func_020b5630(L.bB1);
    func_020b5630(L.bB2);
    func_020b5630(L.bB3);
    func_02066694(L.big);
    func_02094fd4(L.bA);
    i = 0;
    L.r.unk_00 = 0;
    z1 = 0;
    z4 = 0;
    z5 = 0;
    z0 = 0;
    do {
        res = z0;
        obj = func_02098844((unsigned int) data_021dc7bc, i);
        if (obj != 0 && func_02099a28((unsigned int) obj) != 0) {
            r7 = func_02099670(obj);
            if ((u8) (self->unk_47 + 0xff) <= 1) {
                func_0203d7b0(z1, self->unk_45);
                func_0203d79c(1, self->unk_44);
                if (func_0204bcdc((unsigned short *) (&self->unk_3E)) != 0) {
                    ok = P1(self, &L.r);
                } else {
                    ok = P2(self);
                }
                if (ok == 0) {
                    func_02062f90(L.bC, (unsigned short *) (&self->unk_3E));
                    func_0203d7c4(2, L.bC);
                    func_02062f4c(L.bC);
                }
                if (self->unk_40 > 0) {
                    if (self->unk_47 == 1) {
                        func_020b4508(L.bB1, self->unk_40, 1);
                    } else {
                        func_020b45d0(L.bB1, self->unk_40 >> 12, 3, z4, z4, z4);
                    }
                    func_0203d7c4(3, L.bB1);
                }
                if (self->unk_47 == 1) {
                    res = func_02088b48(r7);
                } else {
                    res = func_02088b30(r7);
                }
            } else {
                q = func_02099870(obj);
                if ((self->unk_00 == q->unk_00 && memcmp((u8 *) self + 2, (u8 *) q + 2, 0xc) == 0 &&
                     func_0209518c(self, q) != 0) ||
                    func_02088ab8(r7) != 0) {
                    L.r.unk_00 = (u8) func_020644cc(3);
                    func_02095074((void *) (func_02099870(obj)), L.bA);
                    func_02088aa0(r7);
                    func_0203d7c4(z5, L.bA);
                    res = 1;
                }
            }
            if (res != 0) {
                if ((u8) (self->unk_47 + 0xff) <= 1) {
                    r7 = func_02099870(obj);
                    if (self->unk_00 == ((UnkStruct_020868e8 *) r7)->unk_00 &&
                        memcmp((u8 *) self + 2, (u8 *) r7 + 2, 0xc) == 0 &&
                        func_0209518c(self, (UnkStruct_020868e8 *) r7) != 0) {
                        L.r.unk_00 = (u8) func_020644cc(3);
                    } else {
                        L.r.unk_00 = (u8) (func_020644cc(3) + 3);
                    }
                    func_02095074((void *) (func_02099870(obj)), L.bA);
                    func_0203d7c4(4, L.bA);
                }
                func_02066024(L.big, &L.r, data_020e1fcc[self->unk_47], (const void *) data_020e1f64,
                              (const void *) data_020e1f5c, func_02099870(obj));
                q = func_02099870(obj);
                if ((self->unk_00 == q->unk_00 && memcmp((u8 *) self + 2, (u8 *) q + 2, 0xc) == 0 &&
                     func_0209518c(self, q) != 0) ||
                    self->unk_47 == 3) {
                    L.r.unk_02 = 0x3878;
                    if (self->unk_47 == 2) {
                        L.r.unk_02 = 0x387c;
                    } else if (self->unk_47 == 3) {
                        L.r.unk_02 = 0x3880;
                    }
                    func_02065ed0(L.big, L.r.unk_02, 1);
                }
                func_02097a54(L.big);
            }
        }
        i = i + 1;
    } while (i < 4);
    func_02086d24((UnkStruct_02086d24 *) self);
    func_02086874((void *) self);
    func_02094fbc(L.bA);
    func_02066688(L.big);
    func_020b5618(L.bB3);
    func_020b5618(L.bB2);
    func_020b5618(L.bB1);
}

struct UnkStruct_020868c0 *func_020868c0(struct UnkStruct_020868c0 *obj)
{
    func_0209529c(obj);
    func_02003780(obj->unk_1E);
    func_02003780(obj->unk_2E);
    obj->unk_3E = 0xFFF1;
    return obj;
}

char *func_020868a0(char *ptr)
{
    func_02003750(ptr + 0x2e);
    func_02003750(ptr + 0x1e);
    func_0209526c(ptr);
    return ptr;
}

void func_02086874(void *param)
{
    void *r4 = param;
    func_02095238(r4);
    func_02003738((char *) r4 + 0x1e);
    func_02003738((char *) r4 + 0x2e);
    *(unsigned short *) ((char *) r4 + 0x3e) = 0xfff1;
    *(unsigned int *) ((char *) r4 + 0x40) = 0;
}

void func_0208683c(void *param)
{
    unsigned char a, b, c;
    void *sp;
    void *r4;

    r4 = param;
    func_02086874(param);
    func_0209df64((u8 *) (&sp));
    a = ((unsigned char *) &sp)[2];
    ((unsigned char *) r4)[0x46] = a;
    b = ((unsigned char *) &sp)[1];
    ((unsigned char *) r4)[0x45] = b;
    c = *(unsigned char *) &sp;
    ((unsigned char *) r4)[0x44] = c;
    ((unsigned char *) r4)[0x47] = 0;
}
