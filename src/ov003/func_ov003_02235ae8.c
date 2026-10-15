/* func_ov003_02235ae8 @ 0x02235ae8, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern int func_02034270(void *it, void *src, int a, int b);
extern int func_020341c8(void *it, int a);
extern void func_0203423c(void *it);

int func_ov003_02235ae8(char *self)
{
    char a[0x40];
    char b[0x40];
    unsigned char r = 0;
    char *q = self + 0x1ec;
    int lim = *(int *) (self + 0x208);
    func_02034270(a, q, 0, 0);
    if (func_020341c8(a, 1) > lim) {
        r = (unsigned char) (r + 1);
    }
    // q + 0xc is written inside the call.
    func_02034270(b, q + 0xc, 0, 0);
    if (func_020341c8(b, 1) > lim) {
        r = (unsigned char) (r + 2);
    }
    func_0203423c(b);
    func_0203423c(a);
    return r;
}
