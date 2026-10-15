/* func_020e9684 @ 0x020e9684, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_RotX43_(int a, int b, int c);
extern short FX_SinCosTable_[];

void func_020e9684(int a, int b)
{
    int idx = ((unsigned short) b) >> 4;
    int i1 = idx * 2;
    int i2 = i1 + 1;

    MTX_RotX43_(a, FX_SinCosTable_[i1], FX_SinCosTable_[i2]);
}
