/* turtle4_2: 5 functions, module ov084
 * mwccarm 1.2/base -O4,s
 * func_ov084_0227904c @ 0x0227904c, 0x34 bytes, Thumb
 * func_ov084_02279048 @ 0x02279048, 0x4 bytes, Thumb
 * func_ov084_02279010 @ 0x02279010, 0x38 bytes, Thumb
 * func_ov084_02278fe4 @ 0x02278fe4, 0x2c bytes, Thumb
 * func_ov084_02278fe0 @ 0x02278fe0, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *argument0, int argument1, int argument2, int argument3, int argument4, short argument5,
                         short argument6, int argument7, int argument8, unsigned short argument9, unsigned short argument10);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov084_02279080(void *, int);

int func_ov084_0227904c(char *param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov084_02279048(void)
{
    return 1;
}

int func_ov084_02279010(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov084_02278fe4(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov084_02279080(self, 2);
    }
    return 1;
}

int func_ov084_02278fe0(void)
{
    return 1;
}
