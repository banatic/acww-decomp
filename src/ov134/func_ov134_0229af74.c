/* func_ov134_0229af74 @ 0x0229af74, 0x4c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int, int);

void func_ov134_0229af74(void *self, unsigned int a, int b)
{
    *(int *) ((char *) self + 0x84) = b + 0x3c * a;
    if (a >= 12) {
        a = (unsigned char) (a - 12);
    }
    *(unsigned short *) ((char *) self + 0x94) = (unsigned short) _s32_div_f((b + 0x3c * a) << 16, 0x2d0);
    *(unsigned short *) ((char *) self + 0x92) = (unsigned short) (b * 0x444);
}
