/* func_0206f6b0 @ 0x0206f6b0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);
extern unsigned short data_021cfc70;

int func_0206f6b0(unsigned short param)
{
    if (func_0206fbf8(42)) {
        data_021cfc70 = param;
        return 1;
    }
    return 0;
}
