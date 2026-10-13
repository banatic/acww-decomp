/* func_ov003_02233930 @ 0x02233930, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02271960(void *a, void *b);
extern void func_ov068_02271a14(void *a, void *b);
extern void func_ov068_0227191c(void *a, void *b);
extern void func_ov003_02230e18(void *a, void *b);

void func_ov003_02233930(char *self)
{
    short *p = (short *) (self + 0x242);
    unsigned char *s = (unsigned char *) (self + 0x251);
    switch (*s) {
        case 3:
        case 0xf:
            func_ov068_02271960(self, p);
            break;
        case 4:
            func_ov068_02271a14(self, p);
            func_ov068_0227191c(self, p);
            break;
        case 0xb:
            func_ov003_02230e18(self, p);
            *p = (short) (*p + 1);
            break;
        case 0x13:
            if (*(short *) (self + 0x232) <= 0) {
                *s = 3;
            } else {
                *(short *) (self + 0x232) = (short) (*(short *) (self + 0x232) - 1);
            }
            break;
    }
}
