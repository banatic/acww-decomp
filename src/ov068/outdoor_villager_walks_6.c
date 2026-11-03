/* outdoor_villager_walks_6: 7 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226cbf4 @ 0x0226cbf4, 0xc bytes, Thumb
 * func_ov068_0226cbe4 @ 0x0226cbe4, 0xe bytes, Thumb
 * func_ov068_0226cbc8 @ 0x0226cbc8, 0x1c bytes, Thumb
 * func_ov068_0226cb00 @ 0x0226cb00, 0xc8 bytes, Thumb
 * func_ov068_0226caac @ 0x0226caac, 0x54 bytes, Thumb
 * func_ov068_0226ca74 @ 0x0226ca74, 0x38 bytes, Thumb
 * func_ov068_0226ca2c @ 0x0226ca2c, 0x48 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
} Pair;

struct UnkStruct_0226caac {
    int halfExtentX;
    int halfExtentY;
    int top;
    int bottom;
};

struct UnkStruct_0226caac_2 {
    int x;
    int pad_04;
    int y;
};

struct UnkStruct_0226caac_3 {
    int x;
    int pad_04;
    int y;
};

extern unsigned int data_ov068_0227673c;
extern unsigned short func_020644cc(int);
extern void func_ov068_0226cfd4(void *);
extern int func_02019c6c(void *, int, unsigned short);
extern void func_02013c0c(void *);
extern void func_ov068_02266c70(void *, void *);
extern int func_02013894(void *);
extern void func_020138a4(void *, int);
extern void func_ov068_0226c964(void *, int, void *);
extern void func_0202e188(void *);
extern void func_0201cbc4(void *);
extern Pair data_ov068_022770a8;
extern unsigned short data_020c80f8;
extern unsigned int data_021c67a4;
extern unsigned int data_021c67d0[3];
extern int func_02013300(const void *);
extern int data_ov068_022767ac[];

void func_ov068_0226cbf4(unsigned int *r0)
{
    r0[9] = data_ov068_0227673c;
}

int func_ov068_0226cbe4(void *arg0, int arg1)
{
    if (*(int *) ((char *) arg0 + 0x10) == arg1) {
        return 1;
    }
    return 0;
}

void func_ov068_0226cbc8(short *r4)
{
    r4[0x1a] = func_020644cc(0x1770);
    r4[0x1b] = -1;
}

int func_ov068_0226cb00(u8 *self, u8 *other)
{
    u8 *ptr;
    u8 **ptr2;
    func_ov068_0226cfd4(other);
    *(Pair *) (other + 0x8b0) = data_ov068_022770a8;
    ptr = self;
    func_02019c6c(other + 0x564, 1, data_020c80f8);
    func_02013c0c(other + 0x558);
    func_ov068_02266c70(other + 0x898, other);
    if (func_02013894(ptr + 0x3c) != 0) {
        func_020138a4(self + 0x3c, 0);
    } else {
        func_ov068_0226c964(self, 0, other);
        *((short *) (self + 0xd8)) = -1;
        *((short *) (self + 0xda)) = 0;
    }
    func_0202e188(other);
    *((u8 *) (other + 0x561)) = 1;
    *((u8 *) (other + 0x562)) = 1;
    *((u32 *) (self + 0xf8)) = -1;
    ptr2 = &other;
    *((u8 *) (other + 0x9f0)) = 1;
    func_0201cbc4((*ptr2) + 0x83c);
    return 1;
}

int func_ov068_0226caac(struct UnkStruct_0226caac *s, struct UnkStruct_0226caac_2 *a, struct UnkStruct_0226caac_3 *b)
{
    int result = 0;
    int flag2 = 0;
    int flag1 = result;

    if (b->x > a->x - s->halfExtentX && b->x < a->x + s->halfExtentY) {
        flag1 = 1;
    }
    if (flag1) {
        if (b->y > a->y - s->top) {
            flag2 = 1;
        }
    }
    if (flag2) {
        if (b->y < a->y + s->bottom) {
            result = 1;
        }
    }
    return result;
}

int func_ov068_0226ca74(unsigned int arg0, char *arg1)
{
    char *dst = arg1 + 0x5c;
    int ret = 0;
    if (data_021c67a4 != 0) {
        unsigned int local[3];
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        ret = func_ov068_0226caac((struct UnkStruct_0226caac *) arg0, (struct UnkStruct_0226caac_2 *) local, (struct UnkStruct_0226caac_3 *) dst);
    }
    return ret;
}

int func_ov068_0226ca2c(void *p)
{
    int idx, val, nxt;

    idx = (int) func_020644cc(func_02013894((void *) ((char *) p + 0x3c)) ? 2 : 3);
    val = data_ov068_022767ac[idx];
    if (val == func_02013300((char *) p + 0x3c)) {
        nxt = idx + 1 < 3 ? idx + 1 : 0;
        val = data_ov068_022767ac[nxt];
    }
    return val;
}
