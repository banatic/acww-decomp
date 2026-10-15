/* func_020981f4 @ 0x020981f4, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020981f4 {
    int d[8];
};
struct BIG {
    int d[64];
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
extern u8 data_020e3104[], data_020e3118[], data_020e3108[];

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
