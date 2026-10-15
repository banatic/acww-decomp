/* func_ov045_02260da0 @ 0x02260da0, 0x2c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov045_02260e50(void *, int);

int func_ov045_02260da0(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov045_02260e50(self, 2);
    }
    return 1;
}
