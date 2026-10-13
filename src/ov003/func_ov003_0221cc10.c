/* func_ov003_0221cc10 @ 0x0221cc10, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264cf8(void *p, int a);
extern void func_02056478(void *p, int a, int b, int c, int d);

int func_ov003_0221cc10(void *self)
{
    int result;

    result = func_ov009_02264cf8(self, 0);
    func_02056478((char *) self + 0x2b4, result, 0, 0x1000, 0);
    *((unsigned char *) self + 0x2d5) = 0x1f;
    return 1;
}
