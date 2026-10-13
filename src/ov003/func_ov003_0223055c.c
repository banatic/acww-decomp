/* func_ov003_0223055c @ 0x0223055c, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov003_02230cc0(void *a);
extern void func_ov003_02230f88(void *a);
extern void func_ov003_0223108c(void *a);

void func_ov003_0223055c(char *self, int b, int c, int d, short e)
{
    int h = func_ov003_02230cc0(self);
    func_ov003_02230ce8(self, 0, b, c, 0, h, 0xe, 0, d, 0);
    func_ov003_02230f88(self);
    if (*(unsigned char *) (self + 0x251) != 0xb) {
        func_ov003_0223108c(self);
    }
    *(int *) (self + 0x21c) = e;
}
