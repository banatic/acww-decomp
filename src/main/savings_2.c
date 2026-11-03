/* savings_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020981f4 @ 0x020981f4, 0x104 bytes, Thumb
 * func_020980f0 @ 0x020980f0, 0x104 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020981f4 {
    int d[8];
};

struct BIG {
    int d[64];
};

struct UnkStruct_020980f0 {
    int pad_00[0x41];
};

extern void *func_020984e8(void);
extern int func_020992fc(int);
extern int func_020983f0(int *);
extern int func_02099020(void *, int);
extern void func_02066694(struct BIG *);
extern void *func_020641c8(struct UnkStruct_020981f4 *);
extern void func_02064210(void *, struct UnkStruct_020981f4 *);
extern int func_0203d7c4(int, struct UnkStruct_020981f4 *);
extern int func_02099870(void *);
extern void func_02066024(struct BIG *, u8 *, void *, void *, void *, int);
extern unsigned short func_02065ed0(struct BIG *, int, int);
extern int func_02097a54(struct BIG *);
extern void func_02098ff8(void *, int);
extern void *func_020641b0(struct UnkStruct_020981f4 *);
extern void func_02066688(struct BIG *);
extern u8 data_021dc7aa[];
extern u8 data_020e3104[];
extern u8 data_020e3118[];
extern u8 data_020e3108[];
extern int func_020983c4(int);
extern void func_02098fd0(int, int);
extern u8 data_020e3114[];
extern u8 data_020e3100[];

void func_020981f4(int a)
{
    u8 kind;
    struct UnkStruct_020981f4 s2;
    struct BIG big;
    void *p;
    int *account;
    int v, cost, idx, t;

    p = func_020984e8();
    account = (int *) func_020992fc((int) p);
    if (a > 0) {
        v = func_020983f0(account);
        if (v >= 1000000) {
            cost = 0x37dc;
            idx = 0;
            if (v == 999999999) {
                idx = 4;
                cost = 0x3874;
            } else if (v >= 500000000) {
                idx = 3;
                cost = 0x4a44;
            } else if (v >= 100000000) {
                idx = 2;
                cost = 0x4a40;
            } else if (v >= 10000000) {
                idx = 1;
                cost = 0x3700;
            }
            t = idx + 0x11;
            if (func_02099020(p, t) == 0) {
                kind = (u8) (idx + 0x15);
                func_02066694(&big);
                func_020641c8(&s2);
                func_02064210(data_021dc7aa, &s2);
                func_0203d7c4(0, &s2);
                func_02066024(&big, &kind, data_020e3118, data_020e3108, data_020e3104, func_02099870(p));
                func_02065ed0(&big, cost, 1);
                if (func_02097a54(&big)) {
                    func_02098ff8(p, t);
                }
                func_020641b0(&s2);
                func_02066688(&big);
            }
        }
    }
}

void func_020980f0(int a)
{
    u8 c;
    struct UnkStruct_020980f0 s;
    int p, q, v, msg;

    p = (int) func_020984e8();
    q = func_020992fc(p);
    if (a > 0 && func_02099020((void *) p, 0x16)) {
        v = func_020983c4(q);
        func_02066694((struct BIG *) (&s));
        c = (u8) v;
        func_02066024((struct BIG *) (&s), &c, data_020e3118, data_020e3100, data_020e3114, func_02099870((void *) p));
        msg = 0xfff1;
        switch (v) {
            case 1:
                msg = 0x13fe;
                break;
            case 4:
                msg = 0x13ff;
                break;
            case 7:
                msg = 0x1400;
                break;
            case 10:
                msg = 0x1401;
                break;
            case 13:
                msg = 0x1402;
                break;
            case 16:
                msg = 0x1403;
                break;
            case 20:
                msg = 0x1404;
                break;
        }
        if (msg != 0xfff1) {
            func_02065ed0((struct BIG *) (&s), msg, 1);
        }
        if (func_02097a54((struct BIG *) (&s))) {
            func_02098fd0(p, 0x16);
        }
        func_02066688((struct BIG *) (&s));
    }
}
