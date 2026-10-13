/* func_ov004_0222cc24 @ 0x0222cc24, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Unused local of a class with a destructor; it only reserves stack space.
struct V {
    int x, y, z;
    ~V() {}
};

extern "C" void func_ov004_0222cc24(void *self, V *out)
{
    V t;

    out->x = 0xc000;
    out->y = 0;
    out->z = 0x17000;
}
