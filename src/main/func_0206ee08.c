/* func_0206ee08 @ 0x0206ee08, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203b130(void);
extern void func_0206fcf8(void);
extern void func_0206fd54(int);
extern unsigned int data_021cfc28;
extern unsigned int data_021cfc24;
extern unsigned short data_021cfc20;

int func_0206ee08(void)
{
    if (func_0203b130()) {
        func_0206fcf8();
        func_0206fd54(0);
        data_021cfc28 = 0x1000;
        data_021cfc24 = 0x200;
        data_021cfc20 = 4;
    }
    return 1;
}
