/* func_ov003_02221d3c @ 0x02221d3c, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02224140(int, int, int, int);

void func_ov003_02221d3c(int *r0, int *r1)
{
    int r2 = 0x1000;
    r0[0x3c / 4] = r2;
    r0[0x40 / 4] = r2;
    r0[0x44 / 4] = r2;
    func_ov003_02224140(r1[0], r1[1], 0xfff1, 0);
}
