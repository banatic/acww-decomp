/* func_ov110_0229ccb0 @ 0x0229ccb0, 0x36 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229cd14(void *self, int other);
extern void func_ov110_0229d458(void *self, int other, unsigned short a, unsigned char b);

void func_ov110_0229ccb0(void *self, int other)
{
    if (((unsigned char *) self)[0xf1] == 1) {
        unsigned short a = *(unsigned short *) ((unsigned char *) self + 0xec);
        unsigned char b = ((unsigned char *) self)[0xf0];
        func_ov110_0229cd14(self, other);
        func_ov110_0229d458(self, other, a, b);
    }
}
