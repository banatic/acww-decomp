/* func_ov068_02272654 @ 0x02272654, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02272dc8(void *self);
extern void func_02055060(void *ptr, int a, int b, int c, int d, int e);
extern void func_ov009_02262ef0(void *ptr, int a);

int func_ov068_02272654(void *self)
{
    int x = func_ov068_02272dc8(self);
    func_02055060((char *) self + 0x13c, x, 1, 0x1000, 0, 0);
    func_ov009_02262ef0((char *) self + 0x238, 0x88b);
    ((char *) self)[0x2dc] = 0;
    return 1;
}
