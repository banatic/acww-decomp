/* func_0204f840 @ 0x0204f840, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f840(int *r0, int *r1, int *r2, int *r3, int *r4);

void func_0204f840(int *r0, int *r1, int *r2, int *r3, int *r4)
{
    int r5;
    int r0_val;
    int r1_val;

    r5 = *r4;
    *r0 = r5 >> 0x11;
    r0_val = *(r4 + 2);
    *r1 = r0_val >> 0x11;
    r0_val = *r4;
    r1_val = r0_val >> 0xd;
    *r2 = r1_val & 0xf;
    r0_val = *(r4 + 2);
    r1_val = r0_val >> 0xd;
    *r3 = r1_val & 0xf;
}
