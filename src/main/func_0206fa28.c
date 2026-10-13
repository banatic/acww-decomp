/* func_0206fa28 @ 0x0206fa28, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);
extern unsigned char data_021cfc58;
extern unsigned short data_021cfc64;

int func_0206fa28(unsigned short a, unsigned char b)
{
    if (func_0206fbf8(0x21)) {
        data_021cfc58 = b;
        data_021cfc64 = a;
        return 1;
    } else {
        return 0;
    }
}
