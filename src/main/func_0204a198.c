/* func_0204a198 @ 0x0204a198, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c7a08[];
extern void func_0204a25c(int, int, int, unsigned short, int);

void func_0204a198(int p0, unsigned short id, int x, int y)
{
    unsigned char v;
    unsigned char *p;
    int ox, oy, xb, yb;

    v = 0x25;
    switch (id) {
        case 0x26:
            break;
        case 0x5d:
            v = 0x5c;
            break;
        case 0xc8:
            v = 0xc7;
            break;
    }

    ox = x >> 4;
    oy = y >> 4;
    xb = (x - (ox << 4)) >> 3;
    yb = (y - (oy << 4)) >> 3;
    p = data_021c7a08 + ox * 0x90 + oy * 0x24 + 4 + (xb << 1) + yb;
    *p -= 1;

    func_0204a25c(p0, x, y, v, 0);
}
