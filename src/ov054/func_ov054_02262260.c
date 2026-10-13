/* func_ov054_02262260 @ 0x02262260, 0x2c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov054_02262528(void *, int);

int func_ov054_02262260(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov054_02262528(self, 5);
    }
    return 1;
}
