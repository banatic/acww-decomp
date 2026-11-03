/* bank_menu: 5 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229ade4 @ 0x0229ade4, 0x18 bytes, Thumb
 * func_ov132_0229adb8 @ 0x0229adb8, 0x2c bytes, Thumb
 * func_ov132_0229ad88 @ 0x0229ad88, 0x30 bytes, Thumb
 * func_ov132_0229ad70 @ 0x0229ad70, 0x18 bytes, Thumb
 * func_ov132_0229ad60 @ 0x0229ad60, 0x10 bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_02070b84(void *);

void func_ov132_0229ade4(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098(self, 3);
}

void func_ov132_0229adb8(unsigned char *p)
{
    int i;
    p[0x1504] = 0;
    for (i = 0; i < 2; i++) {
        func_02070b84(p + 0x2c4 + i * 0x6c);
    }
}

unsigned char *func_ov132_0229ad88(unsigned char *self)
{
    if (self[0x1504] >= 2) {
        return self + 0x330;
    } else {
        self[0x1504] = self[0x1504] + 1;
        return self + 0x2c4 + 0x6c * (self[0x1504] - 1);
    }
}

int func_ov132_0229ad70(char *a, int b)
{
    if (*(unsigned short *) (a + 0x1500) & b) {
        return 1;
    }
    return 0;
}

void func_ov132_0229ad60(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x1500);
    *p = (unsigned short) (*p | mask);
}
