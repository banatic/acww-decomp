/* func_ov110_0229d3d8 @ 0x0229d3d8, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(int p1, int p2);
extern int func_ov110_0229d5d4(int p1, int p2);
extern int func_ov110_0229d5c8(int p1, int p2);
extern int func_ov110_0229d590(int p1, int p2);
extern int func_ov094_0229aba4(int p1, int p2);

int func_ov110_0229d3d8(int p1, int p2)
{
    if (func_ov110_0229d5e4(p1, p2) != 0 || func_ov110_0229d5d4(p1, p2) != 0) {
        return func_ov094_0229aba4(p1 + 0x138, func_ov110_0229d590(p1, p2));
    } else if (func_ov110_0229d5c8(p1, p2) != 0) {
        return 0xc4;
    } else {
        return 0;
    }
}
