/* func_ov078_02279640 @ 0x02279640, 0x2c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov078_02279670(void *, int);

int func_ov078_02279640(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov078_02279670(self, 1);
    }
    return 1;
}
