/* func_ov098_022a2cd8 @ 0x022a2cd8, 0xd4 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
    Pair(int x, int y)
    {
        a = x;
        b = y;
    }
};

extern "C" Pair *func_ov098_022a2cd8(int unused, int idx)
{
    static Pair table[16] = {Pair(0, 1),  Pair(1, 1),  Pair(1, 1),  Pair(1, 0),   Pair(1, 0),   Pair(1, -1),
                             Pair(1, -1), Pair(0, -1), Pair(0, -1), Pair(-1, -1), Pair(-1, -1), Pair(-1, 0),
                             Pair(-1, 0), Pair(-1, 1), Pair(-1, 1), Pair(0, 1)};
    return &table[((idx >> 12) & 0xf)];
}
