/* func_ov076_022792d4 @ 0x022792d4, 0x2c bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov076_02279370(void *, int);

int func_ov076_022792d4(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov076_02279370(self, 2);
    }
    return 1;
}
