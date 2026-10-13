/* func_020eabc8 @ 0x020eabc8, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

void func_020eabc8(int *v, int scale)
{
    v[0] = (int) (((long long) v[0] * scale + 0x800) >> 12);
    v[1] = (int) (((long long) v[1] * scale + 0x800) >> 12);
    v[2] = (int) (((long long) v[2] * scale + 0x800) >> 12);
}
