/* func_0206eda0 @ 0x0206eda0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206efd4(int);
extern void func_02001ba4(int);
extern void func_02001afc(int);
extern void func_02002708(int);
extern void func_0206fcc8(void);
extern void func_0206feb0(void);
extern void func_020027f0(int);
extern void func_020ba540(int);
extern int data_021c8c9c;
extern unsigned short data_021cfc20;
extern unsigned char data_020e54a8;

int func_0206eda0(void)
{
    int flag;

    if (func_0206efd4(5) != 0) {
        func_02001ba4(2);
        func_02001afc(0xf);
        func_02002708(5);
        data_021c8c9c = 1;
        func_0206fcc8();
        func_0206feb0();
        func_020027f0(1);
        data_021cfc20 = 5;
        flag = data_020e54a8 ? 0 : 1;
        if (flag != 0) {
            func_020ba540(1);
        }
    }

    return 1;
}
