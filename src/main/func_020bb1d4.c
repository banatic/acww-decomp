/* func_020bb1d4 @ 0x020bb1d4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020bb1d4(int unused, unsigned char *p)
{
    int rem;
    int t;
    int q;

    rem = (p[2] + 6) % 24;
    if (rem >= 12) {
        return 0x100;
    }

    t = rem * 60;
    q = ((t + p[1]) * 0x68000) / 0x2d0;

    return (unsigned) q << 4 >> 16;
}
