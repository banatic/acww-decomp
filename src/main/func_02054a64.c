/* func_02054a64 @ 0x02054a64, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02054a64(unsigned int *p, unsigned int bit)
{
    if (bit >= 32) {
        p[0x54] |= (1 << (bit - 32));
    } else {
        p[0x53] |= (1 << bit);
    }
}
