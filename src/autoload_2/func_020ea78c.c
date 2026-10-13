/* func_020ea78c @ 0x020ea78c, 0xac bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];

typedef struct {
    int unk_00;
    int y;
    int x;
} Vec;

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
