/* func_020ea634 @ 0x020ea634, 0xac bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];

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
