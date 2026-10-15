/* func_02017d80 @ 0x02017d80, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *ptr, int);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_0209129c(int value);

void func_02017d80(void *self, void *other)
{
    if (func_020164cc((char *) other + 0x334, (int) other)) {
        func_02016764((char *) other + 0x334, other, 0x2a, 0, 1, 0x1000, 0, 0);
        {
            int val = *((int *) ((char *) self + 0xac));
            if (val != -1) {
                func_0209129c(val);
            }
        }
        *((unsigned char *) self + 0x98) = 0xc;
    }
}
