/* func_020ec548 @ 0x020ec548, 0x64 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void WXC_End(void);
extern void func_020edb14(void);
extern int func_020edacc(int);
extern int data_021fbf48;
extern int data_021fbf28;
extern unsigned char data_021fbef8;

int func_020ec548(void)
{
    WXC_End();
    if (data_021fbf48 == 0) {
        do {
            func_020edb14();
        } while (data_021fbf48 == 0);
    }
    func_020edacc(data_021fbf28);
    data_021fbf28 = 0;
    data_021fbef8 = 6;
    return 1;
}
