/* func_0203f984 @ 0x0203f984, 0x5c bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int p1, int p2, int p3);

int func_0203f984(int a)
{
    int r;
    r = FX_Div((a & 0xffff) << 12, 0x10000000, 0xffff);
    return (int) (((long long) r * 0xc4ec6LL + 0x800LL) >> 12);
}
