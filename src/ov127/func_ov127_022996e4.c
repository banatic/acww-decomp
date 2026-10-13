/* func_ov127_022996e4 @ 0x022996e4, 0xf4 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299804(int, int);

int func_ov127_022996e4(unsigned short *out, int x, int y)
{
    int xm = (x - 1) & 0x3f;
    int xp = (x + 1) & 0x3f;
    int ym = y - 1;
    int yp = y + 1;
    int count = 0;
    int r;

    if (ym >= 0) {
        r = func_ov127_02299804(xm, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(x, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(xp, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
    }

    r = func_ov127_02299804(xm, y);
    if (r != -1) {
        out[count] = (unsigned short) r;
        count++;
    }
    r = func_ov127_02299804(xp, y);
    if (r != -1) {
        out[count] = (unsigned short) r;
        count++;
    }

    if (yp < 0x20) {
        r = func_ov127_02299804(xm, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(x, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(xp, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
    }

    if (x == 0x3e && y == 0) {
        count--;
    }

    return count;
}
