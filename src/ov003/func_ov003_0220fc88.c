/* func_ov003_0220fc88 @ 0x0220fc88, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020113e0(void *dst, short src);
extern void func_020110a0(void *src, void *dst);

void func_ov003_0220fc88(void *self)
{
    short tmp;
    short *p = &tmp;
    *p = *(short *) ((char *) self + 0x8e);
    func_020113e0(p, *(short *) ((char *) self + 0x7d4));
    func_020110a0(self, p);
}
