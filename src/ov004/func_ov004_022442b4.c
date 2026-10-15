/* func_ov004_022442b4 @ 0x022442b4, 0x23c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define B(o) (*(u8 *) (self + (o)))
#define C(o) (*(signed char *) (self + (o)))
#define S(o) (*(short *) (self + (o)))
#define W(o) (*(int *) (self + (o)))
#define V(o) ((Vec *) (self + (o)))
extern u8 data_ov004_02259a24;
extern void func_ov004_02244f20(char *);
extern void func_ov004_02244774(char *, int, int);
extern int func_ov004_02244c20(char *);
extern int func_ov004_02243f0c(char *);
extern int func_0200322c(Vec *, Vec *);
extern int func_020644cc(int);
extern void func_ov004_02244094(char *);
extern void func_ov004_02243fec(char *);
extern void func_ov004_02244224(char *);
extern void func_ov004_0224412c(char *);
extern void func_ov004_02244f48(Vec *, Vec *, int, int);
extern void func_020550e4(void *, int);
extern int func_ov004_02244904(char *);
void func_ov004_022442b4(char *self)
{
    u8 state = (u8) S(0x172);
    if (state != 25) {
        func_ov004_02244f20(self);
    }
    switch (state) {
        case 19:
            func_ov004_02244774(self, 0, 5);
            break;
        case 3:
        case 15:
            func_ov004_02244774(self, 0, 4);
            break;
        case 4:
            if (func_ov004_02244c20(self) && func_ov004_02243f0c(self) < 0x5000) {
                S(0xac) = func_0200322c(V(0x2c8), V(0x40));
                S(0x172) = 14;
                if (C(0x196) != 23) {
                    S(0x168) = (func_020644cc(5) + 2) * 10;
                }
            } else {
                func_ov004_02244094(self);
            }
            func_ov004_02243fec(self);
            break;
        case 5:
            func_ov004_02244224(self);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            func_ov004_0224412c(self);
            break;
        case 7: {
            int heading;
            S(0x172) = 15;
            S(0x9c) = 0;
            W(0x174) = 160;
            B(0x9a) = 0;
            B(0xae) = 0;
            heading = S(0xac);
            func_ov004_02244f48(V(0x34), V(0x2c8), heading, (B(0xa4) + func_020644cc(3)) << 12);
            S(0xac) = func_0200322c(V(0x2c8), V(0x34));
            break;
        }
        default:
            if (B(0x20)) {
                S(0x172) = 7;
            } else if (B(0xae)) {
                if (data_ov004_02259a24 % 20 == 0) {
                    u8 choice = func_020644cc(100);
                    if ((((u32) W(0x154) << 4) >> 16) == 0 && choice > 92) {
                        func_020550e4(self + 0xb0, 2);
                    } else if (choice > 50) {
                        func_020550e4(self + 0xb0, 0);
                    }
                } else if ((((u32) W(0x154) << 4) >> 16) != 0) {
                    func_ov004_02244f20(self);
                }
                func_ov004_02244904(self);
                if (B(0x22) && func_ov004_02244c20(self)) {
                    B(0xae) = 0;
                    S(0x172) = 11;
                    W(0x174) = 160;
                    if (C(0x196) == 23) {
                        S(0x168) = 0;
                    } else {
                        S(0x168) = (func_020644cc(5) + 2) * 10;
                    }
                }
            } else {
                S(0x172) = 11;
                if (C(0x196) == 23) {
                    S(0x168) = 0;
                } else {
                    S(0x168) = (func_020644cc(5) + 2) * 10;
                }
            }
            break;
    }
    B(0x20) = 0;
}
