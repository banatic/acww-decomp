/* shop_display: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02246000 @ 0x02246000, 0x10 bytes, Thumb
 * func_ov004_02245ff8 @ 0x02245ff8, 0x8 bytes, Thumb
 * func_ov004_02245ff4 @ 0x02245ff4, 0x4 bytes, Thumb
 */

extern void func_ov004_02246010(void *object);
extern void *func_ov004_02246378(int parameter0, int parameter1);

int func_ov004_02246000(void *self)
{
    func_ov004_02246010(self);
    return 1;
}

void *func_ov004_02245ff8(int arg0, int arg1)
{
    return func_ov004_02246378(arg0, arg1);
}

int func_ov004_02245ff4(void)
{
    return 1;
}
