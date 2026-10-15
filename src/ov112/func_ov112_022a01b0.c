/* func_ov112_022a01b0 @ 0x022a01b0, 0xa8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov112_0229f6b8(char *p);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern int func_ov095_0229bba0(char *a, char *b, void *c, int d);
extern void func_ov112_0229fd20(char *p);
extern void func_ov112_0229f668(char *p);

int func_ov112_022a01b0(char *p, int mode)
{
    void *res;
    volatile int limits[2];

    res = func_ov112_0229f6b8(p);
    if (res == 0) {
        return 0;
    }

    switch (mode) {
        case 0x103:
            res = (void *) func_ov095_0229bb9c(p + 0x384, (int) res);
            break;
        case 0x104:
            res = (void *) func_ov095_0229bb98(p + 0x384, (int) res);
            break;
        case 0x105:
            res = (void *) func_ov095_0229bb94(p + 0x384, (int) res);
            break;
        default:
            break;
    }

    if (res == 0) {
        return 0;
    }

    limits[0] = 0x60;
    limits[1] = 0x2710;
    if (!func_ov095_0229bba0(p + 0x384, p + 0xc4, res, *(unsigned char *) (p + 0xbd))) {
        return 0;
    }

    func_ov112_0229fd20(p);
    func_ov112_0229f668(p);
    return 1;
}
