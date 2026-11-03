/* item_texture_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203d228 @ 0x0203d228, 0x2 bytes, Thumb
 * func_0203d224 @ 0x0203d224, 0x2 bytes, Thumb
 * func_0203d064 @ 0x0203d064, 0x1c0 bytes, Thumb
 * func_0203cff8 @ 0x0203cff8, 0x6c bytes, Thumb
 * func_0203cfe4 @ 0x0203cfe4, 0x14 bytes, Thumb
 * func_0203cfd0 @ 0x0203cfd0, 0x14 bytes, Thumb
 * func_0203cfc8 @ 0x0203cfc8, 0x8 bytes, Thumb
 * func_0203cfc0 @ 0x0203cfc0, 0x8 bytes, Thumb
 * func_0203cfb8 @ 0x0203cfb8, 0x8 bytes, Thumb
 * func_0203cfb0 @ 0x0203cfb0, 0x8 bytes, Thumb
 * func_0203cfa8 @ 0x0203cfa8, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct Buf {
    u8 pad_00[0x20];
} Buf;

extern int data_021ed278;
extern void *data_020da8dc;
extern int data_021c6988;
extern u16 data_021c6984;
extern char data_021c698c;
extern void *func_02072a48(void *p, u8 idx);
extern void *func_02072bd0(void *p, u8 idx);
extern void *func_020996b8(void *ctx);
extern int func_02064328(Buf *b, void *tbl, int n, int m);
extern int func_02064af4(Buf *b, void *out, int n);
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_02072da0(void *p);
extern void *func_02072d4c(void *p);
extern void *func_02072f88(void *v);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern void *func_020579f0(int a, int b);
extern int func_02057988(int, int);
extern unsigned int func_021077e8(unsigned int *object);

int func_0203cff8(void *a, void *p);
void *func_0203cfe4(unsigned int *object);
int func_0203cfd0(unsigned int *object);
unsigned int func_0203cfc8(unsigned int *object);

void func_0203d228(void *object) {}

void func_0203d224(void *object) {}

inline static int IdxIn(u16 id, u16 lo, u16 hi)
{
    if ((id >= lo) && (id <= hi)) {
        return id - lo;
    }
    return -1;
}

int func_0203d064(void *out, const u16 *pid, void *ctx)
{
    Buf buf;
    int val;
    int idx;
    unsigned int ok = 0;
    u16 *ptr;
    u16 id;
    id = *pid;
    if ((id >= 0x12a8) && (id <= 0x12af)) {
        ok = 1;
    }
    if (ok > 0) {
        val = IdxIn(id, 0x12a8, 0x12af);
        idx = val;
        if (idx == (-1)) {
            return 0;
        }
        if (ctx == 0) {
            return func_0203cff8(out, func_02072a48(&data_021ed278, (u8) idx));
        }
        return func_0203cff8(out, func_02072bd0(func_020996b8(ctx), (u8) idx));
    }
    if ((id >= 0x1429) && (id <= 0x1430)) {
        idx = IdxIn(id, 0x1429, 0x1430);
        if (idx == (-1)) {
            return 0;
        }
        if (ctx == 0) {
            return func_0203cff8(out, func_02072a48(&data_021ed278, (u8) idx));
        }
        return func_0203cff8(out, func_02072bd0(func_020996b8(ctx), (u8) idx));
    }
    if ((id >= 0x13a0) && (id <= 0x13a7)) {
        idx = IdxIn(id, 0x13a0, 0x13a7);
        if (idx == (-1)) {
            return 0;
        }
        if (ctx == 0) {
            return func_0203cff8(out, func_02072a48(&data_021ed278, (u8) idx));
        }
        return func_0203cff8(out, func_02072bd0(func_020996b8(ctx), (u8) idx));
    }
    idx = IdxIn(id, 0x11a8, 0x12a7);
    if (idx != (-1)) {
        func_02064328(&buf, &data_020da8dc, idx >> 4, idx);
        if (func_02064af4(&buf, out, -1)) {
            return 1;
        }
        return 0;
    }
    if ((data_021c6988 & 1) == 0) {
        data_021c6984 = 0x11a8;
        ptr = &data_021c6984;
        __register_global_object((void *) (ptr), (((void *) func_020051b0)), (void *) (&data_021c698c));
        data_021c6988 |= 1;
    }
    return func_0203d064(out, &data_021c6984, ctx);
}

int func_0203cff8(void *a, void *p)
{
    unsigned short val = 0x11a8;
    void *tmp;

    if (func_0203d064(a, (const u16 *) (&val), 0) == 0) {
        goto zero;
    }
    if (p == 0) {
        goto one;
    }

    tmp = func_02072da0(p);
    MI_CpuCopy8(tmp, func_0203cfe4((unsigned int *) a), 0x200U);

    p = func_02072f88(func_02072d4c(p));
    MI_CpuCopy8(p, (void *) func_0203cfd0((unsigned int *) a), 0x20U);

    return 1;
one:
    return 1;
zero:
    return 0;
}

void *func_0203cfe4(unsigned int *object)
{
    return func_020579f0((int) func_0203cfc8(object), 0);
}

int func_0203cfd0(unsigned int *object)
{
    return func_02057988((int) func_0203cfc8(object), 0);
}

unsigned int func_0203cfc8(unsigned int *object)
{
    return func_021077e8(object);
}

int func_0203cfc0(void)
{
    return 708;
}

int func_0203cfb8(void *argument0, void *argument1, void *argument2)
{
    return func_0203d064((void *) argument0, (const u16 *) ((void *) argument1), (void *) argument2);
}

int func_0203cfb0(void *argument0, void *argument1)
{
    return func_0203cff8((void *) argument0, (void *) argument1);
}

unsigned int func_0203cfa8(unsigned int *data)
{
    return func_0203cfc8(data);
}
