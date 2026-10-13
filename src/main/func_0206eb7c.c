/* func_0206eb7c @ 0x0206eb7c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc20;
extern int func_0206f278(void);
extern void func_02001ba4(int a);
extern void func_020027f0(int a);
extern void func_0206fcc8(void);

int func_0206eb7c(void)
{
    if (func_0206f278() == 0) {
        data_021cfc20 = 0xC;
        func_02001ba4(2);
        func_020027f0(1);
        func_0206fcc8();
    }
    return 1;
}
