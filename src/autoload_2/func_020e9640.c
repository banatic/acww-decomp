/* func_020e9640 @ 0x020e9640, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];
extern void MTX_RotY43_(int, short, short, short *);

void func_020e9640(int a, int b)
{
    int idx = ((unsigned short) b) >> 4;
    short s1 = FX_SinCosTable_[idx * 2];
    short s2 = FX_SinCosTable_[idx * 2 + 1];
    MTX_RotY43_(a, s1, s2, FX_SinCosTable_);
}
