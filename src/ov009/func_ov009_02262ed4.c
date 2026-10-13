/* func_ov009_02262ed4 @ 0x02262ed4, 0x1c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_020044b0(unsigned char *a, int b, int c, int d);

void func_ov009_02262ed4(unsigned char *self, int arg1)
{
    unsigned char *p = self;
    p += 0x40;
    if (*p != 0) {
        func_020044b0(self, arg1, 0x7f, 0);
    }
}
