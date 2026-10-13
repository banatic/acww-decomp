/* func_0206de88 @ 0x0206de88, 0x92 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051c14(const unsigned short *src, int min, int mode, int *out, int flag);

int func_0206de88(const unsigned short *src, int *out, int *count, int total, int min_init, int mode, int lim)
{
    int acc, i, min, tmp, ret;

    acc = 0;
    min = min_init;
    *count = 0;
    i = acc;

    while (i < lim) {
        if (min > total - acc) {
            min = total - acc;
        }
        ret = func_02051c14(src + acc, min, mode, &tmp, 1);
        out[i] = acc;
        acc += tmp;
        if (ret != 0) {
            if (ret == 3 && i == lim - 1) {
                out[i + 1] = acc;
                return 0;
            }
            (*count)++;
        }
        i++;
    }

    out[i] = acc;
    if (acc == total) {
        goto ret1;
    }
    if (src[acc] != 0) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}
