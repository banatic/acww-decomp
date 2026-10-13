/* func_020b5fc8 @ 0x020b5fc8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6044(int a, int b, int *w, short *s);
extern void func_0204f7e0(int *dst, int *src);

int func_020b5fc8(int a, int b, int *dest, int *src)
{
    short s0;
    int w4;
    int tmp[3];
    if (func_020b6044(a, b, &w4, &s0) != 0) {
        func_0204f7e0(tmp, src);
        {
            int t2 = tmp[2];
            int t1 = src[1];
            int t0 = tmp[0];
            dest[0] = t0;
            dest[1] = t1;
            dest[2] = t2;
        }
        if (s0 == 0 || s0 == 0xffff8000) {
            dest[0] = src[0];
            return 1;
        }
        if (s0 == 0x4000 || s0 == 0xffffc000) {
            dest[2] = src[2];
            return 1;
        }
        return 1;
    }
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return 0;
}
