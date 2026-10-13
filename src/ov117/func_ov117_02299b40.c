/* func_ov117_02299b40 @ 0x02299b40, 0x10c bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02030e4c(int);
extern int func_0203194c(u8 *tile, int x, int y);

void func_ov117_02299b40(u8 *dst, int cx, int cy)
{
    unsigned int ox, oy;
    unsigned int n;
    u8 v;
    unsigned int ys, xs, yodd;
    int oyy;
    unsigned int ty, tx, py, px;
    unsigned int yy, xx;
    int ex, ey;
    u8 tile[4];

    func_02030e4c(1);
    ox = cx * 16 + 16;
    oy = cy * 16 + 16;
    n = 0;
    for (ty = 0; ty < 4; ty++) {
        tx = 0;
        ys = ty * 8;
        for (; tx < 4; tx++) {
            py = 0;
            xs = tx * 8;
            for (; py < 8; py++) {
                px = 0;
                yy = ys + py;
                yodd = yy & 1;
                oyy = oy + (yy >> 1);
                for (; px < 8; px++) {
                    xx = xs + px;
                    ex = (xx & 1) == 0 ? 1 : 0;
                    ey = yodd == 0 ? 1 : 0;
                    v = 0;
                    if (func_0203194c(tile, ox + (xx >> 1), oyy)) {
                        if (ex) {
                            v = (ey ? tile[0] : tile[2]) & 0xf;
                        } else {
                            v = (u8) ((u8) ((ey ? tile[1] : tile[3]) & 0xf) << 4);
                        }
                    }
                    dst[n++ >> 1] |= v;
                }
            }
        }
    }
    func_02030e4c(0);
}
