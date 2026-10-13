/* func_0206f6f8 @ 0x0206f6f8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);
extern int data_021cfc80;   // 0x021cfc80
extern short data_021cfc70; // 0x021cfc70

int func_0206f6f8(int a, int b)
{
    if (func_0206fbf8(0x2c) != 0) {
        data_021cfc80 = b;
        data_021cfc70 = a;
        return 1;
    } else {
        return 0;
    }
}
