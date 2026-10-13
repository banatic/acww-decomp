/* func_ov143_0229a0b0 @ 0x0229a0b0, 0x84 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a768(void *, int);
extern void func_ov143_022996a4(void *, int *, int _x);

int func_ov143_0229a0b0(unsigned char *self)
{
    unsigned char mode = self[0xa4];

    if (mode <= 0xf) {
        int out[3];
        func_ov143_022996a4(self, out, mode);
        return out[0] + 0xa;
    } else {
        switch (mode) {
            case 0x10:
                return 0x2e;
            case 0x11:
                return 0x94;
            case 0x12:
                return func_ov002_0220a768(self + 0x110, 1) - 6;
            case 0x13:
                return func_ov002_0220a768(self + 0x110, 2) - 6;
            case 0x14:
                return func_ov002_0220a768(self + 0x110, 3);
            case 0x15:
                return func_ov002_0220a768(self + 0x110, 4);
            default:
                return 0x80;
        }
    }
}