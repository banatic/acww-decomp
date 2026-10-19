/* func_020c1b9c @ 0x020c1b9c, 0x41c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    int c;
} Tri;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad_60[0x3b0 - 0x60];
    int unk_3B0;
    u8 pad_3B4[0x564 - 0x3b4];
    int unk_564;
    u8 pad_568[0x618 - 0x568];
    int unk_618;
    u8 pad_61C[0x658 - 0x61c];
    int unk_658;
    u8 pad_65C[0x698 - 0x65c];
    int *unk_698;
    u8 pad_69C[0x728 - 0x69c];
    u8 unk_728;
} UnkStruct_020c1b9c;

extern void *data_020ccf94;
extern u8 data_021c75b8;
extern Tri data_020d3150;
extern u16 data_020c80f8;
extern int data_020c814c;
extern void *data_020e7ad8;

extern void *func_020a13d0(void);
extern void *func_020984fc(void *);
extern int func_02095ed0(int, void *);
extern int func_02095ab0(Tri *, int, void *);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_0209615c(void *);
extern int func_02019de8(void *);
extern void func_020c1b28(void *, int);
extern void func_0201ad18(void *, int, int, int, const void *, int, int, int);
extern int func_020147e0(void *, int, int);
extern void func_02068440(int *);
extern void func_020c37f8(void);
extern void func_0203aed8(void);
extern int func_02082644(int);
extern void func_020160d8(void *, int);
extern void func_0206844c(int *, u8 *, void *);
extern void func_02068434(int *);
extern int func_02014868(void *);
extern int func_0200322c(void *, Tri *);
extern int func_02095a8c(int, void *);
extern void func_020c37dc(void);
extern int func_020a1380(void);
extern void func_020b8dc0(void);
extern int func_02073918(void *, int);
extern void *func_02099688(void *);
extern int func_020882c4(unsigned char *);
extern void func_020882f0(void *);
extern void func_02098ff8(void *, int);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern void func_02088198(void *);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void *func_020984e8(void);

extern unsigned char data_021fbee8[];

int func_020c1b9c(UnkStruct_020c1b9c *self)
{
    void *local1c;
    u8 b20;
    Tri v;
    Tri tmp;
    void *a;
    void *g;
    void *b;
    void *x;
    unsigned int ok;
    int t;

    a = func_020a13d0();
    g = data_020ccf94;
    b = *(void **) ((char *) g + 0x68);
    local1c = func_020984fc(a);
    switch (self->unk_728) {
        case 0:
            if (data_021c75b8 == 2) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok == 0) {
                break;
            }
            if (func_02095ed0(1, a) == 0) {
                break;
            }
            self->unk_728 = 1;
            break;
        case 1:
            tmp.a = data_020d3150.a;
            tmp.b = data_020d3150.b;
            tmp.c = data_020d3150.c;
            func_02095ab0(&tmp, 0x35c, a);
            func_02019d0c(&self->unk_564, 1, 1, 0xe000, 0x10800, 0, 0, 0, 0, data_020c80f8, 0);
            self->unk_728 = 2;
            break;
        case 2:
            if (func_0209615c(a) != 0) {
                break;
            }
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            self->unk_728 = 3;
            func_020c1b28(&self->unk_658, 6);
            func_0201ad18(&self->unk_3B0, 0, 0, 0, (const void *) data_021fbee8, 4, data_020c814c, 1);
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            func_020147e0(&self->unk_618, 0, 1);
            break;
        case 3:
            if (self->unk_698[1] != 5) {
                break;
            }
            func_02068440(self->unk_698);
            func_02019d0c(&self->unk_564, 2, 2, 0xea00, 0x12e00, 0, 0, 0, 0, data_020c80f8, 0);
            func_020c37f8();
            func_0203aed8();
            self->unk_728 = 4;
            break;
        case 4:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            func_0201ad18(&self->unk_3B0, 1, 0, 0, (const void *) data_021fbee8, 4, data_020c814c, 1);
            t = func_02082644(0x23);
            if (t != 0) {
                func_020160d8(&self->unk_658, t);
            }
            b20 = 0xa;
            func_0206844c(self->unk_698, &b20, data_020e7ad8);
            self->unk_698[2] = 1;
            func_02068434(self->unk_698);
            self->unk_728 = 5;
            break;
        case 5:
            if (func_02014868(&self->unk_618) != 0) {
                break;
            }
            v.a = 0xde00;
            v.b = 0;
            v.c = 0x13a00;
            func_02019d0c(&self->unk_564, 3, 1, 0, 0, 0, func_0200322c(&self->unk_5C, &v), 0, 0, data_020c80f8, 0);
            self->unk_728 = 6;
            break;
        case 6:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 1, 1, 0xde00, 0x13a00, 0, 0, 0, 0, data_020c80f8, 0);
            func_02095a8c(0, a);
            func_020c37dc();
            self->unk_728 = 7;
            break;
        case 7:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            self->unk_728 = 8;
            break;
        case 8:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 1, 1, 0xf000, 0x1d000, 0, 0, 0, 0, data_020c80f8, 0);
            self->unk_728 = 9;
            break;
        case 9:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            if (a != b && func_020a1380() == 0) {
                func_020b8dc0();
            } else {
                self->unk_728 = 0xa;
            }
            break;
        case 10:
            if (func_02073918(g, 0) != 0) {
                x = func_02099688(func_020984e8());
                if (func_020882c4(x) == 1) {
                    func_020882f0(x);
                }
                func_02098ff8(func_020984e8(), 0x39);
                func_020882f0(func_02099688(local1c));
                func_02088198((void *) func_020860c4((int) func_0208602c()));
                func_020b6098(func_020b5e10(), 1);
            }
            if (a == b) {
                func_020882f0(func_02099688(func_020984e8()));
                func_02088198((void *) func_020860c4((int) func_0208602c()));
                func_02098ff8(func_020984e8(), 0x31);
                func_020b6098(func_020b5e10(), 0);
            } else {
                func_020b6098(func_020b5e10(), 1);
            }
            self->unk_728 = 0xb;
            break;
    }
    return 1;
}
