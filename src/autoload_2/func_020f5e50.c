/* func_020f5e50 @ 0x020f5e50, 0x158 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int FX_Sqrt(int);

typedef struct {
    int x;
    int y;
    int z;
} Vec;

int func_020f5e50(Vec *p, int mode)
{
    int x, y, z;
    int sx, sy, sz;
    int ret;
    if (p == 0) {
        return 0;
    }

    switch (mode) {
        case 0:
            x = p->x;
            y = p->y;
            z = p->z + 0xc000;
            sx = (int) (((long long) x * x + 0x800) >> 12);
            sy = (int) (((long long) y * y + 0x800) >> 12);
            sz = (int) (((long long) z * z + 0x800) >> 12);
            ret = FX_Sqrt(sx + sy + sz) >> 12;
            break;
        case 1:
            sy = (int) (((long long) p->y * p->y + 0x800) >> 12);
            sz = (int) (((long long) (p->z + 0xc000) * (p->z + 0xc000) + 0x800) >> 12);
            ret = FX_Sqrt(sy + sz) >> 12;
            break;
        case 2:
            x = (p->x - 0x80000) >> 3;
            y = p->y - 0x50000;
            y >>= 2;
            sx = (int) (((long long) x * x + 0x800) >> 12);
            sy = (int) (((long long) y * y + 0x800) >> 12);
            ret = FX_Sqrt(sx + sy) >> 12;
            break;
    }
    return ret;
}
