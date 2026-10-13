/* func_ov009_02264d30 @ 0x02264d30, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264884(void);

int func_ov009_02264d30(void)
{
    int r0;
    r0 = func_ov009_02264884();
    if (r0 != 0) {
        r0 = *(int *) (r0 + 0xc);
    } else {
        r0 = 0;
    }
    return r0;
}
