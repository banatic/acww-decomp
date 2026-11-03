/* friend_roster_page_3: 4 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229bb7c @ 0x0229bb7c, 0x2c bytes, Thumb
 * func_ov119_0229bb44 @ 0x0229bb44, 0x38 bytes, Thumb
 * func_ov119_0229bb0c @ 0x0229bb0c, 0x38 bytes, Thumb
 * func_ov119_0229bacc @ 0x0229bacc, 0x40 bytes, Thumb
 */

extern void func_02070b84(void *);
extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov119_0229bb7c(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0x9e;
    *p = 0;
    base = (char *) arg0 + 0x4d0;
    for (i = 0; i < 0x13; i++) {
        func_02070b84(base + i * 0x6c);
    }
}

unsigned char *func_ov119_0229bb44(unsigned char *self)
{
    if (self[0x9e] >= 0x13) {
        return self + 0xc68;
    } else {
        self[0x9e] = (*(volatile unsigned char *) &self[0x9e]) + 1;
        return self + 0x4d0 + (self[0x9e] - 1) * 0x6c;
    }
}

void func_ov119_0229bb0c(unsigned char *arg0)
{
    int r4;
    int sp[4];

    r4 = (int) func_ov119_0229bb44((unsigned char *) arg0);
    func_0207094c(r4, 0xd6);
    sp[0] = 0xf;
    sp[1] = 0;
    sp[2] = 0;
    func_02070adc(r4, 8, 0xca, 6, sp[0], sp[1], sp[2]);
    func_02070a04(r4, 1, 0);
}

void func_ov119_0229bacc(int param0, int param1)
{
    int result = (int) func_ov119_0229bb44((unsigned char *) param0);
    func_0207094c(result, param1);
    func_02070adc(result, 8, 0x160, 0xd, 0xf, 0, 0);
    func_02070a04(result, 1, 0);
}
