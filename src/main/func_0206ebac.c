/* func_0206ebac @ 0x0206ebac, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001bb4(int);
extern void func_02001ba4(int);
extern void func_02001d88(int);
extern void func_02001d1c(int);
extern void func_02001b34(int);
extern void func_0206f28c(void);
extern int func_0203aeac(void);
extern unsigned short data_021cfc20;

int func_0206ebac(void)
{
    func_02001bb4(2);
    func_02001ba4(1);
    func_02001d88(0x1f);
    func_02001d1c(0x1b);
    func_02001b34(0xa);
    func_0206f28c();
    if (func_0203aeac() != 0) {
        data_021cfc20 = 0xb;
    }
    return 1;
}
