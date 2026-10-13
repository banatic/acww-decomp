/* func_020860d4 @ 0x020860d4, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020860d4(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    if (idx < 1) {
        p0[idx] = ~(1 << bit) & p0[idx];
    }
}
