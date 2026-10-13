/* func_ov111_0229fb48 @ 0x0229fb48, 0x44 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov095_0229bbc0(void *a, void *b, unsigned char c, unsigned char d, int e);
extern void func_ov111_0229f4c4(void *self);

void func_ov111_0229fb48(unsigned char *self)
{
    unsigned char x = self[0xA0];
    unsigned char y = self[0x9F];
    unsigned char min, max;

    if (y > x) {
        min = x;
        max = y;
    } else {
        min = y;
        max = x;
    }

    self[0x9E] = func_ov095_0229bbc0(self + 0xAC, self + 0x3D16, min, max, 16);
    func_ov111_0229f4c4(self);
}
