/* item_group_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204be88 @ 0x0204be88, 0x28 bytes, Thumb
 * func_0204be60 @ 0x0204be60, 0x28 bytes, Thumb
 */

extern int func_0204b42c(int arg);

int func_0204be88(unsigned short *p)
{
    int result = 0;

    if (*p >= 0x1408 && *p <= 0x1428) {
        result = 1;
    }

    if (result) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204be60(int arg)
{
    if (func_0204be88((unsigned short *) arg)) {
        return func_0204b42c(arg) - 0x1408;
    } else {
        return -1;
    }
}
