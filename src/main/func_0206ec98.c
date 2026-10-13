/* func_0206ec98 @ 0x0206ec98, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int CARD_IsEnabled(void);
extern void func_0203ac2c(void);
extern void func_0203de6c(int);
extern void func_020ba540(int);
extern void func_02001b34(int);
extern void func_0206eb0c(int);

extern unsigned char data_020e54a8;
extern unsigned short data_021cfc20;
extern unsigned int data_021cfc28;
extern unsigned int data_021cfc24;

int func_0206ec98(void)
{
    unsigned int flag2;

    if (CARD_IsEnabled()) {
        func_0203ac2c();
    }
    flag2 = (data_020e54a8 == 0) ? 1 : 0;
    if (flag2 > 0) {
        func_0203de6c(0);
        func_020ba540(1);
        func_02001b34(8);
    }
    data_021cfc20 = 9;
    data_021cfc28 = 0x1000;
    data_021cfc24 = 0x200;
    func_0206eb0c(1);
    return 1;
}
