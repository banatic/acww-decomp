/* func_ov120_0229a81c @ 0x0229a81c, 0x54 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *, unsigned int);
extern int func_ov002_0220a4f8(void *);

int func_ov120_0229a81c(void *self)
{
    if (func_ov120_0229a448(self, 0x800) != 0) {
        return *((unsigned char *) self + 0xAD);
    } else {
        unsigned char b = *((unsigned char *) self + 0xAB);
        if (b >= 2 && b <= 7) {
            return 0xA0;
        }
        if (b == 0) {
            return 0xD8;
        }
        if (b == 1) {
            return 0xBC;
        }
        if (b == 8) {
            return func_ov002_0220a4f8((unsigned char *) self + 0x674);
        }
        return 0x80;
    }
}
