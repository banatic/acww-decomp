/* giraffe_2: 5 functions, module ov070
 * mwccarm 1.2/base -O4,s
 * func_ov070_02279940 @ 0x02279940, 0x34 bytes, Thumb
 * func_ov070_0227993c @ 0x0227993c, 0x4 bytes, Thumb
 * func_ov070_02279904 @ 0x02279904, 0x38 bytes, Thumb
 * func_ov070_022798d8 @ 0x022798d8, 0x2c bytes, Thumb
 * func_ov070_022798d4 @ 0x022798d4, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *argument0, int argument1, int argument2, int argument3, int argument4, short argument5,
                         short argument6, int argument7, int argument8, unsigned short argument9, unsigned short argument10);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(const void *p);
extern int func_0203e020(void *p);
extern void func_ov070_02279974(void *p, int n);

int func_ov070_02279940(void *arg0)
{

    func_02019d0c((void *) ((void *) ((char *) arg0 + 0x564)), (int) ((int) (0)), (int) ((int) (1)), (int) ((int) (0)),
                  (int) ((int) (0)), (short) ((short) (0)), (short) ((short) (0)), (int) ((int) (0)), (int) ((int) (0)),
                  (unsigned short) ((unsigned short) (data_020c80f8)), (unsigned short) ((unsigned short) (0)));
    return 1;
}

int func_ov070_0227993c(void)
{
    return 1;
}

int func_ov070_02279904(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov070_022798d8(void *obj)
{
    if (func_02014868((char *) obj + 0x618) == 0) {
        func_0203e020(obj);
        func_ov070_02279974(obj, 2);
    }
    return 1;
}

int func_ov070_022798d4(void)
{
    return 1;
}
