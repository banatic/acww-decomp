/* func_ov004_02211c84 @ 0x02211c84, 0x250 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define B(o) (*(u8 *) (self + (o)))
#define H(o) (*(u16 *) (self + (o)))
#define W(o) (*(u32 *) (self + (o)))
extern int func_ov004_0220fde0(char *);
extern u16 func_ov004_0223a760(int);
extern u16 data_ov004_0224fd38;
extern void func_ov004_0223cf54(void *, int, void *);
extern int func_ov004_0220ffbc(char *);
extern void func_ov004_022101e4(char *, int, int, int, int);
extern int func_02056f28(void *, int);
extern void *func_ov004_0220e220(void *);
extern int func_ov004_0220d9ec(void *, int);
int func_ov004_02211c84(char *self)
{
    int kind = func_ov004_0223a760(func_ov004_0220fde0(self));
    int active;
    if ((u16) (kind + 0xfc07) <= 3) {
        switch (B(0x849)) {
            case 0:
                if (H(0x846)) {
                    H(0x846)--;
                }
                if (H(0x846) == 0) {
                    B(0x849) = 1;
                    B(0x848) = 0;
                    B(0x84a) = 0;
                    H(0x84c) = 0;
                    if (kind != data_ov004_0224fd38) {
                        func_ov004_0223cf54(self + 0x798, kind, self + 0x7b8);
                    }
                }
                break;
            case 1:
                H(0x84c)++;
                active = func_ov004_0220ffbc(self);
                if (B(0x84a) && active) {
                    B(0x84a) = 0;
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                    B(0x848)++;
                    if (B(0x848) >= H(0x844)) {
                        B(0x849) = 0;
                        if (kind == 0x3fc) {
                            H(0x846) = 60;
                        } else {
                            H(0x846) = 200;
                        }
                    }
                }
                B(0x84a) = active;
                break;
        }
    } else {
        switch (B(0x849)) {
            case 0:
                if (H(0x846)) {
                    H(0x846)--;
                }
                if (H(0x846) == 0) {
                    B(0x849) = 1;
                    B(0x848) = 0;
                    B(0x84a) = 0;
                    if (kind != data_ov004_0224fd38) {
                        func_ov004_0223cf54(self + 0x798, kind, self + 0x7b8);
                    }
                }
                break;
            case 1:
            case 2:
            case 3:
                if (kind == 0x3ff && func_02056f28(self + 0x5d4, 20)) {
                    if (kind != data_ov004_0224fd38) {
                        func_ov004_0223cf54(self + 0x798, kind, self + 0x7b8);
                    }
                }
                active = func_ov004_0220ffbc(self);
                if (B(0x84a) && active) {
                    B(0x84a) = 0;
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                    B(0x848)++;
                    if (B(0x848) >= H(0x844)) {
                        B(0x849) = (B(0x849) + 1) & 3;
                        B(0x848) = 0;
                        if (B(0x849)) {
                            if (kind != data_ov004_0224fd38) {
                                func_ov004_0223cf54(self + 0x798, kind, self + 0x7b8);
                            }
                        } else {
                            if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), 0)) {
                                H(0x846) = H(0x844) * ((W(0x828) << 4) >> 16);
                            } else {
                                H(0x846) = H(0x844) * ((W(0x5d8) << 4) >> 16);
                            }
                        }
                    }
                }
                B(0x84a) = active;
                break;
        }
    }
    return 1;
}
