/* func_0206ef34 @ 0x0206ef34, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203de78(void);
extern void func_020027f0(int);
extern void func_02001ba4(int);
extern void func_0206fcc8(void);
extern void func_0206ef70(void);
extern void func_0206f35c(void);
extern int data_021c8c9c;

void func_0206ef34(void)
{
    if (func_0203de78() == 0) {
        func_020027f0(1);
        func_020027f0(5);
    }
    func_02001ba4(2);
    data_021c8c9c = 0;
    func_0206fcc8();
    func_0206ef70();
    func_0206f35c();
}
