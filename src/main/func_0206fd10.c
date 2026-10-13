/* func_0206fd10 @ 0x0206fd10, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fd04(void);
extern int data_021cfc7c;

int func_0206fd10(void)
{
    if (func_0206fd04() != 0) {
        return data_021cfc7c;
    } else {
        return 0x1000;
    }
}
