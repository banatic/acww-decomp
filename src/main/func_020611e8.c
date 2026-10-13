/* func_020611e8 @ 0x020611e8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_020611e8(unsigned char *base, unsigned int *out)
{
    if (out) {
        *out = ((unsigned int) base[0x44e] << 30) >> 31;
    }
    return base + 0x44a;
}
