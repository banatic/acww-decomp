/* func_ov004_02244f48 @ 0x02244f48, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern long FX_MulFunc(long, long);
extern short FX_SinCosTable_[];
typedef struct {
    long x, y, z;
} UnkStruct_02244f48;
void func_ov004_02244f48(UnkStruct_02244f48 *out, UnkStruct_02244f48 *base, int ang, long r)
{
    long z;
    int k;
    k = ((int) (unsigned short) ang >> 4) * 2;
    z = base->z + FX_MulFunc(r, FX_SinCosTable_[k + 1]);
    out->x = base->x + FX_MulFunc(r, FX_SinCosTable_[k]);
    out->y = 0;
    out->z = z;
}
