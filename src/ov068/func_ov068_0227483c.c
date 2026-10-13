/* func_ov068_0227483c @ 0x0227483c, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov068_022749dc(void *, int);

int func_ov068_0227483c(void *self)
{
    if (func_02014868((char *) self + 0x618)) {
        return 1;
    }
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov068_022749dc(self, 4);
    }
    return 1;
}
