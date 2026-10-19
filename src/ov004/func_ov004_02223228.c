/* func_ov004_02223228 @ 0x02223228, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov004_02222b3c(void *self);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_ov004_0222fd94(void);
extern int func_020147e0(void *p, int a, int b);
extern int func_02016104(void *p);
extern int func_0201c314(void *self, int n);
extern int func_020147fc(void *p, int a, int b, int c);
extern int data_021fbee8;
extern int data_020c814c;

int func_ov004_02223228(char *self)
{
    int n, r;

    if (func_ov004_02222b3c(self) >= 6) {
        func_0201ad18(self + 0x3b0, 1, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
    }
    func_ov004_0222fd94();
    if (func_ov004_02222b3c(self) < 6) {
        func_020147e0(self + 0x618, 1, 0);
    } else {
        n = func_02016104(self + 0x658);
        r = 0;
        if (n != 0) {
            r = func_0201c314(self, n);
        }
        func_020147fc(self + 0x618, 0, r, 0);
    }
    return 1;
}
