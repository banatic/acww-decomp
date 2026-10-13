/* func_ov082_02279288 @ 0x02279288, 0x2c bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov082_02279324(void *, int);

int func_ov082_02279288(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov082_02279324(self, 2);
    }
    return 1;
}
