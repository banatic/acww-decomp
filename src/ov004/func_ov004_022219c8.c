/* func_ov004_022219c8 @ 0x022219c8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov004_02221a64(void *, int);

int func_ov004_022219c8(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov004_02221a64(self, 1);
    }
    return 1;
}
