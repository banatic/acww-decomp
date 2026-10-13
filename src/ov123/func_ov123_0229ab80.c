/* func_ov123_0229ab80 @ 0x0229ab80, 0x100 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov123_0229ac80(int a, unsigned char b, unsigned char c, int f, int g, int h);

int func_ov123_0229ab80(int a, unsigned int b, unsigned int c, unsigned int d, unsigned char e, int f, int g)
{
    int dx, dy;
    int err;
    int sx;
    int sy;
    int i;
    int result;
    int two_dy;
    int two_dx;
    int err2;
    int i2;
    int h;
    int h2;
    unsigned int x = b;
    unsigned int y = c;

    result = 0;

    if (d > x) {
        sx = 1;
        dx = (int) (d - x);
    } else {
        sx = -1;
        dx = (int) (x - d);
    }

    if (e > y) {
        sy = 1;
        dy = (int) (e - y);
    } else {
        sy = -1;
        dy = (int) (y - e);
    }

    if (dx >= dy) {
        err = -dx;
        i = 0;
        dy = (dy << 1);
        two_dx = (dx << 1);
        h = i;

        for (; i <= dx; i++) {
            result |= func_ov123_0229ac80(a, (unsigned char) x, (unsigned char) y, f, g, h);
            x += sx;
            err += dy;
            if (err >= 0) {
                y += sy;
                err -= two_dx;
            }
        }
    } else {
        err2 = -dy;
        i2 = 0;
        dx = (dx << 1);
        two_dy = (dy << 1);
        h2 = i2;

        for (; i2 <= dy; i2++) {
            result |= func_ov123_0229ac80(a, (unsigned char) x, (unsigned char) y, f, g, h2);
            y += sy;
            err2 += dx;
            if (err2 >= 0) {
                x += sx;
                err2 -= two_dy;
            }
        }
    }

    return result;
}
