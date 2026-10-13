/* func_0209fe1c @ 0x0209fe1c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073100(void);
extern int func_020eb070(void);
extern unsigned char data_021f3c14;

int func_0209fe1c(void)
{
    func_02073100();
    if (func_020eb070()) {
        data_021f3c14 = 1;
        return 1;
    }
    return 0;
}
