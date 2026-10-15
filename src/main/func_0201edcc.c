/* func_0201edcc @ 0x0201edcc, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0201edcc {
    u16 a;
    u16 b;
} UnkStruct_0201edcc;
typedef struct UnkStruct_0201edcc_2 {
    u8 d[8];
} UnkStruct_0201edcc_2;

typedef struct UnkStruct_0201edcc_3 {
    u8 pad_00[0x124];
    UnkStruct_0201edcc h;
    u8 pad_128[0x19c - 0x128];
    u16 w;
} UnkStruct_0201edcc_3;

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern int func_0204bcdc(UnkStruct_0201edcc *h);
extern int func_0204bc64(void *h);
extern int func_020644cc(int n);
extern void func_02063ccc(UnkStruct_0201edcc_2 *k, void *x, int z);
extern void func_02063cc8(UnkStruct_0201edcc_2 *k);
extern void func_020638d4(UnkStruct_0201edcc *h, UnkStruct_0201edcc_2 *k, int a, int b, int c, int d, int e);
extern int func_02098f0c(int b, u16 *w, int c, int d);
extern int func_020996ac(int a);
extern int OSi_DoUnlockByWord__main_0203cd2c(int r, u16 *w, int a, int b);
extern int func_020154b4(UnkStruct_0201edcc_3 *p, u16 *w, int a, int b, int c);
extern void func_02015de4(UnkStruct_0201edcc_3 *p, u16 *w, int a, int b);
extern void *data_020c8e98[];

void func_0201edcc(UnkStruct_0201edcc_3 *p)
{
    int a;
    int b;
    int c;
    int t;
    int k;
    UnkStruct_0201edcc loc;
    UnkStruct_0201edcc_2 obj;

    a = func_020984e8();
    b = func_02099734(a);
    c = func_02098eb8(b);
    if (c == -1) {
        c = 0;
    }
    if (func_0204bcdc(&p->h)) {
        loc.b = 0x1546;
        t = (func_0204bc64(&p->h) == func_0204bc64(&loc.b));
    } else {
        t = (p->h.a == 0x1546);
    }
    if (t) {
        p->w = 0x1566;
    } else {
        k = func_020644cc(3);
        func_02063ccc(&obj, data_020c8e98[k], 0);
        func_020638d4(&loc, &obj, 0, 0, 1, 1, 0);
        p->w = loc.a;
        func_02063cc8(&obj);
    }
    func_02098f0c(b, &p->w, c, 0);
    OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(a), &p->w, 0, 1);
    func_020154b4(p, &p->w, 0, 5, 0);
    if (p->w != 0xfff1) {
        func_02015de4(p, &p->w, 0, 7);
    }
}
