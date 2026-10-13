/* func_ov003_022309c0 @ 0x022309c0, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

void func_ov003_022309c0(char *self, int b, int c, int d, int e)
{
    int *v = (int *) (self + 0x204);
    if (*(signed char *) (self + 0x24d) == 0x1f && *(unsigned char *) (self + 0x251) == 0xb) {
        func_ov003_02230ce8(self, 0, b, c, 0, 0, 0, 0, 0, 0);
    } else {
        func_ov003_02230ce8(self, 0, b, c, 0x3556, -0x8000, d, 0, 0, 0);
        v[2] += e;
        *(char *) (self + 0x246) = 1;
    }
}
