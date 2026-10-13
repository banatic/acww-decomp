/* func_ov087_02279010 @ 0x02279010, 0x2c bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov087_022790ac(void *, int);

int func_ov087_02279010(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov087_022790ac(self, 2);
    }
    return 1;
}
