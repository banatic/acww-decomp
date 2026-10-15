/* func_ov004_02225634 @ 0x02225634, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern int func_0203e020(void *self);
extern void func_ov004_022256ec(void *self, int k);
int func_ov004_02225634(unsigned char *self)
{
    if (func_02014868(self + 0x618) != 0) {
        return 1;
    }
    if (func_02014868(self + 0x618) == 0) {
        func_0203e020(self);
        func_ov004_022256ec(self, 2);
    }
    return 1;
}
