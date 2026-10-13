/* func_ov120_0229ae78 @ 0x0229ae78, 0x60 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov120_0229ae78(unsigned char *p, int x, int y)
{
    int i;
    unsigned char *q;
    int vx, vy;

    for (i = 0; i < 14; i++) {
        q = p + i * 3;
        if (q[0x2745] == 12) {
            continue;
        }
        vx = q[0x2743];
        if (vx - 8 >= x) {
            continue;
        }
        if (vx + 8 <= x) {
            continue;
        }
        vy = q[0x2744];
        if (vy - 8 >= y) {
            continue;
        }
        if (vy + 8 <= y) {
            continue;
        }
        return i;
    }
    return 14;
}
