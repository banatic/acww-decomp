/* func_ov112_022a01b0 @ 0x022a01b0, 0xa8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov112_0229f6b8(char *p, int mode);
extern void *func_ov095_0229bb9c(char *p, void *q);
extern void *func_ov095_0229bb98(char *p, void *q);
extern void *func_ov095_0229bb94(char *p, void *q);
extern int func_ov095_0229bba0(char *a, char *b, void *c, int d, int e, int f);
extern void func_ov112_0229fd20(char *p);
extern void func_ov112_0229f668(char *p);

int func_ov112_022a01b0(char *p, int mode)
{
    void *res;

    res = func_ov112_0229f6b8(p, mode);
    if (res == 0) {
        return 0;
    }

    switch (mode) {
        case 0x103:
            res = func_ov095_0229bb9c(p + 0x384, res);
            break;
        case 0x104:
            res = func_ov095_0229bb98(p + 0x384, res);
            break;
        case 0x105:
            res = func_ov095_0229bb94(p + 0x384, res);
            break;
        default:
            break;
    }

    if (res == 0) {
        return 0;
    }

    if (!func_ov095_0229bba0(p + 0x384, p + 0xc4, res, *(unsigned char *) (p + 0xbd), 0x60, 0x2710)) {
        return 0;
    }

    func_ov112_0229fd20(p);
    func_ov112_0229f668(p);
    return 1;
}
