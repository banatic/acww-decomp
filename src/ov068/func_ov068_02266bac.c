/* func_ov068_02266bac @ 0x02266bac, 0x36 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222f458(int x, unsigned char y);
extern int func_020ea990(int x, int y);

int func_ov068_02266bac(int a0, int a1, int a2, int a3, int a4)
{
    int res = func_ov003_0222f458(a1, (unsigned char) a2);
    if (res == -1) {
        goto fail;
    }
    if (func_020ea990(a3, a1) >= a4) {
        goto fail;
    }
    return res;
fail:
    return -1;
}
