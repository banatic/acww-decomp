/* func_020065a0 @ 0x020065a0, 0x450 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_020065a0;
typedef struct {
    int a;
    int b;
} UnkStruct_020065a0_2;

typedef union Pay {
    struct {
        u32 w0;
        u32 w4;
        u32 w8;
    } w;
    u8 b[16];
} Pay;

typedef struct UnkStruct_020065a0_3 {
    char pad_00[0x16c];
    u8 unk_16C;
    char pad_16D[0x2e4 - 0x16d];
    u8 unk_2E4;
    char pad_2E5[0x7d4 - 0x2e5];
    Pay unk_7D4;
    char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
    char pad_7F4[0x800 - 0x7f4];
    int unk_800;
    char pad_804[0x8ec - 0x804];
    u8 unk_8EC;
    char pad_8ED[0x8fc - 0x8ed];
    int unk_8FC;
    int unk_900;
    union {
        struct {
            u8 type : 5;
            u8 sub : 2;
            u8 pending : 1;
        } b;
        u8 raw;
    } unk_904;
} UnkStruct_020065a0_3;

extern int func_02042a5c(u8 *, int);
extern void func_0204f794(UnkStruct_020065a0 *, int, int);
extern int func_0200f290(UnkStruct_020065a0_3 *, int);
extern void func_0200e854(UnkStruct_020065a0_3 *);
extern void func_0204f818(int *, int *, UnkStruct_020065a0 *);
extern int func_ov003_0220fb30(UnkStruct_020065a0_3 *, int, int, int, int, int, int);
extern int func_0200b83c(UnkStruct_020065a0_3 *, UnkStruct_020065a0_2 *, int, int, int, int);
extern int func_0200ad24(UnkStruct_020065a0_3 *, UnkStruct_020065a0_2 *, int, int, int);
extern int func_ov003_02218ca8(UnkStruct_020065a0_3 *, UnkStruct_020065a0_2 *, int, int);
extern int func_ov003_02216410(UnkStruct_020065a0_3 *, int, UnkStruct_020065a0_2 *, int, int);
extern int func_ov003_02216698(UnkStruct_020065a0_3 *, int, int, UnkStruct_020065a0_2 *, int, int);
extern int func_ov003_02211d4c(UnkStruct_020065a0_3 *, int, UnkStruct_020065a0 *, int, int);
extern int func_ov003_02211980(UnkStruct_020065a0_3 *, UnkStruct_020065a0 *, int, int, int);
extern void *func_ov003_022109f8(UnkStruct_020065a0_3 *, int, UnkStruct_020065a0_2 *, int, int, int);
extern int func_ov003_022100c4(UnkStruct_020065a0_3 *, UnkStruct_020065a0_2 *, int, int, int);
extern int func_ov003_022122ac(UnkStruct_020065a0_3 *, int, UnkStruct_020065a0_2 *, int, int);
extern int func_ov003_02216ab8(UnkStruct_020065a0_3 *, int, int, UnkStruct_020065a0_2 *, int, int);
extern int func_0200d4e8(UnkStruct_020065a0_3 *, int, int, int);
extern void func_0200f268(UnkStruct_020065a0_3 *, int);
extern unsigned int *func_0200f27c(UnkStruct_020065a0_3 *, int);

void func_020065a0(UnkStruct_020065a0_3 *self)
{
    int sub;
    Pay *p;
    int flag;
    u8 raw[8];
    int o1;
    int o2;
    int o3;
    int o4;
    int lo;
    int type;
    int hi;
    UnkStruct_020065a0 pos;

    if (func_02042a5c(raw + 2, self->unk_800) == 0 && self->unk_904.b.pending == 0) {
        return;
    }
    o1 = 0;
    o2 = 0;
    if (self->unk_904.b.pending) {
        self->unk_904.raw &= ~0x80;
        hi = self->unk_8FC;
        lo = self->unk_900;
        type = self->unk_904.b.type;
        sub = self->unk_904.b.sub;
    } else {
        *(u16 *) raw = *(u16 *) (raw + 4);
        lo = *(u16 *) raw;
        hi = lo >> 8;
        lo &= 0xff;
        type = raw[2];
        sub = raw[3];
    }
    func_0204f794(&pos, hi, lo);

    switch (type) {
        case 0:
            break;
        case 17:
            if (self->unk_7F0 != 0) {
                break;
            }
            self->unk_8EC = 2;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 14:
        case 19:
        case 20:
        case 21:
        case 22:
            if (func_0200f290(self, 0xa) == 0) {
                self->unk_904.raw |= 0x80;
                self->unk_8FC = hi;
                self->unk_900 = lo;
                type &= 0x1f;
                self->unk_904.raw = (self->unk_904.raw & ~0x1f) | type;
                sub &= 3;
                self->unk_904.raw = (self->unk_904.raw & ~0x60) | (sub << 5);
                return;
            }
            func_0200e854(self);
            break;
        case 12:
        case 13:
        case 15:
        case 16:
        case 18:
        case 23:
        case 24:
        case 25:
        case 26:
            return;
    }

    switch (type) {
        case 1:
        case 2:
            if (self->unk_7F0 == 0x68) {
                UnkStruct_020065a0 v;
                int zz;
                p = &self->unk_7D4;
                zz = p->w.w4;
                v.x = p->w.w0;
                v.y = 0;
                v.z = zz;
                func_0204f818(&o1, &o2, &v);
                if (o1 == hi && o2 == lo) {
                    p->b[0xc] = 1;
                    self->unk_2E4 = 1;
                    return;
                }
            }
            func_ov003_0220fb30(self, pos.x, pos.z, type != 1, 1, 6, -1);
            break;
        case 3:
        case 4:
        case 21:
        case 22:
            if (self->unk_7F0 == 0x18) {
                p = &self->unk_7D4;
                o1 = p->b[5];
                o2 = p->b[5];
                if (o1 == hi && o2 == lo) {
                    p->b[4] = 1;
                    p->b[7] = type;
                    return;
                }
            }
            flag = 1;
            switch (type) {
                case 3:
                    flag = 0;
                case 4: {
                    UnkStruct_020065a0_2 a;
                    a.a = hi;
                    a.b = lo;
                    func_0200b83c(self, &a, -1, flag, 6, -1);
                } break;
                case 0x15:
                    flag = 0;
                case 0x16: {
                    UnkStruct_020065a0_2 b;
                    b.a = hi;
                    b.b = lo;
                    func_0200ad24(self, &b, flag, 6, -1);
                } break;
            }
            break;
        case 5:
            if (self->unk_7F0 == 0x16) {
                p = &self->unk_7D4;
                o1 = p->b[0];
                o2 = p->b[1];
                if (o1 == hi && o2 == lo) {
                    p->b[2] = 1;
                    return;
                }
            }
            {
                UnkStruct_020065a0_2 c;
                c.a = hi;
                c.b = lo;
                func_ov003_02218ca8(self, &c, 6, -1);
            }
            break;
        case 6:
        case 7:
            if (sub == 2) {
                UnkStruct_020065a0_2 d;
                d.a = hi;
                d.b = lo;
                func_ov003_02216410(self, 1, &d, 6, -1);
            } else {
                UnkStruct_020065a0_2 e;
                e.a = hi;
                e.b = lo;
                func_ov003_02216698(self, sub != 0, type != 6, &e, 6, -1);
            }
            break;
        case 8: {
            UnkStruct_020065a0 f;
            f.x = pos.x;
            f.y = pos.y;
            f.z = pos.z;
            func_ov003_02211d4c(self, 0, &f, 6, -1);
        } break;
        case 11: {
            UnkStruct_020065a0 h;
            h.x = pos.x;
            h.y = pos.y;
            h.z = pos.z;
            func_ov003_02211d4c(self, 1, &h, 6, -1);
        } break;
        case 9:
            flag = 0;
        case 10: {
            UnkStruct_020065a0 g;
            g.x = pos.x;
            g.y = pos.y;
            g.z = pos.z;
            func_ov003_02211980(self, &g, flag, 6, -1);
        } break;
        case 19: {
            UnkStruct_020065a0_2 i;
            i.a = hi;
            i.b = lo;
            func_ov003_022109f8(self, 0, &i, 0xfff1, 6, -1);
        } break;
        case 20:
            if (self->unk_7F0 == 0x66) {
                UnkStruct_020065a0 v2;
                Pay *q = &self->unk_7D4;
                o3 = 0;
                o4 = 0;
                v2.x = q->w.w0;
                v2.y = q->w.w4;
                v2.z = q->w.w8;
                func_0204f818(&o3, &o4, &v2);
                if (o3 == hi && o4 == lo) {
                    func_0200f27c(self, 0x1c);
                    q->b[0xf] = 1;
                    return;
                }
            }
            {
                UnkStruct_020065a0_2 j;
                j.a = hi;
                j.b = lo;
                func_ov003_022100c4(self, &j, 1, 6, -1);
            }
            break;
        case 14:
            self->unk_16C = 0;
            if (sub == 2) {
                UnkStruct_020065a0_2 k;
                k.a = hi;
                k.b = lo;
                func_ov003_02216410(self, 1, &k, 6, -1);
            } else if (sub == 3) {
                UnkStruct_020065a0_2 l;
                l.a = hi;
                l.b = lo;
                func_ov003_022122ac(self, 1, &l, 6, -1);
            } else {
                UnkStruct_020065a0_2 m;
                m.a = hi;
                m.b = lo;
                func_ov003_02216ab8(self, sub != 0, 1, &m, 6, -1);
            }
            break;
        case 17:
            if (self->unk_7F0 == 0) {
                func_0200d4e8(self, 3, 1, -1);
                func_0200f268(self, 0x1c);
            }
            break;
        case 0:
        case 12:
        case 13:
        case 15:
        case 16:
        case 18:
        case 23:
        case 24:
        case 25:
        case 26:
            break;
    }
}
