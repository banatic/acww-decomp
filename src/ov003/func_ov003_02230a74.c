/* func_ov003_02230a74 @ 0x02230a74, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

void func_ov003_02230a74(char *self)
{
    int save = *(int *) (self + 0x21c);
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 6, 1);
    *(int *) (self + 0x21c) = save;
    *(char *) (self + 0x252) = 0x3c;
}
