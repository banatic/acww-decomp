/* func_020a7fac @ 0x020a7fac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dcc(void);
extern unsigned short data_021fbe40[2];

int func_020a7fac(void)
{
    int result = 0;

    if (func_020a7dcc() != 0) {
        goto out;
    }
    if ((data_021fbe40[1] & 2) == 0) {
        goto out;
    }
    result = 1;

out:
    return result;
}
