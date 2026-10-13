/* func_ov102_0229cc24 @ 0x0229cc24, 0x3c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229cc90(void *p, int a);
extern void func_ov102_0229d2a4(void *p, int a, unsigned short b, unsigned char c);

void func_ov102_0229cc24(unsigned char *self, int param)
{
    if (self[0x259f] == 1) {
        unsigned short field_a = *(unsigned short *) (self + 0x259c);
        unsigned char field_b = self[0x259e];
        func_ov102_0229cc90(self, param);
        func_ov102_0229d2a4(self, param, field_a, field_b);
    }
}
