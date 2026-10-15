/* func_ov145_02299f30 @ 0x02299f30, 0x4c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a768(char *ptr, int param);
extern int func_ov002_0220a4f8(char *ptr);

int func_ov145_02299f30(char *arg)
{
    unsigned char b;

    b = *(unsigned char *) (arg + 0xc2);
    if (b <= 3) {
        return -36 * b + 0x94;
    }
    switch (b) {
        case 4:
            return func_ov002_0220a768(arg + 0x174, 6);
        case 5:
            return func_ov002_0220a4f8(arg + 0x12c);
        default:
            return 0x80;
    }
}
