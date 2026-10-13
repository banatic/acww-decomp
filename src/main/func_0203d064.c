/* func_0203d064 @ 0x0203d064, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
extern int func_0203cff8(void *out, void *s);
extern void func_02064328(Buf *b, void *tbl, int n, int m);
extern int func_02064af4(Buf *b, void *out, int n);
extern void func_020051b0(void);
extern void __register_global_object(void *obj, void (*dtor)(void), void *node);
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
        __register_global_object(ptr, func_020051b0, &data_021c698c);
        data_021c6988 |= 1;
    }
    return func_0203d064(out, &data_021c6984, ctx);
}
