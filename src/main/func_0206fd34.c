/* func_0206fd34 @ 0x0206fd34, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fd04(void);
// 0x021cfc7c

extern unsigned char data_021cfc7c[];

int func_0206fd34(void)
{
    int result;
    int *ptr;

    if (func_0206fd04() != 0) {
        ptr = (int *) data_021cfc7c;
        result = *ptr;
    } else {
        result = 0;
    }
    return result;
}
