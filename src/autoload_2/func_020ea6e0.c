/* func_020ea6e0 @ 0x020ea6e0, 0xac bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];

void func_020ea6e0(int *v, int angle)
{
    int i = ((unsigned short) angle >> 4) << 1;
    short c = FX_SinCosTable_[i];
    int z = v[2];
    short s = FX_SinCosTable_[i + 1];
    int x = v[0];
    int sx = (int) (((long long) s * x + 0x800) >> 12);

    v[0] = (int) (((long long) c * z + 0x800) >> 12) + sx;
    v[2] = (int) (((long long) s * z + 0x800) >> 12) - (int) (((long long) c * x + 0x800) >> 12);
}
