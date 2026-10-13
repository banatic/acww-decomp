/* func_ov144_0229a198 @ 0x0229a198, 0x70 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a72c(char *ptr, int arg);
extern int func_ov002_0220a4d4(char *ptr);

int func_ov144_0229a198(char *p)
{
    unsigned char b = (unsigned char) p[0xC1];
    if (b <= 8) {
        unsigned int word = *(unsigned int *) (p + 0xA0);
        return ((b << 4) + 0x20) - (word & 0xF);
    } else {
        switch (b) {
            case 9:
                return func_ov002_0220a72c(p + 0x170, 6);
            case 11:
                return 0x2A;
            case 12:
                return 0x7D;
            case 13:
                return 0x65;
            case 10:
                return func_ov002_0220a4d4(p + 0x128);
            default:
                return 0x60;
        }
    }
}
