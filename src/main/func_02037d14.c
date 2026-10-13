/* func_02037d14 @ 0x02037d14, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02037d14(int *r0, int *r1, int r2);

void func_02037d14(int *r0, int *r1, int r2)
{
    int r4;
    int r0_val;
    r4 = r2 & 0xf;
    *r0 = r4;
    r0_val = (r2 >> 4) & 0xf;
    *r1 = r0_val;
}
