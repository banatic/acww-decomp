/* func_0206f6d4 @ 0x0206f6d4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);

extern unsigned short data_021cfc70;

int func_0206f6d4(int arg0)
{
    int result;
    int r4 = arg0;
    if (func_0206fbf8(0x29) != 0) {
        data_021cfc70 = (unsigned short) r4;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
