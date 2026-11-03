/* barber_talk: 8 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_02260bb0 @ 0x02260bb0, 0x6 bytes, Thumb
 * func_ov053_02260ba8 @ 0x02260ba8, 0x6 bytes, Thumb
 * func_ov053_02260a68 @ 0x02260a68, 0x140 bytes, Thumb
 * func_ov053_02260a18 @ 0x02260a18, 0x4e bytes, Thumb
 * func_ov053_022609fc @ 0x022609fc, 0x1a bytes, Thumb
 * func_ov053_02260894 @ 0x02260894, 0x168 bytes, Thumb
 * func_ov053_02260790 @ 0x02260790, 0x104 bytes, Thumb
 * func_ov053_0226075c @ 0x0226075c, 0x32 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02260bb0;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_02260ba8;

typedef struct Entry {
    void *ptr;
    unsigned char flag;
} Entry;

typedef struct UnkStruct_02260a68 {
    unsigned char pad_00[0xb0];
    int idx;
    int kind;
} UnkStruct_02260a68;

typedef struct UnkStruct_02260a68_2 {
    void *ptr;
    unsigned char flag;
} UnkStruct_02260a68_2;

typedef struct UnkStruct_02260894 {
    u8 pad_00[0x1e];
    u8 state;
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40;
    u8 pad_44[0xb4 - 0x44];
    void *unk_B4;
    u8 unk_B8;
    u8 unk_B9;
    u8 unk_BA;
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
} UnkStruct_02260894;

typedef struct UnkStruct_02260790 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xba - 0xb8];
    u8 unk_BA;
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
} UnkStruct_02260790;

extern int func_020984e8(void);
extern int func_ov053_02260474(int);
extern int func_0202ea80(int, int);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_020644cc(int);
extern unsigned int data_ov053_02261c60;
extern void *data_ov053_02261980;
extern Entry data_ov053_02261a90[14];
extern int func_ov004_0222beb4(void);
extern int func_02099670(int argument0);
extern void func_02088bac(int, int);
extern void func_02035684(int, int, int);
extern void *func_02099870(void *);
extern int func_020950c0(void *);
extern int func_ov004_0222c1b0(int);
extern void func_0200467c(int);
extern void func_ov053_02261524(void *, int);
extern void *func_0208602c(void);
extern void func_020860d4(void *, int);
extern void func_0206844c(void *, u8 *, const void *);
extern u8 data_ov053_022617ec[][2];
extern u8 data_021f43e8[];
extern int func_020160b4(UnkStruct_02260790 *self);
extern int func_020ab504(int a);
extern void func_0208b520(void);
extern int func_0201b43c(int a, int b);
extern void func_0201b420(int a, int b);
extern void func_020860f0(int a, int b);
extern int func_02099824(int t);
extern int func_020997f8(int t);
extern u8 data_ov053_022617c4[];
extern u8 data_ov053_022617c0[];
extern unsigned int func_02088bc0(int);

int func_ov053_0226075c(void *receiver);

void func_ov053_02260bb0(UnkStruct_02260bb0 *p, unsigned long v)
{
    p->unk_B0 = v;
}

unsigned long func_ov053_02260ba8(UnkStruct_02260ba8 *p)
{
    return p->unk_B0;
}

void func_ov053_02260a68(UnkStruct_02260a68 *self, UnkStruct_02260a68_2 *out)
{
    int v;
    unsigned int guard;
    void *p;

    v = func_020984e8();

    guard = data_ov053_02261c60;
    if ((guard & 1) == 0) {
        p = data_ov053_02261980;
        data_ov053_02261a90[0].ptr = p;
        data_ov053_02261a90[1].ptr = p;
        data_ov053_02261a90[2].ptr = p;
        data_ov053_02261a90[3].ptr = p;
        data_ov053_02261a90[4].ptr = p;
        data_ov053_02261a90[5].ptr = p;
        data_ov053_02261a90[6].ptr = p;
        data_ov053_02261a90[7].ptr = p;
        data_ov053_02261a90[8].ptr = p;
        data_ov053_02261a90[9].ptr = p;
        data_ov053_02261a90[10].ptr = p;
        data_ov053_02261a90[11].ptr = p;
        data_ov053_02261a90[12].ptr = p;
        data_ov053_02261a90[13].ptr = p;
        data_ov053_02261c60 = guard | 1;
    }

    if ((int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) == 4) {
        out->ptr = data_ov053_02261a90[self->idx].ptr;
        out->flag = (unsigned char) func_ov053_0226075c(self);
    } else {
        if ((int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 0 && (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 3 && (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 5 &&
            (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 7 && (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 8 && (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 9 &&
            (int) func_ov053_02260ba8((UnkStruct_02260ba8 *) self) != 0xa) {
            if (func_ov053_02260474(self->kind) == 0) {
                if (func_0202ea80(0x13, 0) == 0) {
                    if (func_02099020(v, 0xb) == 0) {
                        func_ov053_02260bb0((UnkStruct_02260bb0 *) self, 1);
                        func_02098ff8(v, 0xb);
                    } else {
                        func_ov053_02260bb0((UnkStruct_02260bb0 *) self, 2);
                    }
                } else {
                    func_ov053_02260bb0((UnkStruct_02260bb0 *) self, func_020644cc(3) + 0xb);
                }
            } else {
                func_ov053_02260bb0((UnkStruct_02260bb0 *) self, 6);
            }
        }
        if (self->idx >= 0 && self->idx < 0xe) {
            out->flag = data_ov053_02261a90[self->idx].flag;
            out->ptr = data_ov053_02261a90[self->idx].ptr;
        }
    }
}

void func_ov053_02260a18(unsigned char *p)
{
    unsigned char b = p[0x1e];
    if (b == 0xe || b == 0x37) {
        if ((b == 0xe && p[0xb9] == 1) || (b == 0x37 && p[0xb9] == 2)) {
            func_ov004_0222beb4();

            func_02088bac(func_02099670((int) func_020984e8()), 1);
        }
        p[0xb9]++;
    }
}

void func_ov053_022609fc(void *p)
{
    if (*(unsigned char *) ((char *) p + 0x1e) == 0xc) {
        func_02035684(0xe, 0x46, 0);
    }
}

void func_ov053_02260894(UnkStruct_02260894 *obj)
{
    u8 m;
    void *h;
    const void *tag;
    int code;
    int v;

    h = (void *) func_020984e8();
    tag = data_ov053_02261980;
    code = 0xff;

    switch (obj->state) {
        case 0xd:
            if (obj->unk_BA == obj->unk_BC && obj->unk_BB == obj->unk_BD) {
                code = 0x37;
            } else {
                code = 0xe;
            }
            obj->unk_B9 = 0;
            break;
        case 0x17:
            obj->unk_B8 = 1;
            break;
        case 0x18:
            obj->unk_B8 = 0;
            break;
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
            v = func_020950c0(func_02099870(h));
            if (obj->unk_B8 != 0) {
                v = (v == 0) ? 1 : 0;
            }
            obj->unk_BA = data_ov053_022617ec[obj->state - 0x2f][v];
            break;
        case 0x40:
            func_ov004_0222c1b0(0);
            func_0200467c(0x43);
            code = func_ov053_0226075c((void *) obj);
            break;
        case 0x42:
            func_ov053_02261524(obj->unk_B4, 9);
            break;
        case 0xe:
        case 0x37:
            func_0202ea80(0x13, 1);
            func_020860d4(func_0208602c(), 7);
            func_0206844c(obj->unk_40, data_021f43e8, 0);
            break;
        case 0x41:
            func_ov004_0222c1b0(1);
            func_0200467c(0x44);
            break;
        case 0x45:
            break;
    }

    if (code != 0xff) {
        m = (u8) code;
        func_0206844c(obj->unk_40, &m, tag);
    }
}

void func_ov053_02260790(UnkStruct_02260790 *self)
{
    u8 arg;
    int t;
    int a;
    int k;
    int code;

    t = func_020984e8();
    a = func_020ab504(func_020160b4(self));
    k = (*(int *) &data_ov053_02261980);
    code = 0xff;
    switch (self->unk_1E) {
        case 1:
        case 2:
        case 4:
            if (a == 0) {
                func_0208b520();
                code = 8;
            }
            break;
        case 8:
            if (a == 0) {
                if (func_0201b43c(self->unk_B4, 0xbb8) != 0) {
                    func_0201b420(self->unk_B4, 0xbb8);
                    code = 0x3c;
                    func_020860f0((int) func_0208602c(), 7);
                    self->unk_BA = 0;
                    self->unk_BB = 0;
                    self->unk_BC = (u8) func_02099824(t);
                    self->unk_BD = (u8) func_020997f8(t);
                } else {
                    code = 0x3f;
                }
            }
            break;
        case 9:
        case 10:
            if (a != 4) {
                self->unk_BB = data_ov053_022617c4[a];
                code = 0xc;
            }
            break;
        case 11:
        case 0x38:
            if (a != 4) {
                self->unk_BB = data_ov053_022617c0[a];
                code = 0xc;
            }
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c((void *) self->unk_40, &arg, (const void *) k);
    }
}

int func_ov053_0226075c(void *receiver)
{
    int first = func_020984e8();

    if (func_02088bc0(func_02099670(first)) >= 0x10) {
        if (func_020950c0((void *) ((int) func_02099870((void *) first))) == 0) {
            return 0x15;
        } else {
            return 0x16;
        }
    }
    return 0x3e;
}
