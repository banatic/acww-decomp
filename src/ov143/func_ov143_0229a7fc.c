/* func_ov143_0229a7fc @ 0x0229a7fc, 0x6c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af94(int);
extern int data_021fbe94;
extern void func_02002c6c(void *p, int a, int b, int c, int d, int e);
extern void func_02002d14(void *p, int a, int b, int c, int d, int e);
extern char data_ov143_0229b220;
extern char data_ov143_0229b234;
extern char data_ov143_0229b24c;

void func_ov143_0229a7fc(int arg0)
{
    int r4;
    func_ov002_0220af94(arg0 + 0x110);
    r4 = data_021fbe94;
    func_02002c6c(&data_ov143_0229b220, r4, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c(&data_ov143_0229b234, r4, 8, 0x140, 0x140, 0x1bf);
    func_02002d14(&data_ov143_0229b24c, r4, 8, 4, 4, 0xd);
}
