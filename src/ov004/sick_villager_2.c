/* sick_villager_2: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02222820 @ 0x02222820, 0x5c bytes, Thumb
 * func_ov004_022227e8 @ 0x022227e8, 0x38 bytes, Thumb
 * func_ov004_022227b8 @ 0x022227b8, 0x30 bytes, Thumb
 * func_ov004_02222728 @ 0x02222728, 0x90 bytes, Thumb
 * func_ov004_0222271c @ 0x0222271c, 0xc bytes, Thumb
 * func_ov004_022226f8 @ 0x022226f8, 0x24 bytes, Thumb
 * func_ov004_022226d4 @ 0x022226d4, 0x24 bytes, Thumb
 * func_ov004_022226b4 @ 0x022226b4, 0x20 bytes, Thumb
 * func_ov004_0222269c @ 0x0222269c, 0x18 bytes, Thumb
 * func_ov004_022225fc @ 0x022225fc, 0xa0 bytes, Thumb
 * func_ov004_02222554 @ 0x02222554, 0xa8 bytes, Thumb
 * func_ov004_0222251c @ 0x0222251c, 0x38 bytes, Thumb
 * func_ov004_022223b8 @ 0x022223b8, 0x164 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02222820 {
    void *unk_00;
    u32 unk_04;
    u32 unk_08;
};

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_022227e8;

typedef struct {
    char pad_00[0x1a8];
    int unk_1A8;
} UnkStruct_022226b4;

extern struct UnkStruct_02222820 *data_021c80bc;
extern int func_02037e0c(void *, int, int, int);
extern int func_0204bc90(int tile);
extern void func_020308e0(int, int);
extern int func_020984e8(void);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);
extern int func_02014868(void *);
extern int func_ov004_02222178(void *self, int a);
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *p, int n);
extern char data_021e5a2c[];
extern int func_0207b410(char *p);
extern int func_0209a67c(int v);
extern void func_0209a664(int arg0, int arg1);
extern void func_0202dc3c(void *ptr, int value, int count);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void *func_0206fc8c(void);
extern void func_0209a050(void *h);
extern int func_020644cc(int k);
extern void func_0206844c(void *a, void *b, int c);
extern int func_02015330(void *self, void *obj, int a, int b, int c);
extern int func_0208150c(int a);
extern int func_0200366c(int a, void *b, int c, void *d);
extern int data_ov004_02257f9c;
extern int data_ov004_022542b0;
extern int data_ov004_022542bc;
extern int func_0209a6ec(void *);
extern void func_02015e40(void *, int, int);
extern void *func_0206837c(int);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, unsigned char *, int, void *, int, int);
extern void func_020ab5f8(void *);
extern void func_02068388(int, int);
extern char data_021f43f8[];
extern void func_0200467c(int);

void func_ov004_02222820(void *receiver)
{
    struct UnkStruct_02222820 *q;
    void *base;
    int y;
    int x;
    int zero;
    int tile;

    zero = 0;
    q = data_021c80bc;
    if (q->unk_04 > zero && q->unk_08 > zero && q->unk_00 != 0) {
        base = q->unk_00;
    } else {
        base = 0;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            if ((tile = func_02037e0c(base, x, y, zero)) != 0 && func_0204bc90(tile) != 0) {
                func_020308e0(x, y);
            }
        }
    }
}

void func_ov004_022227e8(UnkStruct_022227e8 *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8();
    if (a == 0) {
        return;
    }
    if (param->unk_830 == 0) {
        return;
    }
    b = func_02099870(a);
    c = func_020804b8(param->unk_830, b);
    func_02081e14(c, 0, 0, 0);
}

int func_ov004_022227b8(u8 *self)
{
    if (func_02014868(self + 0x618) != 0) {
        return 0;
    }
    return (*(unsigned int *) (self + 0x89c) <= 1) ? 1 : 0;
}

void func_ov004_02222728(char *self, unsigned int k, int a2)
{
    volatile int v[3];
    int t;

    v[0] = *(int *) (self + 0x5c);
    t = *(int *) (self + 0x60);
    v[1] = t;
    v[2] = *(int *) (self + 0x64);
    v[1] = t + 0x2000;
    switch (k) {
        case 3:
            *(char *) (self + 0x560) = (char) a2;
            func_ov004_02222178(self, 2);
            break;
        case 0:
            *(char *) (self + 0x560) = (char) a2;
            func_02016108(self + 0x8a0, func_0201c2a4(self, 4));
            func_ov004_02222178(self, 3);
            break;
        case 8:
            func_ov004_022227e8((UnkStruct_022227e8 *) self);
            func_ov004_02222178(self, 0);
            break;
        case 4:
            func_ov004_02222178(self, 0);
            break;
    }
}

int func_ov004_0222271c(char *self)
{
    // DECLS
    // ENDDECLS
    return *(u8 *) (self + 0x1a4);
}

int func_ov004_022226f8(void *receiver)
{
    int r;
    if (func_0209a67c(func_0207b410(data_021e5a2c)) != 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

void func_ov004_022226d4(void)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_0207b410((char *) ((unsigned int) (((void * *) data_021e5a2c))));
    func_0209a664(v1, func_02099870(func_020984e8()));
}

void func_ov004_022226b4(UnkStruct_022226b4 *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A8 = val;
}

void func_ov004_0222269c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (a1 == 0x4) {
        func_ov004_022226d4();
        *(int *) ((char *) *(int *) (self + 0x40) + 0x8) = 0x1;
    }
}

void func_ov004_022225fc(void *self)
{
    unsigned char b[4];

    if (*(int *) ((char *) *(void **) ((char *) self + 0x1a8) + 0x89c) == 6 && func_0206fbc0() != 0) {
        if (func_0206fc6c() == 0) {
            *(int *) ((char *) *(void **) ((char *) self + 0x40) + 8) = 1;
            b[0] = (unsigned char) (func_020644cc(3) + 0xd);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[0], 0);
            func_ov004_02222178(*(void **) ((char *) self + 0x1a8), 4);
        } else {
            func_0209a050(func_0206fc8c());
            b[1] = (unsigned char) (func_020644cc(3) + 0x10);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[1], 0);
            *(short *) (b + 2) = 0x155e;
            func_02015330(self, b + 2, 0, 6, 0);
            func_ov004_02222178(*(void **) ((char *) self + 0x1a8), 7);
        }
    }
}

void func_ov004_02222554(char *self, char *out)
{
    char *h;

    *(int *) out = (int) &data_ov004_02257f9c;
    func_ov004_0222271c((char *) self);
    h = *(char **) (self + 0x1a8);
    if (*(unsigned char *) (h + 0x897) == 0) {
        func_0200366c(func_0208150c(*(int *) (h + 0x830)), &data_ov004_02257f9c, 0x28, &data_ov004_022542b0);
    } else {
        func_0200366c(func_0208150c(*(int *) (h + 0x830)), &data_ov004_02257f9c, 0x28, &data_ov004_022542bc);
    }
    *(char *) (*(char **) (self + 0x1a8) + 0x899) = 0;
    if (func_ov004_022226f8(self) != 0) {
        out[4] = (char) (func_020644cc(3) + 3);
        *(char *) (*(char **) (self + 0x1a8) + 0x898) = 1;
    } else {
        out[4] = (char) func_020644cc(3);
        *(char *) (*(char **) (self + 0x1a8) + 0x898) = 0;
    }
}

void func_ov004_0222251c(void *self)
{
    void *o;
    o = (void *) func_0207b410((char *) (((int *) data_021e5a2c)));
    if (o != 0) {
        if (func_0209a6ec(o) != 0) {
            func_02015e40(self, func_0209a6ec(o), 0);
        }
    }
}

void func_ov004_022223b8(unsigned char *self)
{
    unsigned char *owner = *(unsigned char **) (self + 0x1a8);
    void *window;
    unsigned char values[5];
    if (owner[0x899] == 0) {
        switch (self[0x1e]) {
            case 0:
            case 1:
            case 2:
                window = func_0206837c(*(int *) (self + 0x40));
                if (window) {
                    func_020ab670(window, 3, 2);
                    values[0] = 21;
                    func_020ab628(window, 0, &values[0], 0, data_021f43f8, 0, 0);
                    values[1] = 22;
                    func_020ab628(window, 1, &values[1], 0, data_021f43f8, 0, 0);
                    values[2] = func_020644cc(10) + 10;
                    func_020ab628(window, 2, &values[2], 0, data_021f43f8, 0, 0);
                    func_020ab5f8(window);
                    func_02068388(*(int *) (self + 0x40), 1);
                }
                break;
            case 3:
            case 4:
            case 5:
                window = func_0206837c(*(int *) (self + 0x40));
                if (window) {
                    func_020ab670(window, 2, 1);
                    values[3] = 23;
                    func_020ab628(window, 0, &values[3], 0, data_021f43f8, 0, 0);
                    values[4] = func_020644cc(10) + 120;
                    func_020ab628(window, 1, &values[4], 0, data_021f43f8, 0, 0);
                    func_020ab5f8(window);
                    func_02068388(*(int *) (self + 0x40), 1);
                }
                break;
        }
    } else {
        switch (self[0x1e]) {
            case 7:
            case 8:
            case 9:
                func_ov004_02222178(owner, 5);
                break;
            case 16:
            case 17:
            case 18:
                func_0200467c(95);
                break;
        }
    }
}
