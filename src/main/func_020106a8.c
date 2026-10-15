/* func_020106a8 @ 0x020106a8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020110e8(void *);
extern int func_0201111c(int);
extern int func_0205f874(int, int);
extern int func_0205f848(int, int);

void func_020106a8(int p0, int p1, int p2)
{
    int k = func_020110e8((void *) p0);
    int r4;
    int r1;

    if (k >= 0x10) {
        if (k >= 0x18) {
            r4 = 0x19;
        } else {
            r4 = 0x11;
        }
    } else {
        if (k >= 8) {
            r4 = 9;
        } else {
            r4 = 1;
        }
    }

    if (func_0201111c(p0) != 0) {
        r4 -= 0x10;
        r1 = p2 + r4 * 8;
    } else {
        r1 = p2 + r4 * 8;
    }

    r4 = p2 + ((p1 << 3) + 0x80);

    if (r1 < 0x80) {
        func_0205f874(p0 + 0x7a0, r1);
    }
    if (r4 >= 0x80 && r4 < 0xc0) {
        func_0205f848(p0 + 0x7a0, r4);
    }
}