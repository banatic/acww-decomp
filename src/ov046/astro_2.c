/* astro_2: 2 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02260618 @ 0x02260618, 0x2c bytes, Thumb
 * func_ov046_022605f8 @ 0x022605f8, 0x20 bytes, Thumb
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);

int func_ov046_02260618(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov046_022605f8(int param)
{
    if (func_02014868((void *) (param + 0x618)) != 0) {
        return 0;
    } else {
        return 1;
    }
}
