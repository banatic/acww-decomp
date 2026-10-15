/* func_ov004_022247b4 @ 0x022247b4, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern short *func_0209d358(int a, int b);
extern int func_020960f8(int a, int b);
extern int func_ov004_0222c070(int k);
extern void func_0208b514(void);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_0203e020(void *self);
extern void func_ov004_022249b4(void *self, int a);
extern int data_021fbee8;
extern int data_020c814c;

int func_ov004_022247b4(char *self)
{
    if (func_02014868(self + 0x618) == 0) {
        if (func_02073d90(data_020ccf94) == 0) {
            if (*func_0209d358(0, 0x4a) == 0) {
                if (func_020960f8(0x28, 4) != 0) {
                    func_ov004_0222c070(2);
                }
                func_0208b514();
            }
        }
        func_0201ad18(self + 0x3b0, 0, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
        func_0203e020(self);
        func_ov004_022249b4(self, 2);
    }
    return 1;
}
