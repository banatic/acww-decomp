/* vector: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ea78c @ 0x020ea78c, 0xac bytes, ARM
 * func_020ea6e0 @ 0x020ea6e0, 0xac bytes, ARM
 * func_020ea634 @ 0x020ea634, 0xac bytes, ARM
 */

typedef struct {
    int unk_00;
    int y;
    int x;
} Vec;

extern short FX_SinCosTable_[];

void func_020ea78c(Vec *p, int angle)
{
    int a = ((unsigned short) angle) >> 4;
    short s0 = FX_SinCosTable_[a * 2];
    short s1 = FX_SinCosTable_[a * 2 + 1];
    int x = p->x;
    int y = p->y;
    long long t1 = (long long) s0 * x;
    long long t2 = (long long) s1 * y;
    long long t3 = (long long) s0 * y;
    long long t4 = (long long) s1 * x;

    p->y = (int) ((t2 + 0x800) >> 12) - (int) ((t1 + 0x800) >> 12);
    p->x = (int) ((t3 + 0x800) >> 12) + (int) ((t4 + 0x800) >> 12);
}

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

void func_020ea634(int *p, int angle)
{
    int idx = ((unsigned short) angle) >> 4;
    int i = idx * 2;
    int j = i + 1;
    short a = FX_SinCosTable_[i];
    short b = FX_SinCosTable_[j];
    int y = p[1];
    int x = p[0];

    long long t1 = (long long) a * y;
    long long t2 = (long long) b * x;
    long long t3 = (long long) a * x;
    long long t4 = (long long) b * y;

    p[0] = (int) ((t2 + 0x800) >> 12) - (int) ((t1 + 0x800) >> 12);
    p[1] = (int) ((t3 + 0x800) >> 12) + (int) ((t4 + 0x800) >> 12);
}
