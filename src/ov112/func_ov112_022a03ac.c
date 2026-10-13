/* func_ov112_022a03ac @ 0x022a03ac, 0x10c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov095_0229ba44(void *p, int b, int c);
extern int func_ov095_0229bebc(void *p, int b);
extern void func_ov112_0229fd20(void *self);
extern void func_ov112_022a02f4(void *self, int arg);
extern int func_ov112_022a01b0(void *self, int b);
extern void func_ov112_0229ff50(void *self);
extern void func_ov112_022a0144(void *self);
extern void func_ov112_022a00ac(void *self);
extern void func_ov112_022a0068(void *self);
extern void func_ov112_022a0028(void *self);
extern int func_ov112_022a0258(void *self, u16 b);

int func_ov112_022a03ac(void *self, int b)
{
    int result = 1;
    int ret;

    ret = func_ov095_0229ba44((char *) self + 0x384, b, 6);
    if (ret != 0) {
        func_ov112_0229fd20(self);
        return ret;
    }

    if (func_ov095_0229bebc((char *) self + 0x384, b) != 0) {
        switch (b) {
            case 0x100:
                func_ov112_022a02f4(self, result);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov112_022a01b0(self, b) == 0) {
                    func_ov112_0229ff50(self);
                }
                result = 2;
                break;
            case 0x118:
                func_ov112_022a0144(self);
                result = 2;
                break;
            case 0x119:
                func_ov112_022a00ac(self);
                result = 2;
                break;
            case 0x113:
                func_ov112_022a0068(self);
                result = 3;
                break;
            case 0x115:
                func_ov112_022a0028(self);
                result = 3;
                break;
            default:
                result = 2;
                break;
        }
    } else {
        if (func_ov112_022a0258(self, (u16) b) == 0) {
            func_ov112_0229ff50(self);
        }
        if (b == 10) {
            result = 2;
        }
    }

    return result;
}
