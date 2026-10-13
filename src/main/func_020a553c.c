/* func_020a553c @ 0x020a553c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209dad0(void);
extern void func_020046c4(void);
extern void func_020ee4d8(int, int);
extern unsigned char data_020e3c7c;
extern unsigned char data_021dc6c4;
extern int data_021f42f4;

void func_020a553c(int arg0, int arg1)
{
    if (arg1 == 2) {
        data_020e3c7c = 0;
        if (data_021dc6c4 != 0) {
            func_0209dad0();
        }
        data_021f42f4 = 0;
        func_020046c4();
    }
    func_020ee4d8(arg0, arg1);
}
