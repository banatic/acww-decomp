/* func_ov111_0229f730 @ 0x0229f730, 0x124 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov095_0229ba44(void *p, int param, int six);
extern void func_ov111_0229fd08(void *self);
extern int func_ov095_0229bebc(void *p, int param);
extern int func_ov111_0229fb8c(void *self, int ret);
extern void func_ov111_0229facc(void *self);
extern void func_ov111_0229fa50(void *self);
extern void func_ov111_0229f9d4(void *self);
extern void func_ov111_0229f92c(void *self);
extern void func_ov111_0229f860(void *self);
extern int func_ov111_022a09f8(void *self, int a, int b);
extern int func_ov095_0229af98(void *p, int param);
extern void func_ov111_022a0198(void *self);
extern void func_ov111_0229f0cc(void *self);
extern int func_ov111_0229fc38(void *self, u16 param);
extern void func_ov111_0229f854(void *receiver);

struct UnkStruct_0229f730 {
    char pad_00[0xa2];
    u8 unk_A2;
    char pad_A3[0xac - 0xa3];
    char unk_AC[1];
};

int func_ov111_0229f730(struct UnkStruct_0229f730 *self, int param)
{
    int ret = 1;
    int res = func_ov095_0229ba44(self->unk_AC, param, 6);

    if (res != 0) {
        func_ov111_0229fd08(self);
        return res;
    }

    if (func_ov095_0229bebc(self->unk_AC, param) != 0) {
        switch (param - 0x100) {
            case 0:
                func_ov111_0229fb8c(self, ret);
                break;
            case 3:
                func_ov111_0229facc(self);
                ret = 2;
                break;
            case 4:
                func_ov111_0229fa50(self);
                ret = 2;
                break;
            case 5:
                func_ov111_0229f9d4(self);
                ret = 2;
                break;
            case 24:
                func_ov111_0229f92c(self);
                ret = 2;
                break;
            case 25:
                func_ov111_0229f860(self);
                ret = 2;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                func_ov111_022a09f8(self, param - 0x10a, 0);
                ret = 2;
                break;
            case 27:
            case 28:
            case 29:
            case 30:
                if (self->unk_A2 != 0) {
                    return 0;
                }
                func_ov095_0229af98(self->unk_AC, param);
                func_ov111_022a0198(self);
                func_ov111_0229f0cc(self);
                ret = 3;
                break;
            case 6:
                break;
            default:
                return 0;
        }
    } else {
        if (func_ov111_0229fc38(self, (u16) param) == 0) {
            func_ov111_0229f854(self);
        }
    }

    return ret;
}
