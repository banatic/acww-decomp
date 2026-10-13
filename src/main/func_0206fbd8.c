/* func_0206fbd8 @ 0x0206fbd8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int a);
extern char data_021cfc48;

int func_0206fbd8(int a, int b)
{
    if (func_0206fbf8(a)) {
        data_021cfc48 = b;
        return 1;
    }
    return 0;
}
