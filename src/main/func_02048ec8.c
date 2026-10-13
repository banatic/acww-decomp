/* func_02048ec8 @ 0x02048ec8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204ed80(void);

int func_02048ec8(void)
{
    int ret = 0;
    int v;
    v = func_0204ed80();
    if (v == 0) {
        goto set;
    }
    if (v != 1) {
        goto done;
    }
set:
    ret = 1;
done:
    return ret;
}
