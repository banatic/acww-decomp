/* fortune_teller_3: 8 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02260e1c @ 0x02260e1c, 0x34 bytes, Thumb
 * func_ov045_02260e00 @ 0x02260e00, 0x1c bytes, Thumb
 * func_ov045_02260dcc @ 0x02260dcc, 0x34 bytes, Thumb
 * func_ov045_02260da0 @ 0x02260da0, 0x2c bytes, Thumb
 * func_ov045_02260d9c @ 0x02260d9c, 0x4 bytes, Thumb
 * func_ov045_02260d6c @ 0x02260d6c, 0x30 bytes, Thumb
 * func_ov045_02260d68 @ 0x02260d68, 0x4 bytes, Thumb
 * func_ov045_02260d64 @ 0x02260d64, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov045_02260644(void);
extern int func_0203e0a8(int, int);
extern void *func_02016104(void *);
extern int func_0201c314(void *, void *);
extern int func_020147e0(void *, int, int);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov045_02260e50(void *, int);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);

int func_ov045_02260e1c(void *param)
{
    func_02019d0c((char *) param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov045_02260e00(int param)
{
    int r4 = param;
    if (func_ov045_02260644() != 0) {
        func_0203e0a8(r4, 0);
    }
    return 1;
}

int func_ov045_02260dcc(void *self)
{
    void *p;
    p = func_02016104((char *) self + 0x68c);
    if (p != 0) {
        func_0201c314(self, p);
    }
    func_020147e0((char *) self + 0x618, 1, 0);
    return 1;
}

int func_ov045_02260da0(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov045_02260e50(self, 2);
    }
    return 1;
}

int func_ov045_02260d9c(void)
{
    return 1;
}

int func_ov045_02260d6c(void *param)
{
    if (func_02014868((char *) param + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov045_02260e50(param, 2);
    }
    return 1;
}

int func_ov045_02260d68(void)
{
    return 1;
}

int func_ov045_02260d64(void)
{
    return 1;
}
