/* func_ov143_0229a030 @ 0x0229a030, 0x80 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_022996a4(void *self, int *out, unsigned char index);
extern int func_ov002_0220a72c(void *self, int param);

int func_ov143_0229a030(void *self)
{
    unsigned char b;
    int local[3];

    b = *(unsigned char *) ((char *) self + 0xa4);
    if (b <= 15) {
        func_ov143_022996a4(self, local, b);
        return local[1] + 3;
    }
    switch (b) {
        case 16:
            return 0xa0;
        case 17:
            return 0xa0;
        case 18:
            return func_ov002_0220a72c((char *) self + 0x110, 1);
        case 19:
            return func_ov002_0220a72c((char *) self + 0x110, 2);
        case 20:
            return func_ov002_0220a72c((char *) self + 0x110, 3);
        case 21:
            return func_ov002_0220a72c((char *) self + 0x110, 4);
        default:
            return 0x60;
    }
}
