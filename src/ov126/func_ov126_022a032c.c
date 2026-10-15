/* func_ov126_022a032c @ 0x022a032c, 0xb0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_022a0904(unsigned char *p);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern int func_ov095_0229bba0(unsigned char *p1, unsigned char *p2, int val, int a4);
extern void func_ov126_022a0168(unsigned char *p);
extern void func_ov126_022a08c4(unsigned char *p);

int func_ov126_022a032c(unsigned char *self, int mode)
{
    volatile int argument_values[2];
    int result;

    result = func_ov126_022a0904(self);
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

    if (!(argument_values[0] = (int) (self[0xa6]), argument_values[1] = (int) (0x2710),
          func_ov095_0229bba0(self + 0x19c, self + 0x4248, result, self[0xa8]))) {
        return 0;
    }

    func_ov126_022a0168(self);
    func_ov126_022a08c4(self);
    return 1;
}
