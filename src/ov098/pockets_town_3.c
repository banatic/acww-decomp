/* pockets_town_3: 7 functions, module ov098
 * mwccarm 1.2/base -O4,s
 * func_ov098_022a31d8 @ 0x022a31d8, 0x50 bytes, Thumb
 * func_ov098_022a30a4 @ 0x022a30a4, 0x134 bytes, Thumb
 * func_ov098_022a3060 @ 0x022a3060, 0x44 bytes, Thumb
 * func_ov098_022a2fc0 @ 0x022a2fc0, 0xa0 bytes, Thumb
 * func_ov098_022a2fa8 @ 0x022a2fa8, 0x16 bytes, Thumb
 * func_ov098_022a2f2c @ 0x022a2f2c, 0x7c bytes, Thumb
 * func_ov098_022a2ec0 @ 0x022a2ec0, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int pad1;
    int b;
} UnkStruct_022a2fc0;

typedef struct {
    unsigned char pad_00[0x5c];
    UnkStruct_022a2fc0 sub;
    unsigned char pad1[0x8e - 0x68];
    short c;
} UnkStruct_022a2fc0_2;

typedef struct UnkStruct_022a2f2c {
    u8 pad_00[0xb6];
    u8 unk_B6;
} UnkStruct_022a2f2c;

struct BigStruct {
    unsigned char pad_00[0x2e14];
    int unk_2E14;
    unsigned char pad_2E18[4];
    int unk_2E1C;
};

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_ov094_022999e4(unsigned int);
extern int func_ov002_02208d4c(void *w, int a, int b);
extern int func_ov098_022a2bfc(void *self);
extern void func_ov096_0229c2dc(void *, int);
extern int func_02073d90(int);
extern void func_ov096_0229c2ec(void *, int);
extern int data_020ccf94;
extern int func_020961a8(int);
extern int func_0204f658(int, int, int);
extern int func_0203162c(void *a, void *b, int c, int d, int e, int f);
extern int data_021c80bc;
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern unsigned char func_ov096_0229cbbc(void *self);
extern unsigned short func_ov096_0229f0dc(UnkStruct_022a2f2c *self, u8 kind);
extern int func_ov003_0222780c(int a, int b, void *p);
extern void func_ov098_022a2eb4(UnkStruct_022a2f2c *self, u8 idx);
extern int func_ov003_02219b38(int a);
extern unsigned char *func_ov096_0229f860(UnkStruct_022a2f2c *self);
extern void func_020779b8(char *dst, int a, int b);
extern void MI_CpuCopy8(char *dst, char *src, int len);
extern void func_02073820(void *ptr);
extern void func_020737f0(void *ptr, char *buf, int len);
extern void func_02073770(void *ptr, int a, int b);

int func_ov098_022a2fc0(char *p, int flag);
void func_ov098_022a2f2c(UnkStruct_022a2f2c *self);

int func_ov098_022a31d8(void *a, unsigned int v)
{
    volatile long long unused;
    (void) &unused;
    if (func_02099020(func_020984e8(), 1) != 0) {
        if ((v >= 0x14fe && v <= 0x1517) || (v >= 0x151d && v <= 0x151e)) {
            return 0;
        }
    }
    return func_ov094_022999e4(v);
}

void func_ov098_022a30a4(char *self, u16 id)
{
    u16 v;
    int f;
    u16 a0, a1;

    v = id;

    f = 0;
    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12b0 && a0 <= 0x12e7) {
        f = 1;
    }
    if (f != 0 || (a0 >= 0x12e8 && a0 <= 0x131f)) {
        func_ov002_02208d4c(self + 0x294c, 0x1b, 0x21);
    }

    f = 0;
    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12b0 && a0 <= 0x12e7) {
        f = 1;
    }
    if (f != 0) {
        func_ov002_02208d4c(self + 0x294c, 8, 0x15);
        return;
    }
    if (a0 >= 0x12e8 && a0 <= 0x131f) {
        if (func_ov098_022a2fc0((char *) self, 0) != 0) {
            func_ov002_02208d4c(self + 0x294c, 8, 0x18);
        }
        return;
    }
    if ((a0 >= 0x137c && a0 <= 0x137c) || (a0 >= 0x1408 && a0 <= 0x1428) || (a0 >= 0x1471 && a0 <= 0x1491) ||
        (a0 >= 0x14fe && a0 <= 0x1517) || (a0 >= 0x151d && a0 <= 0x151e) || (a0 >= 0x1567 && a0 <= 0x1567)) {
        func_ov002_02208d4c(self + 0x294c, 6, 0x17);
        return;
    }
    if (func_ov098_022a2bfc(self) != 0) {
        func_ov002_02208d4c(self + 0x294c, 7, 0x16);
    }
}

void func_ov098_022a3060(void *param)
{
    func_ov096_0229c2dc(param, 8);
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (func_ov098_022a2fc0((char *) param, 1) == 0) {
        return;
    }
    func_ov002_02208d4c((char *) param + 0x294c, 0x11, 0x19);
    func_ov096_0229c2ec(param, 8);
}

int func_ov098_022a2fc0(char *p, int flag)
{
    UnkStruct_022a2fc0_2 *obj;
    int period;
    UnkStruct_022a2fc0 *sub;
    int result;

    obj = (UnkStruct_022a2fc0_2 *) func_020961a8(4);
    sub = &obj->sub;
    period = 0xa00;
    result = func_0204f658(data_021c80bc, obj->sub.a >> 17, sub->b >> 17);

    if (flag) {
        if ((result & 0x7f000) == 0 && (result & 8) == 0) {
            return 0;
        }
        period = 0x1b58;
    } else {
        if ((result & 0x7f000) != 0 || (result & 8) != 0) {
            period += 0xe10;
        } else {
            period += 0x3e8;
        }
    }

    return func_0203162c(p + 0x2e14, sub, obj->c, 0x7800, period, 0xc);
}

void func_ov098_022a2fa8(void *p)
{
    func_ov002_02208098(p, 0x30);
    func_ov098_022a2f2c((UnkStruct_022a2f2c *) p);
}

void func_ov098_022a2f2c(UnkStruct_022a2f2c *self)
{
    volatile u16 id;
    int a;
    int b;

    a = func_ov096_0229cbbc(self);
    b = func_ov096_0229f0dc(self, self->unk_B6);
    if (func_ov003_0222780c(a, b, (u8 *) self + 0x2e14) != 0) {
        u8 idx;
        id = (u16) b;
        {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x12e8 && hi <= 0x131f) {
                ok = 1;
            }
            idx = (u8) (ok > 0 ? hi - 0x12e8 : -1);
        }
        func_ov098_022a2eb4(self, idx);
        func_ov003_02219b38(1);
        func_ov096_0229f860(self);
    }
}

void func_ov098_022a2ec0(struct BigStruct *obj, char a, char b)
{
    if (func_02073d90((int) ((*(void * *) &data_020ccf94)))) {
        char buffer[16];
        void *ptr;
        buffer[0] = b;
        buffer[1] = a;
        func_020779b8(buffer + 7, obj->unk_2E14, obj->unk_2E1C);
        MI_CpuCopy8(buffer + 7, buffer + 2, 5);
        ptr = (*(void * *) &data_020ccf94);
        func_02073820(ptr);
        func_020737f0(ptr, buffer, 7);
        func_02073770(ptr, 22, 4);
    }
}
