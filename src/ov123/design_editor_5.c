/* design_editor_5: 6 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229b204 @ 0x0229b204, 0x24 bytes, Thumb
 * func_ov123_0229b1d4 @ 0x0229b1d4, 0x30 bytes, Thumb
 * func_ov123_0229b1a0 @ 0x0229b1a0, 0x34 bytes, Thumb
 * func_ov123_0229b174 @ 0x0229b174, 0x2c bytes, Thumb
 * func_ov123_0229b160 @ 0x0229b160, 0x12 bytes, Thumb
 * func_ov123_0229b0dc @ 0x0229b0dc, 0x84 bytes, Thumb
 */

extern int func_02002a88(int, int, int, int, int);
extern int func_020b9c10(char *a, char *b, int c, int d, int e, int f);
extern int func_ov123_02299650(void *param1, int param2);
extern void func_ov123_0229b364(void *param1);
extern void func_ov123_0229b228(void *param1);
extern void func_ov123_0229b308(void *param1);
extern void func_ov123_02299630(void *param1, int param2);
extern int func_02072614(void);
extern int func_0207261c(int a, unsigned char b);
extern int func_020b9b6c(void *a, int b, int c, int d);
extern void func_020708e4(void *a, unsigned short *b, int c);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(void *a, int b, int c);

void func_ov123_0229b204(int a)
{
    int size = 0x20;
    func_02002a88(a + 0x3030, 6, size, size, 0x11f);
}

void func_ov123_0229b1d4(char *param)
{
    func_020b9c10(param + 0x15c, param + 0x3030, 6, 0x20, 0x20, 0x11f);
}

void func_ov123_0229b1a0(void *param1)
{
    if (func_ov123_02299650(param1, 0x40)) {
        func_ov123_0229b364(param1);
        func_ov123_0229b228(param1);
        func_ov123_0229b308(param1);
        func_ov123_0229b1d4((char *) param1);
        func_ov123_02299630(param1, 0x40);
    }
}

int func_ov123_0229b174(void *param)
{
    return func_020b9b6c((char *) param + 0x124, func_0207261c(func_02072614(), ((unsigned char *) param)[0xa1]), 6, 0xe);
}

void func_ov123_0229b160(void *r0, unsigned char r1)
{
    ((unsigned char *) r0)[0xa2] = r1;
    ((unsigned char *) r0)[0xa3] = (r1 - 1) * 0xc;
}

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
