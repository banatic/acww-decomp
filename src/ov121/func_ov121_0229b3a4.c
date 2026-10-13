/* func_ov121_0229b3a4 @ 0x0229b3a4, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const void *ptr);
extern int func_ov121_02299fc8(const void *p);
extern int func_ov121_0229bc70(const void *p, int r);
extern void func_ov121_0229a150(const void *p);

void func_ov121_0229b3a4(const void *self)
{
    if (func_0208e484((const char *) self + 0x3a8) == 0) {
        return;
    }
    {
        int r = func_ov121_02299fc8(self);
        if (r == -1 || func_ov121_0229bc70(self, r) == 0) {
            func_ov121_0229a150(self);
        }
    }
}
