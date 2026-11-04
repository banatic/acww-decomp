/* matrix: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9714 @ 0x020e9714, 0x30 bytes, ARM
 * func_020e96c8 @ 0x020e96c8, 0x4c bytes, ARM
 * func_020e9684 @ 0x020e9684, 0x44 bytes, ARM
 * func_020e9640 @ 0x020e9640, 0x44 bytes, ARM
 * func_020e95fc @ 0x020e95fc, 0x44 bytes, ARM
 */

extern void MTX_Concat43(void *, void *, void *);
extern void MTX_RotX43_(int a, int b, int c);
extern short FX_SinCosTable_[];
extern void MTX_RotY43_(int, int, int);
extern void MTX_RotZ43_(int a, int b, int c);

void func_020e95fc(int a, int b);

void func_020e9714(void *param, int argument1)
{
    char local[0x30];
    func_020e95fc((int) local, argument1);
    MTX_Concat43(local, param, param);
}

void func_020e96c8(int *r0, int r1, int r2, int r3)
{
    r0[0] = 0x1000;
    r0[1] = 0;
    r0[2] = 0;
    r0[3] = 0;
    r0[4] = 0x1000;
    r0[5] = 0;
    r0[6] = 0;
    r0[7] = 0;
    r0[8] = 0x1000;
    r0[9] = r1;
    r0[10] = r2;
    r0[11] = r3;
}

void func_020e9684(int a, int b)
{
    int idx = ((unsigned short) b) >> 4;
    int i1 = idx * 2;
    int i2 = i1 + 1;

    MTX_RotX43_(a, FX_SinCosTable_[i1], FX_SinCosTable_[i2]);
}

void func_020e9640(int a, int b)
{
    int idx = ((unsigned short) b) >> 4;
    short s1 = FX_SinCosTable_[idx * 2];
    short s2 = FX_SinCosTable_[idx * 2 + 1];
    MTX_RotY43_(a, s1, s2);
}

void func_020e95fc(int a, int b)
{
    int v = ((unsigned short) b) >> 4;
    MTX_RotZ43_(a, FX_SinCosTable_[2 * v], FX_SinCosTable_[2 * v + 1]);
}
