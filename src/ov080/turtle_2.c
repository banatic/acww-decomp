/* turtle_2: 5 functions, module ov080
 * mwccarm 1.2/base -O4,s
 * func_ov080_02278ecc @ 0x02278ecc, 0x34 bytes, Thumb
 * func_ov080_02278ec8 @ 0x02278ec8, 0x4 bytes, Thumb
 * func_ov080_02278e90 @ 0x02278e90, 0x38 bytes, Thumb
 * func_ov080_02278e64 @ 0x02278e64, 0x2c bytes, Thumb
 * func_ov080_02278e60 @ 0x02278e60, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov080_02278f00(void *, int);

int func_ov080_02278ecc(int param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, (int) data_020c80f8, 0);
    return 1;
}

int func_ov080_02278ec8(void)
{
    return 1;
}

int func_ov080_02278e90(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov080_02278e64(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov080_02278f00(self, 2);
    }
    return 1;
}

int func_ov080_02278e60(void)
{
    return 1;
}
