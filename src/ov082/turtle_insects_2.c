/* turtle_insects_2: 5 functions, module ov082
 * mwccarm 1.2/base -O4,s
 * func_ov082_022792f0 @ 0x022792f0, 0x34 bytes, Thumb
 * func_ov082_022792ec @ 0x022792ec, 0x4 bytes, Thumb
 * func_ov082_022792b4 @ 0x022792b4, 0x38 bytes, Thumb
 * func_ov082_02279288 @ 0x02279288, 0x2c bytes, Thumb
 * func_ov082_02279284 @ 0x02279284, 0x4 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov082_02279324(void *, int);

unsigned int func_ov082_022792f0(unsigned int a)
{
    func_02019d0c(a + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov082_022792ec(void)
{
    return 1;
}

int func_ov082_022792b4(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov082_02279288(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov082_02279324(self, 2);
    }
    return 1;
}

int func_ov082_02279284(void)
{
    return 1;
}
