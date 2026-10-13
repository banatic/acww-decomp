/* func_020860f0 @ 0x020860f0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020860f0(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    if (idx < 1) {
        p0[idx] = (1 << bit) | p0[idx];
    }
}
