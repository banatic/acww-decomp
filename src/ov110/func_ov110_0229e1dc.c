/* func_ov110_0229e1dc @ 0x0229e1dc, 0xd4 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// func_02002c6c and func_02002d14 take six arguments; the 4th and 5th are the same constant.

extern void *data_021fbe94;
extern u8 data_ov110_0229ed18[];
extern u8 data_ov110_0229ed3c[];
extern u8 data_ov110_0229ed5c[];
extern u8 data_ov110_0229ed74[];
extern u8 data_ov110_0229ed8c[];
extern u8 data_ov110_0229eda4[];
extern u8 data_ov110_0229edbc[];
extern u8 data_ov110_0229edd4[];
extern u8 data_ov110_0229edec[];
extern u8 data_ov110_0229ee04[];

extern int func_02002ca4(u8 *, void *, int);
extern int func_02002c6c(u8 *, void *, int, int, int, int);
extern int func_02002d14(u8 *, void *, int, int, int, int);
extern int func_0206fca4(void);
extern void func_ov110_0229c4f8(void *, int);

void func_ov110_0229e1dc(void *o)
{
    void *p;
    u8 *a;
    u8 *b;
    int t;

    p = data_021fbe94;
    func_02002ca4(data_ov110_0229ed18, p, 4);
    func_02002c6c(data_ov110_0229ed3c, p, 4, 0x1b9, 0x1b9, 0x238);
    t = func_0206fca4();
    a = 0;
    b = a;
    switch (t) {
        case 0x1d:
            a = data_ov110_0229ed5c;
            b = data_ov110_0229ed74;
            break;
        case 0x1e:
            a = data_ov110_0229ed8c;
            b = data_ov110_0229eda4;
            break;
        case 0x1f:
            a = data_ov110_0229edbc;
            b = data_ov110_0229edd4;
            break;
        case 0x20:
            a = data_ov110_0229edec;
            b = data_ov110_0229ee04;
            break;
    }
    if (a != 0) {
        func_02002d14(a, p, 4, 3, 3, 5);
    }
    if (b != 0) {
        func_02002c6c(b, p, 4, 0x208, 0x208, 0x238);
    }
    func_ov110_0229c4f8(o, 0);
}
