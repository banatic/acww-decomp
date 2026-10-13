/* func_020eac34 @ 0x020eac34, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

void func_020eac34(long *out, long *in, long scale)
{
    long long x, y, z;
    z = ((long long) in[2] * scale + 0x800) >> 12;
    y = ((long long) in[1] * scale + 0x800) >> 12;
    x = ((long long) in[0] * scale + 0x800) >> 12;
    out[0] = (long) x;
    out[1] = (long) y;
    out[2] = (long) z;
}
