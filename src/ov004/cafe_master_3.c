/* cafe_master_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02224440 @ 0x02224440, 0x104 bytes, Thumb
 * func_ov004_0222439c @ 0x0222439c, 0xa4 bytes, Thumb
 * func_ov004_022242c0 @ 0x022242c0, 0xdc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222439c {
    unsigned char b;
};

typedef struct UnkStruct_022242c0 {
    char unk_00[0x14];
    int unk_14;
} UnkStruct_022242c0;

typedef struct UnkStruct_022242c0_2 {
    char unk_00[0x1e];
    unsigned char unk_1E;
    char unk_1F[0x40 - 0x1f];
    UnkStruct_022242c0 *unk_40;
    char unk_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_022242c0_2;

extern int func_020984e8(void);
extern int func_02099670(int a);
extern int func_020a12e8(void);
extern int func_0200338c(int a, int b);
extern int func_02073d90(void *p);
extern short *func_0209d358(int a, int b);
extern int func_020644cc(int n);
extern int func_0202ea80(int a, int b);
extern int func_ov068_02273974(int a);
extern int func_02088bd4(int a);
extern int func_020960f8(int a, int b);
extern void func_0208b520(void);
extern int data_ov004_02254594[2];
extern u8 data_ov004_02254508[];
extern void *data_020ccf94;
extern void func_ov004_0222421c(void *self, int a);
extern void func_0206844c(void *ctx, struct UnkStruct_0222439c *t, int a);
extern int func_020160b4(UnkStruct_022242c0_2 *self);
extern int func_020ab504(void *);
extern int func_0201b43c(int a, int b);
extern void func_0201b420(int a, int b);

void func_ov004_02224440(int arg, char *out)
{
    // DECLS
    int a;
    int b;
    int c;
    // ENDDECLS

    a = func_02099670(func_020984e8());
    if (func_020a12e8() != 0) {
        *(int *) out = data_ov004_02254594[1];
        out[4] = 0x1f;
        return;
    }
    *(int *) out = data_ov004_02254594[0];
    b = func_0200338c(0x66, 0);
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        out[4] = (char) (func_020644cc(3) + 0x55);
        return;
    }
    if (func_0202ea80(0x17, 0) != 0) {
        if (b != 0 && func_ov068_02273974(b) == 7) {
            out[4] = 0x58;
            return;
        }
        c = func_02088bd4(a) >> 2;
        out[4] = (char) (data_ov004_02254508[c] + func_020644cc(3));
        return;
    }
    if (func_020960f8(0x28, 4) == 0) {
        if (func_0202ea80(0x16, 1) == 0) {
            out[4] = (char) (func_02088bd4(a) >> 1);
            return;
        }
        if (b != 0 && func_ov068_02273974(b) == 7) {
            out[4] = 0x58;
            return;
        }
        out[4] = (char) ((func_02088bd4(a) >> 2) + 0x49);
        return;
    }
    if (func_0202ea80(0x17, 0) == 0) {
        func_0208b520();
    }
    out[4] = (char) ((func_02088bd4(a) >> 2) + 0x14);
}

void func_ov004_0222439c(char *self)
{
    struct UnkStruct_0222439c t;
    int s;
    char *ctx;
    int u;
    unsigned char code;
    int c;

    s = func_02099670(func_020984e8());
    ctx = *(char **) (self + 0x40);
    u = (*(int *) data_ov004_02254594);
    code = 0xff;
    if (func_020a12e8() != 0) {
        return;
    }
    c = *(unsigned char *) (self + 0x1e);
    if (c >= 0x1c && c <= 0x23) {
        if ((unsigned int) func_02088bd4(s) >= 5 && func_020644cc(3) == 0) {
            code = 0x2c;
        } else {
            *(int *) (ctx + 0x14) = 0;
            func_ov004_0222421c(self, 1);
        }
    }
    c = *(unsigned char *) (self + 0x1e);
    switch (c) {
        case 0x2d:
        case 0x2e:
            if (c == 0x2d) {
                *(char *) (self + 0xb9) = 1;
            }
            *(int *) (ctx + 0x14) = 0;
            func_ov004_0222421c(self, 1);
            break;
    }
    c = *(unsigned char *) (self + 0x1e);
    if (c >= 0x30 && c <= 0x3b) {
        *(int *) (ctx + 0x14) = 0;
        func_ov004_0222421c(self, 3);
    }
    if (code != 0xff) {
        t.b = code;
        func_0206844c(*(char **) (self + 0x40), &t, u);
    }
}

void func_ov004_022242c0(UnkStruct_022242c0_2 *self)
{
    int h;
    int fl;
    int v;
    unsigned char k;
    unsigned char b;

    h = func_02099670(func_020984e8());
    fl = func_020ab504((void *) func_020160b4(self));
    v = (*(int *) data_ov004_02254594);
    k = 0xff;
    if ((int) self->unk_1E >= 0x24 && (int) self->unk_1E <= 0x2b) {
        if (fl != 0) {
            k = (unsigned char) ((func_02088bd4(h) >> 2) + 0x28);
        } else {
            self->unk_40->unk_14 = 0;
            func_ov004_0222421c((void *) self, 2);
        }
    }
    switch (self->unk_1E) {
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            if (fl == 0) {
                if (func_0201b43c(self->unk_B4, 0xc8) == 0) {
                    k = 0x2f;
                } else {
                    func_0201b420(self->unk_B4, 0xc8);
                    k = (unsigned char) (func_020644cc(2) + ((func_02088bd4(h) >> 2) * 2 + 0x1c));
                }
            } else {
                k = (unsigned char) ((func_02088bd4(h) >> 2) + 0x18);
            }
            break;
    }
    if (k != 0xff) {
        b = k;
        func_0206844c((void *) self->unk_40, (struct UnkStruct_0222439c *) (&b), v);
    }
}
