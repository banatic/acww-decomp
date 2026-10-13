/* func_ov004_02224844 @ 0x02224844, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *p);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_0201c314(void *self, int n);
extern void func_020147fc(void *p, int a, int b, int c);
extern int data_021fbee8;
extern int data_020c814c;

int func_ov004_02224844(char *self)
{
    int n;
    int r;

    n = gt2GetIncomingBufferSize(self + 0x658);
    r = 0;
    func_0201ad18(self + 0x3b0, 1, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
    if (n != 0) {
        r = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, r, 0);
    return 1;
}
