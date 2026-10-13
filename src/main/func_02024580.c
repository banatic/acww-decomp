/* func_02024580 @ 0x02024580, 0x3f8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define P32(o) (*(int *) (p + (o)))
#define P16(o) (*(u16 *) (p + (o)))

extern int func_020984e8(void);
extern int func_02099734(void);
extern int func_0209b91c(int);
extern int func_020644cc(int);
extern int func_0209b914(int);
extern int func_0209bc40(int);
extern int func_0205be38(void);
extern int func_0202b510(int);
extern void func_02027170(u16 *, int);
extern void func_0207ddd0(u16 *, int);
extern void func_0207de70(int, u16 *);
extern void func_0207de14(u16 *, int);
extern void func_0202d5e4(u16 *, int);
extern void func_0202d5cc(u16 *, int);
extern void func_02098a24(int, int, int);
extern int func_02098eb8(int);
extern void func_02098f0c(int, u16 *, int, int);
extern int func_020996ac(int);
extern void OSi_DoUnlockByWord__main_0203cd2c(int, u16 *, int, int);
extern void func_02015f38(char *, int, int, int, int, int, int);
extern void func_02015de4(char *, u16 *, int, int);

void func_02024580(char *p)
{
    int a;
    int b;
    int c;
    u16 v0, v1, v2, v3, v4, v5, v6, v7;
    u16 v8, v9, v10, v11, v12, v13, v14, v15;
    int r5;
    int r6;
    int r7;
    int flag;
    u16 x;

    if (P32(0x164) == 0) {
        return;
    }
    a = func_020984e8();
    b = func_02099734();
    r6 = *(int *) ((char *) P32(0x100) + 0x830);
    c = func_0209b91c(P32(0x164));
    r7 = func_020644cc(0x64);
    r5 = func_0209b914(P32(0x164));
    switch (func_0209bc40(c)) {
        case 0:
        case 1:
        case 2:
            switch (r5) {
                case 0:
                case 1:
                    if (r7 < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x1f4;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v0, P32(0x1a0));
                        P16(0x19c) = v0;
                    }
                    break;
                case 2:
                case 3:
                    func_0207ddd0(&v1, *(int *) ((char *) P32(0x100) + 0x830));
                    P16(0x19c) = v1;
                    if (P16(0x19c) != 0xfff1) {
                        func_0207de70(*(int *) ((char *) P32(0x100) + 0x830), &P16(0x19c));
                    } else if (func_020644cc(0x64) < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x2bc;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v2, P32(0x1a0));
                        P16(0x19c) = v2;
                    }
                    break;
                default:
                    func_0202d5e4(&v3, a);
                    P16(0x19c) = v3;
                    break;
            }
            if (P16(0x19c) == 0xfff1) {
                func_0202d5e4(&v4, 0);
                P16(0x19c) = v4;
            }
            break;
        case 3:
            switch (r5) {
                case 0:
                case 1:
                    func_0207de14(&v5, r6);
                    P16(0x19c) = v5;
                    if (P16(0x19c) != 0xfff1) {
                        func_0207de70(r6, &P16(0x19c));
                    } else if (r7 < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x1f4;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v6, P32(0x1a0));
                        P16(0x19c) = v6;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                    func_0207ddd0(&v7, r6);
                    P16(0x19c) = v7;
                    if (P16(0x19c) != 0xfff1) {
                        func_0207de70(r6, &P16(0x19c));
                    } else if (func_020644cc(0x64) < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x2bc;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v8, P32(0x1a0));
                        P16(0x19c) = v8;
                    }
                    break;
                default:
                    func_0202d5cc(&v9, a);
                    P16(0x19c) = v9;
                    break;
            }
            if (P16(0x19c) == 0xfff1) {
                func_0202d5cc(&v10, 0);
                P16(0x19c) = v10;
            }
            break;
        case 4:
            switch (r5) {
                case 0:
                case 1:
                    if (r7 < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x1f4;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v11, P32(0x1a0));
                        P16(0x19c) = v11;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                    func_0207ddd0(&v12, r6);
                    P16(0x19c) = v12;
                    if (P16(0x19c) != 0xfff1) {
                        func_0207de70(r6, &P16(0x19c));
                    } else if (func_020644cc(0x64) < 0x1e) {
                        P32(0x1a0) = (func_0205be38() << 2) + 0x2bc;
                        P32(0x1a0) = func_0202b510(P32(0x1a0));
                        func_02027170(&v13, P32(0x1a0));
                        P16(0x19c) = v13;
                    }
                    break;
                default:
                    func_0202d5e4(&v14, a);
                    P16(0x19c) = v14;
                    break;
            }
            if (P16(0x19c) == 0xfff1) {
                func_0202d5e4(&v15, 0);
                P16(0x19c) = v15;
            }
            break;
    }
    flag = 0;
    x = P16(0x19c);
    if (x >= 0x1492 && x <= 0x14fd) {
        flag = 1;
    }
    if (flag != 0) {
        func_02098a24(b, P32(0x1a0), 1);
    } else if (x != 0xfff1) {
        c = func_02098eb8(b);
        if (c != -1) {
            func_02098f0c(b, &P16(0x19c), c, 0);
            OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(a), &P16(0x19c), 0, 1);
        }
    }
    flag = 0;
    x = P16(0x19c);
    if (x >= 0x1492 && x <= 0x14fd) {
        flag = 1;
    }
    if (flag != 0) {
        func_02015f38(p, P32(0x1a0), 1, 4, 1, 0, 0);
    } else if (x != 0xfff1) {
        func_02015de4(p, &P16(0x19c), 1, 7);
    }
}
