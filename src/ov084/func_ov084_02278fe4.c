/* func_ov084_02278fe4 @ 0x02278fe4, 0x2c bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov084_02279080(void *, int);

int func_ov084_02278fe4(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov084_02279080(self, 2);
    }
    return 1;
}
