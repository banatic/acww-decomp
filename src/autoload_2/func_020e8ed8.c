/* func_020e8ed8 @ 0x020e8ed8, 0x194 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned short data_0213dda0[];
#define LOOKUP(i) data_0213dda0[(i)]
extern int FX_Div(int, int);

short func_020e8ed8(int y, int x)
{
    int res;

    if (y == 0) {
        res = (x >= 0) ? 0 : 0x8000;
    } else if (x == 0) {
        res = (y >= 0) ? 0x4000 : 0xc000;
    } else if (y >= 0) {
        if (x >= 0) {
            if (x >= y) {
                res = LOOKUP(FX_Div(y, x) >> 2);
            } else {
                res = 0x4000 - LOOKUP(FX_Div(x, y) >> 2);
            }
        } else {
            x = -x;
            if (x < y) {
                res = 0x4000 + LOOKUP(FX_Div(x, y) >> 2);
            } else {
                res = 0x8000 - LOOKUP(FX_Div(y, x) >> 2);
            }
        }
    } else {
        if (x < 0) {
            if (x <= y) {
                res = 0x8000 + LOOKUP(FX_Div(-y, -x) >> 2);
            } else {
                res = 0xc000 - LOOKUP(FX_Div(-x, -y) >> 2);
            }
        } else {
            y = -y;
            if (x < y) {
                res = 0xc000 + LOOKUP(FX_Div(x, y) >> 2);
            } else {
                res = -LOOKUP(FX_Div(y, x) >> 2);
            }
        }
    }
    return (short) res;
}
