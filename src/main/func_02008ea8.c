/* func_02008ea8 @ 0x02008ea8, 0x468 bytes, Thumb, module main
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
typedef struct UnkStruct_02008ea8 {
    u8 pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02008ea8;

typedef struct UnkStruct_02008ea8_2 {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2d8 - 0x2d0];
    unsigned int unk_2D8;
    u8 pad_2DC[0x5c8 - 0x2dc];
    u8 sub_5c8[0x698 - 0x5c8];
    UnkStruct_02008ea8 unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[0x10];
    u8 pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02008ea8_2;

extern void *data_020ccf94;
extern int data_020d83b4;
extern int data_020d83c4;
extern int data_020d83d8;
extern volatile unsigned char data_020e54a8;

extern void func_0200faf0(UnkStruct_02008ea8_2 *self, int a);
extern void func_ov003_0222e5fc(int a);
extern void func_ov003_0222e898(int a, int b);
extern void func_ov003_02219668(UnkStruct_02008ea8 *o, const Vec3 *v);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern void func_ov003_0222d83c(int a, u16 *v, UnkStruct_02008ea8 *o, int d);
extern void *func_020604f8(void *p);
extern void func_ov003_0222aaa0(Vec3 *out, int a);
extern void func_ov003_0222aa50(void *p, Vec3 *a, Vec3 *b);
extern int func_02056f94(void *p);
extern int func_02056f28(void *p, int a);
extern void func_020109a0(UnkStruct_02008ea8_2 *self, int a, int b, int c);
extern void func_0205eae0(void *p, int a, int b, int c);
extern int func_02073908(void *g, int a);
extern void func_0203ae98(void);
extern int func_02008258(UnkStruct_02008ea8_2 *self, int a);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_02008ea8_2 *self, void *b);
extern void func_0203ee08(UnkStruct_02008ea8_2 *self, void *b);
extern void func_0200f27c(UnkStruct_02008ea8_2 *self, int a);
extern void func_0200f268(UnkStruct_02008ea8_2 *self, int a);
extern void func_020a8164(void *p, void *g);
extern void func_ov003_02215240(UnkStruct_02008ea8_2 *self, int a, int b, int c);
extern void func_ov003_02213ae4(UnkStruct_02008ea8_2 *self, int a, int b, int c, int d, int e);
extern void func_0203e19c(void);
extern void func_0203b144(void);
extern void func_020110c4(u16 *out, UnkStruct_02008ea8_2 *self);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0200fc90(UnkStruct_02008ea8_2 *self);
extern void func_ov003_02217c5c(UnkStruct_02008ea8_2 *self, int a, int b, int c, int d, int e, int f, int g);
extern void func_0203e110(void);
extern void func_0200d4e8(UnkStruct_02008ea8_2 *self, int a, int b, int c);

void func_02008ea8(UnkStruct_02008ea8_2 *self)
{
    u16 w[8];
    UnkStruct_02008ea8 blk;
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec3 v4;
    Vec3 v5;
    u8 *p;
    int kind;
    u8 *statep;
    u8 s2;
    void *g;
    void *b;
    void *o;
    int n;
    int c;
    unsigned int ok;

    func_0200faf0(self, 0x400);
    p = self->unk_7D4;
    s2 = p[2];
    kind = p[5];
    statep = p + 3;
    blk = self->unk_698;

    switch (s2) {
        case 0:
            if (*statep == 3) {
                *statep = 0;
                func_ov003_0222e5fc(p[6]);
                func_ov003_0222e898(kind, (u8) self->unk_800);
            }
            if (kind == 9) {
                v1.x = 0x119a;
                v1.y = 0x4cd;
                v1.z = -0x4cd;
            } else {
                v1.x = 0xb33;
                v1.y = 0x19a;
                v1.z = -0x19a;
            }
            func_ov003_02219668(&blk, &v1);
            w[5] = 0x64;
            w[6] = 0x64;
            w[7] = 0x64;
            v1.x = blk.unk_24;
            v1.y = blk.unk_28;
            v1.z = blk.unk_2C;
            func_0203f7d0(&v1, &v1);
            func_ov003_0222d83c((u8) self->unk_800, &w[5], &blk, 0);
            break;
        case 1:
            o = func_020604f8((char *) self + 0x5c8);
            if (o != 0) {
                v1.x = 0xb33;
                v1.y = 0x19a;
                v1.z = -0x19a;
                func_ov003_02219668(&blk, &v1);
                v2.x = blk.unk_24;
                v2.y = blk.unk_28;
                v2.z = blk.unk_2C;
                func_0203f7d0(&v2, &v2);
                func_ov003_0222aaa0(&v3, *(signed char *) ((char *) o + 0x7e));
                v4.x = v2.x;
                v4.y = v2.y;
                v4.z = v2.z;
                v5.x = v3.x;
                v5.y = v3.y;
                v5.z = v3.z;
                func_ov003_0222aa50(o, &v4, &v5);
            }
            break;
    }

    switch (self->unk_704) {
        case 0x87:
            if (func_02056f94(self->sub_2d0) == 0) {
                return;
            }
            func_020109a0(self, 0x88, 0, 0);
            func_0205eae0((char *) self + 0x5a0, 0xa, 0, 1);
            return;
        case 0x89:
            if (func_02056f94(self->sub_2d0) == 0) {
                return;
            }
            func_020109a0(self, 0x8a, 0, 0);
            func_0205eae0((char *) self + 0x5a0, 0x20, 0, 1);
            return;
        case 0x86:
            n = 0x19;
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                if (func_02056f28(self->sub_2d0, 0xc) != 0) {
                    func_0203ae98();
                }
            }
            break;
        default:
            n = 5;
            break;
    }

    if ((int) ((self->unk_2D8 << 4) >> 16) < n) {
        return;
    }

    g = data_020ccf94;
    if (func_02073908(g, self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        return;
    }

    switch (*statep) {
        case 0:
            if (func_0203e1c4() != 0) {
                *statep = 1;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c(self, 0x11);
                switch (s2) {
                    case 0:
                        func_020a8164((char *) self + 0xec, &data_020d83c4);
                        self->unk_10A = 0x40;
                        break;
                    case 1:
                        func_020a8164((char *) self + 0xec, &data_020d83d8);
                        self->unk_10A = 0x40;
                        break;
                    case 2:
                        func_020a8164((char *) self + 0xec, &data_020d83b4);
                        self->unk_10A = 0x28;
                        break;
                    case 3:
                        func_020a8164((char *) self + 0xec, &data_020d83b4);
                        self->unk_10A = 0x29;
                        break;
                    case 7:
                        func_020a8164((char *) self + 0xec, &data_020d83b4);
                        self->unk_10A = 0x22;
                        break;
                    default:
                        func_020a8164((char *) self + 0xec, &data_020d83b4);
                        self->unk_10A = s2 + 0x1a;
                        break;
                }
                self->unk_12C->unk_08 = 1;
            }
            // fall through
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *statep = 2;
            break;
        case 2:
            if (s2 < 2) {
                if (self->unk_12C == 0) {
                    break;
                }
                if (((u8 *) self->unk_12C)[0x1e77] != 0xfe) {
                    break;
                }
                if (s2 == 1) {
                    func_ov003_02215240(self, 1, 6, -1);
                    break;
                }
                func_ov003_02213ae4(self, 3, kind, kind, 6, -1);
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268(self, 0x11);
            func_0203e19c();
            if (func_02073908(g, self->unk_800) != 0) {
                func_0203b144();
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_020110c4(&w[3], self);
            if (func_0204bcdc(&w[3]) != 0) {
                w[4] = 0xfff1;
                if (func_0204bc64(&w[3]) == func_0204bc64(&w[4])) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (w[3] == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c == 0 && func_0200fc90(self) == 0) {
                ok = (data_020e54a8 == 0) ? 1 : 0;
                if (ok != 0) {
                    func_ov003_02217c5c(self, 2, 2, 0, 0, 0, 6, -1);
                    break;
                }
            }
            ok = (data_020e54a8 == 0) ? 1 : 0;
            if (ok != 0) {
                func_0203e110();
                func_0200f27c(self, 0);
            }
            func_0200d4e8(self, 3, 1, -1);
            break;
    }
}
