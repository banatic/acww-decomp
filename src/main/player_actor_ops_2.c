/* player_actor_ops_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02095ce0 @ 0x02095ce0, 0x24 bytes, Thumb
 * func_02095bdc @ 0x02095bdc, 0x104 bytes, Thumb
 * func_02095ba8 @ 0x02095ba8, 0x34 bytes, Thumb
 * func_02095b9c @ 0x02095b9c, 0xc bytes, Thumb
 * func_02095b90 @ 0x02095b90, 0xc bytes, Thumb
 * func_02095b84 @ 0x02095b84, 0xc bytes, Thumb
 * func_02095b64 @ 0x02095b64, 0x20 bytes, Thumb
 * func_02095b58 @ 0x02095b58, 0xc bytes, Thumb
 * func_02095b4c @ 0x02095b4c, 0xc bytes, Thumb
 * func_02095b40 @ 0x02095b40, 0xc bytes, Thumb
 * func_02095b1c @ 0x02095b1c, 0x24 bytes, Thumb
 * func_02095aec @ 0x02095aec, 0x2e bytes, Thumb
 * func_02095ab0 @ 0x02095ab0, 0x3a bytes, Thumb
 * func_02095a8c @ 0x02095a8c, 0x24 bytes, Thumb
 * func_02095a4c @ 0x02095a4c, 0x3e bytes, Thumb
 * func_02095a28 @ 0x02095a28, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02095bdc {
    u8 pad_00[0x7f0];
    int a;
    int b0;
    int b1;
    int d;
    u8 pad_800[0x8eb - 0x800];
    s8 e;
} UnkStruct_02095bdc;

struct UnkStruct_02095ab0 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern int func_02096718(int);
extern int func_0200c9a8(int, int, int, int);
extern volatile u8 data_020e54a8;
extern int func_02008258(UnkStruct_02095bdc *p, int v);
extern void *func_020094a0(UnkStruct_02095bdc *p, u8 k, u8 c, u8 d, unsigned int e, short f);
extern void func_020110c4(u16 *x, UnkStruct_02095bdc *p);
extern int func_0204bcdc(u16 *x);
extern int func_0204bc64(u16 *x);
extern int func_0200fc90(UnkStruct_02095bdc *p);
extern int func_ov003_02217c5c(UnkStruct_02095bdc *p, int a, int b, int c, int d, int e, int f, int h);
extern int func_0200d4e8(UnkStruct_02095bdc *p, int a, int b, int c);
extern int func_0200c904(int, unsigned short, int, int, int, int);
extern int func_02009d38(int, int, int, int);
extern int func_02008750(int, void *, int, int);
extern int func_02009a44(int, void *, int, int, int);
extern int func_020095b0(int, int, int, int);
extern void *func_0200a448(void *, int, int, unsigned char, int, int, int, int);
extern int func_0200a254(int, int, int);

int func_02095ce0(void)
{
    int res = func_02096718(4);
    if (res != 0) {
        return func_0200c9a8(res, 3, 5, -1);
    }
    return 0;
}

int func_02095bdc(void)
{
    UnkStruct_02095bdc *p;
    int v;
    int n;
    int t;
    int t2;
    u16 x[2];

    p = (UnkStruct_02095bdc *) func_02096718(4);
    if (p != 0) {
        v = p->a;
        n = p->e;
        p->e = 0;
        if (v == 0x2c || v == 0x29 || v == 0x2a) {
            return 1;
        }
        p->d = func_02008258(p, v);
        if (n > 0) {
            return (int) func_020094a0(p, (u8) (n + 3), 0, 0, 6, -1);
        } else {
            t = (data_020e54a8 == 0);
            if (t) {
                func_020110c4(x, p);
                if (func_0204bcdc(x)) {
                    x[1] = 0xfff1;
                    t2 = (func_0204bc64(&x[0]) == func_0204bc64(&x[1]));
                } else {
                    t2 = (x[0] == 0xfff1);
                }
                if (!t2 && !func_0200fc90(p) && v != 0x39) {
                    return func_ov003_02217c5c(p, 2, 2, 0, 0, 0, 6, -1);
                }
            }
            return func_0200d4e8(p, 3, 5, -1);
        }
    } else {
        return 0;
    }
}

int func_02095ba8(unsigned short *a, int b, int c)
{
    int res = func_02096718(4);
    if (res != 0) {
        return func_0200c904(res, *a, b, c, 6, -1);
    } else {
        return 0;
    }
}

int func_02095b9c(void *param1)
{
    return func_02095ba8((unsigned short *) param1, 0, 5);
}

int func_02095b90(int a)
{
    return func_02095ba8((unsigned short *) a, 1, 5);
}

int func_02095b84(int a)
{
    return func_02095ba8((unsigned short *) a, 2, 5);
}

int func_02095b64(void)
{
    unsigned short local;
    unsigned short *ptr;

    local = 0xFFF1;
    ptr = &local;
    return func_02095ba8(ptr, 3, 5);
}

int func_02095b58(void *param1)
{
    return func_02095ba8((unsigned short *) param1, 0, 0x10);
}

void func_02095b4c(int a)
{
    func_02095ba8((unsigned short *) a, 1, 16);
}

int func_02095b40(int a)
{
    return func_02095ba8((unsigned short *) a, 2, 0x10);
}

int func_02095b1c(unsigned short *arg0)
{
    int ret = func_02096718(4);
    if (ret != 0) {
        ret = func_02009d38(ret, *arg0, 6, -1);
    } else {
        ret = 0;
    }
    return ret;
}

int func_02095aec(unsigned short *param)
{
    int r;
    r = func_02096718(4);
    if (r != 0) {
        unsigned short tmp;
        tmp = *param;
        return func_02008750(r, &tmp, 6, -1);
    } else {
        return 0;
    }
}

int func_02095ab0(struct UnkStruct_02095ab0 *p, int arg2, void *arg3)
{
    int result;
    struct UnkStruct_02095ab0 local;

    result = func_02096718((int) arg3);
    if (result != 0) {
        local.unk_00 = p->unk_00;
        local.unk_04 = p->unk_04;
        local.unk_08 = p->unk_08;
        result = func_02009a44(result, &local, arg2, 5, -1);
    } else {
        result = 0;
    }
    return result;
}

int func_02095a8c(int a, int b)
{
    int x;
    x = func_02096718(b);
    if (x != 0) {
        return func_020095b0(x, a, 5, -1);
    } else {
        return 0;
    }
}

void *func_02095a4c(int a, int *b, unsigned char *c, int *d, int e)
{
    void *ptr;

    ptr = (void *) func_02096718(4);
    if (ptr != 0) {
        return func_0200a448(ptr, a, *b, *c, *d, e, 6, -1);
    }
    return 0;
}

int func_02095a28(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_0200a254(r, 6, -1);
    }
    return 0;
}
