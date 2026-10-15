/* func_ov003_02214d2c @ 0x02214d2c, 0x438 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct T12c {
    u8 pad_00[4];
    int unk_04;
    int unk_08;
} T12c;
typedef struct Vec3 {
    int x, y, z;
} Vec3;
typedef struct UnkStruct_02214d2c {
    u8 pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02214d2c;
typedef struct Pair {
    int x;
    int y;
} Pair;

typedef struct UnkStruct_02214d2c_2 {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2d4 - 0x2d0];
    unsigned int unk_2D4;
    unsigned int unk_2D8;
    u8 pad_2DC[0x5c8 - 0x2dc];
    u8 sub_5c8[0x698 - 0x5c8];
    UnkStruct_02214d2c unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[0x1c];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x810 - 0x804];
    int unk_810;
    u8 pad_814[0x81c - 0x814];
    int unk_81C;
    u16 unk_820;
    u16 unk_822;
} UnkStruct_02214d2c_2;

extern int data_ov003_02238100;
extern int data_ov003_02238158;

extern int func_0200faf0(UnkStruct_02214d2c_2 *self, int a);
extern void *func_020604f8(void *p);
extern void func_ov003_0222aaa0(Vec3 *out, int a);
extern void func_ov003_02219668(UnkStruct_02214d2c *o, const Vec3 *v);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern int func_ov003_0222aa50(void *p, Vec3 *a, Vec3 *b);
extern int func_02056f28(void *p, int a);
extern void func_0203ae98(void);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_02214d2c_2 *self, void *b);
extern void func_0203ee08(UnkStruct_02214d2c_2 *self, void *b);
extern unsigned int *func_0200f27c(UnkStruct_02214d2c_2 *self, int a);
extern void func_0200f268(UnkStruct_02214d2c_2 *self, int a);
extern void func_020a8164(void *p, void *g);
extern int func_0203cbd0(u16 *p);
extern void func_02035624(int a);
extern void func_02035684(int a, int b, int c);
extern void func_020356c4(int a, int b, int c, int d);
extern int func_0203cc38(void);
extern int func_02099fe8(void);
extern int func_02043368(int a, Pair *p, unsigned char *result);
extern int func_0203e19c(void);
extern int func_ov003_02214c04(UnkStruct_02214d2c_2 *self, int a, int b, int c);
extern int func_0203b144(void);
extern int func_02043554(int a, int b);
extern void func_02060448(void *p);
extern int func_02008258(UnkStruct_02214d2c_2 *self, int a);
extern int func_ov003_0220d498(UnkStruct_02214d2c_2 *self, void *d, int a, int b, int c);
extern void *func_020094a0(UnkStruct_02214d2c_2 *self, int a, int b, int c, int d, int e);

void func_ov003_02214d2c(UnkStruct_02214d2c_2 *self)
{
    u16 m[4];
    Pair pr;
    UnkStruct_02214d2c blk;
    Vec3 v;
    Vec3 c;
    Vec3 w;
    Vec3 a;
    Vec3 b2;
    u8 *pay;
    u8 *statep;
    void *o;
    void *bp;
    int n;
    int q;
    int ok;
    u8 t;

    func_0200faf0(self, 0x400);
    pay = self->unk_7D4;
    o = func_020604f8((char *) self + 0x5c8);
    if (o != 0) {
        blk = self->unk_698;
        func_ov003_0222aaa0(&c, *(signed char *) ((char *) o + 0x7e));
        v.x = 0x4cd;
        v.y = 0;
        v.z = 0;
        n = (int) (((unsigned int) self->unk_2D8 << 4) >> 16);
        if (pay[4] != 0) {
            v.x = 0x800;
            v.y = 0x19a;
            v.z = -0x19a;
        } else if (n >= 0x10) {
            q = (n - 0xf) * 0x19a / ((int) (((unsigned int) self->unk_2D4 << 4) >> 16) - 0x10);
            v.x = v.x + q * 2;
            v.y = v.y + q;
            v.z = v.z - q;
        }
        func_ov003_02219668(&blk, &v);
        w.x = blk.unk_24;
        w.y = blk.unk_28;
        w.z = blk.unk_2C;
        func_0203f7d0(&w, &w);
        a.x = w.x;
        a.y = w.y;
        a.z = w.z;
        b2.x = c.x;
        b2.y = c.y;
        b2.z = c.z;
        func_ov003_0222aa50(o, &a, &b2);
    }

    statep = pay + 2;
    if (self->unk_704 == 0x59) {
        if (func_02056f28(self->sub_2d0, 3) != 0) {
            func_0203ae98();
        }
    }
    if (((unsigned int) self->unk_2D8 << 4) >> 16 < 0x11 && *statep < 5 && pay[4] == 0) {
        return;
    }

    switch (*statep) {
        case 0:
            if (func_0203e1c4() != 0) {
                *statep = 1;
                bp = self;
                if (self != 0) {
                    bp = (char *) self + 0xec;
                }
                func_0203ee14(self, bp);
                func_0200f27c(self, 0x11);
                func_020a8164((char *) self + 0xec, &data_ov003_02238158);
                t = pay[3];
                self->unk_10A = t;
                m[1] = (u16) (t + 0x12e8);
                func_0203cbd0(&m[1]);
                self->unk_822 = m[1];
                self->unk_820 = self->unk_822;
                self->unk_12C->unk_08 = 1;
                func_02035624(0x12);
                func_02035684(0xc, 0, 4);
                func_020356c4(0xd, 0x39, 0x7f, 1);
            }
            // fall through
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            if (func_0203cc38() != 0 && pay[5] == 0) {
                *statep = 5;
                self->unk_81C = 0xe;
                break;
            }
            *statep = 2;
            self->unk_81C = 8;
            break;
        case 2:
            if (func_02099fe8() == -1) {
                pr.x = 0;
                pr.y = 0;
                if (func_02043368(0x10, &pr, 0) != 0) {
                    *statep = 3;
                    ok = 0;
                    if (self->unk_820 >= 0x1320 && self->unk_820 <= 0x1322) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        self->unk_81C = 4;
                        break;
                    }
                    self->unk_81C = 0;
                    break;
                }
                *statep = 4;
                self->unk_81C = 1;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = self;
            if (self != 0) {
                bp = (char *) self + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            func_ov003_02214c04(self, 0, 6, -1);
            func_0203b144();
            break;
        case 3:
            if (self->unk_81C >= 0xf) {
                ok = 0;
                if (self->unk_820 >= 0x1320 && self->unk_820 <= 0x1322) {
                    ok = 1;
                }
                if (ok != 0) {
                    *statep = 6;
                    if (self->unk_810 != -1) {
                        break;
                    }
                    self->unk_810 = func_02043554(self->unk_800, self->unk_820);
                    if (self->unk_810 == -1) {
                        break;
                    }
                    *statep = 4;
                    break;
                }
                *statep = 4;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = self;
            if (self != 0) {
                bp = (char *) self + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_ov003_02214c04(self, 1, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            func_02060448((char *) self + 0x5c8);
            bp = self;
            if (self != 0) {
                bp = (char *) self + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_ov003_0220d498(self, &data_ov003_02238100, 0, 6, -1);
            func_0203b144();
            break;
        case 5:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = self;
            if (self != 0) {
                bp = (char *) self + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            func_020094a0(self, 1, pay[3], 0, 6, -1);
            break;
        case 6:
            if (self->unk_810 != -1) {
                break;
            }
            self->unk_810 = func_02043554(self->unk_800, self->unk_820);
            if (self->unk_810 == -1) {
                break;
            }
            *statep = 4;
            break;
    }
}
