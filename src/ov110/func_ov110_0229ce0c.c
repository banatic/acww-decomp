/* func_ov110_0229ce0c @ 0x0229ce0c, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229c2c8(void *, int);
extern void func_ov094_0229a6bc(void *, void *, void *);

void func_ov110_0229ce0c(unsigned char *self)
{
    unsigned char b;

    if (func_ov110_0229c2c8(self, 0x40) != 0) {
        return;
    }

    b = self[0xf1];
    if (b == 0) {
        return;
    }
    if (b != 1) {
        return;
    }

    func_ov094_0229a6bc((void *) (self + 0x138), *(void **) (self + 0xa8), *(void **) (self + 0xac));
}
