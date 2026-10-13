/* func_ov003_02230314 @ 0x02230314, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

void func_ov003_02230314(char *self)
{
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 8, 1);
    *(int *) (self + 0x21c) = *(unsigned char *) (self + 0x257);
    *(int *) (self + 0x228) = *(int *) (self + 0x208);
}
