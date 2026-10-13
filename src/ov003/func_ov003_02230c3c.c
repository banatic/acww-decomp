/* func_ov003_02230c3c @ 0x02230c3c, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov003_02230cc0(void);
extern int func_020644cc(int a);

void func_ov003_02230c3c(char *self, int b, int c, int d, unsigned char e, int f)
{
    int r = func_020644cc(3);
    int h = func_ov003_02230cc0();
    func_ov003_02230ce8(self, (short) (0x14 * (r + 5)), b, c, 0, h, d, 0, e, 0);
    *(char *) (self + 0x252) = 0x28;
    *(char *) (self + 0x256) = (char) func_020644cc(0x12);
    *(char *) (self + 0x24c) = 1;
    *(int *) (self + 0x21c) = f;
    *(short *) (self + 0x232) = 0;
}
