/* turtle_fishing_2: 5 functions, module ov081
 * mwccarm 1.2/base -O4,s
 * func_ov081_022792ac @ 0x022792ac, 0x34 bytes, Thumb
 * func_ov081_022792a8 @ 0x022792a8, 0x4 bytes, Thumb
 * func_ov081_02279270 @ 0x02279270, 0x38 bytes, Thumb
 * func_ov081_02279244 @ 0x02279244, 0x2c bytes, Thumb
 * func_ov081_02279240 @ 0x02279240, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(const void *);
extern int func_0203e020(const void *);
extern void func_ov081_022792e0(const void *, int);

int func_ov081_022792ac(void *p)
{
    func_02019d0c((char *) p + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov081_022792a8(void)
{
    return 1;
}

int func_ov081_02279270(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov081_02279244(const void *p)
{
    if (!func_02014868((const char *) p + 0x618)) {
        func_0203e020(p);
        func_ov081_022792e0(p, 2);
    }
    return 1;
}

int func_ov081_02279240(void)
{
    return 1;
}
