/* func_ov075_02278dec @ 0x02278dec, 0x2c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_ov075_022794b8(void *, int);

int func_ov075_02278dec(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov075_022794b8(self, 3);
    }
    return 1;
}
