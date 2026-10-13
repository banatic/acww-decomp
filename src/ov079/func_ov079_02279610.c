/* func_ov079_02279610 @ 0x02279610, 0x2c bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov079_02279c34(void *, int);

int func_ov079_02279610(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov079_02279c34(self, 1);
    }
    return 1;
}
