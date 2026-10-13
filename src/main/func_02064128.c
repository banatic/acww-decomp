/* func_02064128 @ 0x02064128, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int, int, int);

void func_02064128(int p0, int p1, int p2)
{
    MI_CpuCopy8((p0 + 14), p1, (p2 << 1));
}
