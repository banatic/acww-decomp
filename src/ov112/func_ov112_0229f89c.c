/* func_ov112_0229f89c @ 0x0229f89c, 0x48 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bbc0(unsigned char *, unsigned char *, unsigned char, unsigned char, int);
extern void func_ov112_0229f6d4(void *, unsigned char);
extern void func_ov112_0229f8e4(void *);

void func_ov112_0229f89c(unsigned char *self)
{
    unsigned char a = self[0xBF];
    unsigned char b = self[0xBE];
    unsigned char min, max, v;

    if (b > a) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }

    v = (unsigned char) func_ov095_0229bbc0(self + 0x384, self + 0xC4, min, max, 0x60);
    func_ov112_0229f6d4(self, v);
    func_ov112_0229f8e4(self);
}
