/* func_02086108 @ 0x02086108, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */
int func_02086108(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    return (idx < 1) && (((1 << bit) & p0[idx]) != 0);
}
