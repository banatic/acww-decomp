/* outdoor_villager_moves_8: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022693f0 @ 0x022693f0, 0x60 bytes, Thumb
 * func_ov068_02269314 @ 0x02269314, 0xdc bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    int unk_20;
} UnkStruct_022693f0;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02269314;

extern unsigned short data_020c80f8;
extern int func_02019e00(char *addr);
extern int func_02019de8(char *addr);
extern int func_02019c6c(char *addr, int val, unsigned short data);
extern int func_ov068_0226c0e0(UnkStruct_022693f0 *a, char *b);
extern void func_ov068_0226cce8(UnkStruct_022693f0 *a, char *b, int c);
extern int func_ov068_022697cc(u8 *self, u8 *obj, int c);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern s16 data_ov068_02276724;

void func_ov068_022693f0(UnkStruct_022693f0 *a, char *b)
{
    if (func_02019e00(b + 0x564) == 3 && func_02019de8(b + 0x564) != 0) {
        func_02019c6c(b + 0x564, 1, data_020c80f8);
        a->unk_1C = 4;
        a->unk_20 = 10;
    } else {
        if (func_ov068_0226c0e0(a, b) != 0) {
            func_ov068_0226cce8(a, b, 0x13);
        }
    }
}

void func_ov068_02269314(u8 *self, u8 *obj)
{
    void *node;
    UnkStruct_02269314 *q;

    if (*(u16 *) (obj + 0xa06) >= data_ov068_02276724) {
        func_ov068_0226cce8((UnkStruct_022693f0 *) self, (char *) obj, 0x15);
        return;
    }
    if (func_ov068_0226c0e0((UnkStruct_022693f0 *) self, (char *) obj) != 0) {
        func_ov068_0226cce8((UnkStruct_022693f0 *) self, (char *) obj, 0x13);
        return;
    }
    if (*(int *) (self + 0x20) != 0) {
        return;
    }
    if (func_ov068_022697cc(self, obj, 0x3000) != 0) {
        func_02019d0c(obj + 0x564, 0xb, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        self[0x1c] = 2;
        *(int *) (self + 0x20) = 0xc8;
        return;
    }
    if (func_02019e00((char *) (obj + 0x564)) != 0) {
        return;
    }
    if (func_02019de8((char *) (obj + 0x564)) == 0) {
        return;
    }
    node = *(void **) (self + 0xe4);
    q = (UnkStruct_02269314 *) ((u8 *) node + 0x5c);
    func_02019d0c(obj + 0x564, 2, 1, q->unk_00, q->unk_08, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
    self[0x1c] = 1;
    *(int *) (self + 0x20) = 0xc8;
}
