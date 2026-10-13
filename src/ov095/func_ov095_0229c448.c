/* func_ov095_0229c448 @ 0x0229c448, 0x74 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229c52c(void *p, int x);
extern int func_ov095_0229c510(void *p, int x);
extern int func_ov095_0229c4f4(void *p, int x);
extern int func_ov095_0229c4d8(void *p, int x);
extern int func_ov095_0229c4bc(void *p, int x);

int func_ov095_0229c448(void *p, int x, unsigned int y)
{
    unsigned int v = y;
    int ret, result;

    if (v >= 9) {
        v = ((unsigned char *) p)[0x1b];
    }
    ret = func_ov095_0229c52c(p, x);
    if (ret >= 0) {
        return ret;
    }
    switch (v) {
        case 2:
            result = func_ov095_0229c510(p, x);
            break;
        case 3:
            result = func_ov095_0229c4f4(p, x);
            break;
        case 6:
            result = func_ov095_0229c4d8(p, x);
            break;
        case 8:
            result = func_ov095_0229c4bc(p, x);
            break;
        default:
            result = 0x3000;
            break;
    }
    return result;
}
