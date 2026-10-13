/* func_ov094_0229a36c @ 0x0229a36c, 0x1e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a36c(void *r0, int r1);

void func_ov094_0229a36c(void *r0, int r1)
{
    int r2;
    int r3;
    int r4;
    int r5;

    r2 = r1 >> 5;
    r5 = r2 << 2;
    r4 = *(int *) ((char *) r0 + r5);
    r3 = 1;
    r2 = 0x1f;
    r1 &= r2;
    r3 <<= r1;
    r4 |= r3;
    *(int *) ((char *) r0 + r5) = r4;
}
