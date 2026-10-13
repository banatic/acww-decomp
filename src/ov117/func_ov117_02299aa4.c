/* func_ov117_02299aa4 @ 0x02299aa4, 0x12 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct tile {
    char data[512];
};
struct tile *func_ov117_02299aa4(struct tile *base, unsigned int a, unsigned int b)
{
    if (a >= 4 || b >= 4) {
        return base;
    }
    return &base[a + b * 4];
}
