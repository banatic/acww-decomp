/* func_ov094_0229a34c @ 0x0229a34c, 0x1e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a34c(void *r0, int r1);

void func_ov094_0229a34c(void *r0, int r1)
{
    int r2 = r1 >> 5;
    int r4 = ((int *) r0)[r2];
    int r3 = 1 << (r1 & 0x1f);
    r4 &= ~r3;
    ((int *) r0)[r2] = r4;
}
