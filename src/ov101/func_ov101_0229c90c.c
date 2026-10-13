/* func_ov101_0229c90c @ 0x0229c90c, 0x36 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c970(void *self, int other);
extern void func_ov101_0229cd40(void *self, int other, unsigned short a, unsigned char b);

void func_ov101_0229c90c(void *self, int other)
{
    if (((unsigned char *) self)[0xaf] == 1) {
        unsigned short a = *(unsigned short *) ((unsigned char *) self + 0xac);
        unsigned char b = ((unsigned char *) self)[0xae];
        func_ov101_0229c970(self, other);
        func_ov101_0229cd40(self, other, a, b);
    }
}
