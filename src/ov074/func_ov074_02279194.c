/* func_ov074_02279194 @ 0x02279194, 0x2c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov074_02279778(void *, int);

int func_ov074_02279194(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov074_02279778(self, 1);
    }
    return 1;
}
