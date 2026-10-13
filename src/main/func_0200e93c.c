/* func_0200e93c @ 0x0200e93c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern int func_020e8ed8(int, int);

int func_0200e93c(int a0, int a1, int a2, int a3, short a4, short *a5)
{
    int v, result, diff;

    if (a3 < FX_MulFunc(0x108, 0x108)) {
        return 0;
    }

    v = func_020e8ed8(a1, a2);

    if (a3 >= FX_MulFunc(0x2666, 0x2666)) {
        result = 1;
    } else {
        diff = (short) (v - a4);
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < 0x4000) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result) {
        *a5 = (short) v;
    }

    return result;
}
