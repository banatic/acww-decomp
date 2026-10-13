/* func_ov003_0222e7f8 @ 0x0222e7f8, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];
extern int func_ov003_0222e7bc(int x);

void func_ov003_0222e7f8(int v)
{
    unsigned char *p;
    unsigned char st;
    unsigned char i;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    *(unsigned short *) (p + 0x242) = 0;
    st = p[0x251];
    if (func_ov003_0222e7bc(*(signed char *) (p + 0x24d)) != 0 && p[0x250] != 4 && st != 0x10 && st != 0xa) {
        if (st != 0x11) {
            if (*(short *) (p + 0x232) > 6) {
                *(short *) (p + 0x232) = 6;
                p[0x251] = 0x11;
            }
        }
    } else {
        p[0x250] = 4;
    }
}
