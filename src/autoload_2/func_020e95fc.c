/* func_020e95fc @ 0x020e95fc, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int MTX_RotZ43_(int a, int b, int c);
extern short FX_SinCosTable_[];

int func_020e95fc(int a, int b)
{
    int v = ((unsigned short) b) >> 4;
    return MTX_RotZ43_(a, FX_SinCosTable_[2 * v], FX_SinCosTable_[2 * v + 1]);
}
