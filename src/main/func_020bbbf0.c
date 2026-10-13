/* func_020bbbf0 @ 0x020bbbf0, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short r : 5;
    unsigned short g : 5;
    unsigned short b : 5;
    unsigned short a : 1;
} RGB555;

void func_020bbbf0(RGB555 *dst, RGB555 *ca, RGB555 *cb, int weightB)
{
    int weightA = 0x1000 - weightB;

    dst->r = (ca->r * weightA + cb->r * weightB) >> 12;
    dst->g = (ca->g * weightA + cb->g * weightB) >> 12;
    dst->b = (ca->b * weightA + cb->b * weightB) >> 12;
    dst->a = 0;
}
