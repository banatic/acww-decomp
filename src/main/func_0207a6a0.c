/* func_0207a6a0 @ 0x0207a6a0, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0207a6a0_2 {
    u16 id;
};

extern void func_020791a4(char);
extern int func_020b65c4(void);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern int func_02099734(void *);
extern int func_02098eb8(int);
extern int func_02099870(void *);
extern struct UnkStruct_0207a6a0_2 *func_020992e4(void *);
extern int func_020951bc(int);
extern void func_0209e474(void *);
extern int func_020992ac(void *);
extern struct UnkStruct_0207a6a0_2 *func_0207a764(void *, int);
extern int func_0207cf74(void *);
extern void func_0207a180(void *);

void func_0207a6a0(void *self, void *arg1)
{
    int p;
    struct UnkStruct_0207a6a0 {
        u32 a, b;
    } s;
    struct UnkStruct_0207a6a0_2 *r4;
    u8 b5;
    int cmp;

    if ((func_020791a4(-1), func_020b65c4()) != 6) {
        return;
    }

    if (arg1 == 0) {
        arg1 = func_020984e8();
    }
    if (arg1 == 0) {
        return;
    }

    if (func_02099020(arg1, 1) != 0) {
        return;
    }

    if (func_02098eb8(func_02099734(arg1)) == -1) {
        return;
    }

    p = func_02099870(arg1);
    r4 = func_020992e4(arg1);
    if (r4->id == 0) {
        return;
    }
    if (func_020951bc(p) == 0) {
        return;
    }

    s.a = 0;
    s.b = 0;
    func_0209e474(&s);

    b5 = ((u8 *) &s)[5];

    cmp = func_020992ac(arg1);
    if (cmp == b5) {
        return;
    }

    if (((u8 *) r4)[1] != ((u8 *) &s)[4]) {
        return;
    }
    if (((u8 *) r4)[0] != ((u8 *) &s)[3]) {
        return;
    }
    if (((u8 *) &s)[2] < 6) {
        return;
    }

    r4 = func_0207a764(self, p);
    if (func_0207cf74(r4) != 0) {
        func_0207a180((char *) self + 0x3f7c);
    }
    func_020791a4((signed char) (int) r4);
}
