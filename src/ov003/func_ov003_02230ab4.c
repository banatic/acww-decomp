/* func_ov003_02230ab4 @ 0x02230ab4, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020644cc(int a);
extern void func_ov003_0222d518(void *a, int b);

void func_ov003_02230ab4(char *self)
{
    int *v = (int *) (self + 0x1e0);
    int *s;
    func_ov003_02230ce8(self, 0x384, 0xc8, 0x28, 1, -0x8000, 0x2f, 0, 0xa, 0);
    *(char *) (self + 0x252) = 0x3c;
    *(char *) (self + 0x256) = (char) func_020644cc(0x12);
    *(char *) (self + 0x24c) = 1;
    *(int *) (self + 0x220) = 0;
    s = (int *) (self + 0x204);
    *(int *) (self + 0x1e0) = s[0];
    v[1] = s[1];
    v[2] = s[2];
    func_ov003_0222d518(self, 0x1000);
}
