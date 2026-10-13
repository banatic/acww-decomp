/* func_0206ee7c @ 0x0206ee7c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_021cfc20;
extern int func_0206efd4(int);
extern void func_02002708(int);
extern void func_02001bb4(int);
extern void func_02001d88(int);
extern void func_02001d1c(int);
extern void func_0206f2f0(void);
extern int func_0206ee4c(void);

int func_0206ee7c(void)
{
    if (func_0206efd4(1)) {
        data_021cfc20 = 2;
        func_02002708(1);
        func_02001bb4(2);
        func_02001d88(0x1f);
        func_02001d1c(0x1b);
        func_0206f2f0();
        return func_0206ee4c();
    } else {
        return 1;
    }
}
