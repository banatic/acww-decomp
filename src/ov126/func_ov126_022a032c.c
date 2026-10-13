/* func_ov126_022a032c @ 0x022a032c, 0xb0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_022a0904(unsigned char *p, int mode);
extern int func_ov095_0229bb9c(unsigned char *p, int val);
extern int func_ov095_0229bb98(unsigned char *p, int val);
extern int func_ov095_0229bb94(unsigned char *p, int val);
extern int func_ov095_0229bba0(unsigned char *p1, unsigned char *p2, int val, int a4, int a5, int a6);
extern void func_ov126_022a0168(unsigned char *p);
extern void func_ov126_022a08c4(unsigned char *p);

int func_ov126_022a032c(unsigned char *self, int mode)
{
    int result;

    result = func_ov126_022a0904(self, mode);
    if (!result) {
        return 0;
    }

    switch (mode) {
        case 0x103:
            result = func_ov095_0229bb9c(self + 0x19c, result);
            break;
        case 0x104:
            result = func_ov095_0229bb98(self + 0x19c, result);
            break;
        case 0x105:
            result = func_ov095_0229bb94(self + 0x19c, result);
            break;
    }

    if (!result) {
        return 0;
    }

    if (!func_ov095_0229bba0(self + 0x19c, self + 0x4248, result, self[0xa8], self[0xa6], 0x2710)) {
        return 0;
    }

    func_ov126_022a0168(self);
    func_ov126_022a08c4(self);
    return 1;
}
