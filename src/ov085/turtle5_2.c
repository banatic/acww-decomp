/* turtle5_2: 5 functions, module ov085
 * mwccarm 1.2/base -O4,s
 * func_ov085_022790b8 @ 0x022790b8, 0x34 bytes, Thumb
 * func_ov085_022790b4 @ 0x022790b4, 0x4 bytes, Thumb
 * func_ov085_0227907c @ 0x0227907c, 0x38 bytes, Thumb
 * func_ov085_02279050 @ 0x02279050, 0x2c bytes, Thumb
 * func_ov085_0227904c @ 0x0227904c, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *p);
extern int func_0203e020(void *p);
extern void func_ov085_022790ec(void *p, int n);

int func_ov085_022790b8(void *arg)
{
    func_02019d0c((char *) arg + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov085_022790b4(void)
{
    return 1;
}

int func_ov085_0227907c(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov085_02279050(void *p)
{
    if (func_02014868((char *) p + 0x618) == 0) {
        func_0203e020(p);
        func_ov085_022790ec(p, 2);
    }
    return 1;
}

int func_ov085_0227904c(void)
{
    return 1;
}
