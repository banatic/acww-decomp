/* func_ov123_0229b0dc @ 0x0229b0dc, 0x84 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229b174(void *param);
extern void func_020708e4(void *a, unsigned short *b, int c);
extern void func_02070a98(void *a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(void *a, int b, int c);

void func_ov123_0229b0dc(void *self, int n)
{
    unsigned short buf[4];

    ((unsigned char *) self)[0xa1] = n;
    func_ov123_0229b174(self);
    if (n < 9U) {
        buf[0] = 0x3000;
    } else {
        buf[0] = 0xff11;
    }
    buf[1] = 0xff10 + (n + 1) % 10;
    buf[2] = 0;
    func_020708e4((char *) self + 0xb8, buf, 5);
    func_02070a98((char *) self + 0xb8, 8, 0x128, 2, 6, 0, 1);
    func_02070a04((char *) self + 0xb8, 0, 0);
}
