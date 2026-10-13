/* func_ov110_0229cc14 @ 0x0229cc14, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d3d8(void *p, unsigned char b);
extern int func_ov110_0229c2c8(void *p, int n);

int func_ov110_0229cc14(void *p)
{
    int v;

    v = func_ov110_0229d3d8(p, ((unsigned char *) p)[0xf5]);
    if (func_ov110_0229c2c8(p, 0x20)) {
        v += 0x100;
    } else if (func_ov110_0229c2c8(p, 0x10)) {
        v -= 0x100;
    }
    v += 8;
    return v;
}
