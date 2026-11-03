/* turtle6_2: 5 functions, module ov086
 * mwccarm 1.2/base -O4,s
 * func_ov086_02278f4c @ 0x02278f4c, 0x34 bytes, Thumb
 * func_ov086_02278f48 @ 0x02278f48, 0x4 bytes, Thumb
 * func_ov086_02278f10 @ 0x02278f10, 0x38 bytes, Thumb
 * func_ov086_02278ee4 @ 0x02278ee4, 0x2c bytes, Thumb
 * func_ov086_02278ee0 @ 0x02278ee0, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov086_02278f80(void *, int);

int func_ov086_02278f4c(void *arg)
{
    func_02019d0c((char *) arg + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov086_02278f48(void)
{
    return 1;
}

int func_ov086_02278f10(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov086_02278ee4(void *arg0)
{
    if (func_02014868((char *) arg0 + 0x618) == 0) {
        func_0203e020(arg0);
        func_ov086_02278f80(arg0, 2);
    }
    return 1;
}

int func_ov086_02278ee0(void)
{
    return 1;
}
