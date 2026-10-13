/* func_020a7ee4 @ 0x020a7ee4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_020a7dcc(void);

int func_020a7ee4(void)
{
    int r = 0;
    if (func_020a7dcc() != 0) {
        goto done;
    }
    if ((data_021fbe40 & 2) == 0) {
        goto done;
    }
    r = 1;
done:
    return r;
}
