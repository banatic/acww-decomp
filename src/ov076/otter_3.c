/* otter_3: 5 functions, module ov076
 * mwccarm 1.2/base -O4,s
 * func_ov076_0227933c @ 0x0227933c, 0x34 bytes, Thumb
 * func_ov076_02279338 @ 0x02279338, 0x4 bytes, Thumb
 * func_ov076_02279300 @ 0x02279300, 0x38 bytes, Thumb
 * func_ov076_022792d4 @ 0x022792d4, 0x2c bytes, Thumb
 * func_ov076_022792d0 @ 0x022792d0, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *, int, int, int, int, short, short, int, int, unsigned short, unsigned short);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov076_02279370(void *, int);

int func_ov076_0227933c(void *param)
{

    func_02019d0c((char *) param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov076_02279338(void)
{
    return 1;
}

int func_ov076_02279300(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov076_022792d4(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov076_02279370(self, 2);
    }
    return 1;
}

int func_ov076_022792d0(void)
{
    return 1;
}
