/* func_0206f728 @ 0x0206f728, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);

extern volatile unsigned short data_021cfc70;

int func_0206f728(int param)
{
    if (func_0206fbf8(0x2b)) {
        data_021cfc70 = (unsigned short) param;
        return 1;
    }
    return 0;
}
