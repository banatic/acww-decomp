/* func_0206fbf8 @ 0x0206fbf8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070094(int);
extern int func_0207004c(int);
extern unsigned char data_021cfc5c;

int func_0206fbf8(int a)
{
    if (func_02070094(a) == 0) {
        return 0;
    } else {
        data_021cfc5c = a;
        return func_0207004c(9);
    }
}
