/* func_ov110_0229cd8c @ 0x0229cd8c, 0x28 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(int *);
extern int func_ov002_02209d7c(int *);

void func_ov110_0229cd8c(int *r0)
{
    int *r4 = r0;
    int *r1 = r4 + 0x22c8 / 4;
    int r0_1 = func_ov002_02209d84(r1);
    r4[0x2a] = r0_1;
    r1 = r4 + 0x22c8 / 4;
    r0_1 = func_ov002_02209d7c(r1);
    r4[0x2b] = r0_1;
}
