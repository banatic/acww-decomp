/* func_02042c58 @ 0x02042c58, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Coord {
    int x;
    int y;
};

void func_02042c58(unsigned char *self, struct Coord *coord, int value)
{
    int x = coord->x;
    int y = coord->y;
    int index = ((x - 16) >> 2) + ((y - 16) << 4);
    int bit = (x & 3) << 1;
    if (index >= 0 && index < 0x400) {
        // empty
    } else {
        index = 0;
        bit = 0;
    }
    self += 0x6c;
    self[index] = (value << bit) | (self[index] & ~(3 << bit));
}
