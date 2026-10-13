/* func_ov145_02299aac @ 0x02299aac, 0x70 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(char *ptr, int a, int b, int c, int d, int e);
extern int func_ov145_02299a24(char *self);
extern int func_020b9bbc(char *a, char *b, int c, int d, int e);
extern void func_ov145_02299648(char *self, int a);

void func_ov145_02299aac(char *self)
{
    int zero = 0;

    func_0206fdd4(self + 0x14c6, zero, zero, 31, 31, 3);
    {
        int ret = func_ov145_02299a24(self);
        if (ret < 9) {
            func_0206fdd4(self + 0x14c6, zero, ret * 2, 31, 18, 4);
        }
    }
    if (func_020b9bbc(self + 0xad8, self + 0x14c6, 4, 0x800, 0) != 0) {
        func_ov145_02299648(self, 8);
    }
}
