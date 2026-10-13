/* func_ov080_02278e64 @ 0x02278e64, 0x2c bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov080_02278f00(void *, int);

int func_ov080_02278e64(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov080_02278f00(self, 2);
    }
    return 1;
}
