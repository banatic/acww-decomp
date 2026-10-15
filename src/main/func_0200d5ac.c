/* func_0200d5ac @ 0x0200d5ac, 0x354 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define U32(p, o) (*(u32 *) ((char *) (p) + (o)))
#define U8(p, o) (*(u8 *) ((char *) (p) + (o)))
#define AT(p, o) ((void *) ((char *) (p) + (o)))

extern u8 data_020e54a8;
extern void *data_020ccf94;
extern int data_021c526c;

extern int func_02008258(void *, int);
extern int func_02073908(void *, int);
extern int func_020310d0(void *, int, int);
extern int func_020b6660(void);
extern void func_0201a74c(void *);
extern int func_020b67ac(void);
extern void func_0200451c(void *);
extern unsigned int *func_0200f27c(void *, int);
extern u8 func_020b65c4(void);
extern int func_020b5d5c(void);
extern int func_0200edb0(void *);
extern void func_020b8dc0(void);
extern u8 func_020ec1e8(void);
extern int func_020eae40(void);
extern int func_0200d554(void *, int, int);
extern int func_ov004_0222bdf0(void *, int, int, int);
extern int func_0200f290(void *, int);
extern int func_ov003_02218388(void *, int, int);
extern int func_020b2998(void);
extern void func_02035ab4(void *);
extern int func_ov003_0220f244(void *, int, int, int);
extern int func_ov003_02217ddc(void *, int, int);
extern void *func_ov003_0220efc8(void *, int, int);
extern int func_ov004_022275a0(void *, int, int);
extern int func_ov004_02227468(void *, int, int);
extern int func_ov004_02228dfc(void *, int, int, int);
extern int func_0200c3b0(void *, int, int, int);
extern int func_ov004_02226c2c(void *, void *, int, int);
extern int func_ov004_02226454(void *, void *, int, int);
extern int func_0200d4e8(void *, int, int, int);
extern void func_0200f394(void *);
extern int func_0203e110(void);

void func_0200d5ac(void *p1, int *p2)
{
    int mode;
    int flag;
    void *g;
    unsigned int t;
    int x;
    u8 y;

    if (*p2 == 0) {
        return;
    }
    U32(p1, 0x7fc) = func_02008258(p1, U32(p1, 0x7f0));
    mode = U32(p1, 0x7d4);
    t = (data_020e54a8 == 0) ? 1 : 0;
    if (t != 0 && mode != 1 && func_02073908(data_020ccf94, U32(p1, 0x800)) != 0 &&
        func_020310d0(AT(p1, 0x5c), 0, 0x19) >= 0x800) {
        mode = 0x6d;
    }
    t = (data_020e54a8 == 0) ? 1 : 0;
    if (t == 0 || func_020b6660() != 0) {
        func_0201a74c(AT(p1, 0x90c));
        if (func_02073908(data_020ccf94, U32(p1, 0x800)) != 0 || (func_020b67ac() != 0 && mode == 8)) {
            func_0200451c(AT(p1, 0x83c));
            U32(p1, 0x924) = (u32) AT(p1, 0x83c);
            U8(p1, 0x932) = 1;
            func_0200f27c(p1, 0x19);
        } else {
            func_0200451c(AT(p1, 0x880));
            U32(p1, 0x924) = (u32) AT(p1, 0x880);
        }
        func_0200f27c(p1, 0xa);
    }
    g = data_020ccf94;
    if (func_02073908(g, U32(p1, 0x800)) != 0) {
        x = func_020b65c4();
        if (x != 0xc && x != 0x2f) {
            if (func_020b5d5c() == 0 || func_0200edb0(p1) == 1) {
                func_020b8dc0();
                func_0200f27c(p1, 0x1b);
            } else if (U32(g, 0x64) == 0) {
                y = (u8) (func_020ec1e8() + 0xfd);
                if (y <= 1) {
                    func_020eae40();
                }
            }
        }
    }
    flag = 0;
    switch (mode) {
        case 1:
            func_0200d554(p1, 9, ~flag);
            break;
        case 8:
            if (func_020b67ac() != 0) {
                func_ov004_0222bdf0(p1, 0, 6, -1);
            } else {
                if (func_0200f290(p1, 0x1b) == 0) {
                    flag = 1;
                }
                func_ov004_0222bdf0(p1, 1, 6, -1);
            }
            break;
        case 0x3b:
            func_ov003_02218388(p1, 6, ~flag);
            break;
        case 0x3c:
            if (func_02073908(g, U32(p1, 0x800)) != 0 && func_020b2998() == 0) {
                func_02035ab4(AT(data_021c526c, 0x2e4));
                func_ov003_0220f244(p1, 0, 7, -1);
                mode = 0x6d;
            } else {
                func_ov003_02217ddc(p1, 1, -1);
            }
            break;
        case 0x6d:
            func_02035ab4(AT(data_021c526c, 0x2e4));
            func_ov003_0220f244(p1, 1, 7, ~flag);
            break;
        case 0x6e:
            func_ov003_0220efc8(p1, 7, ~flag);
            break;
        case 0x43:
            func_ov004_022275a0(p1, 6, ~flag);
            break;
        case 0x44:
            func_ov004_02227468(p1, 6, ~flag);
            break;
        case 0x28:
            if (func_0200f290(p1, 0x1b) == 0) {
                flag = 1;
            }
            func_ov004_02228dfc(p1, 0, 6, -1);
            break;
        case 0x10:
            U32(p1, 0x7f8) = 1;
            func_0200c3b0(p1, 3, 5, ~flag);
            break;
        case 0x8b:
            func_ov004_02226c2c(p1, AT(p1, 0x5c), 6, ~flag);
            func_0200f27c(p1, 5);
            break;
        case 0x8e:
            func_ov004_02226454(p1, AT(p1, 0x5c), 6, ~flag);
            func_0200f27c(p1, 5);
            break;
        default:
            mode = 2;
            func_0200d4e8(p1, 0, 1, -1);
            if (func_0200f290(p1, 0x1b) == 0) {
                flag = 1;
            }
            func_0200f394(p1);
            break;
    }
    U32(p1, 8) = ((u32) (mode << 0x16) & 0x3fc00000) | (U32(p1, 8) & 0xc03fffff);
    if (flag != 0) {
        if (func_02073908(g, U32(p1, 0x800)) != 0) {
            func_0203e110();
        }
    }
}
