/* func_020ff434 @ 0x020ff434, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Src {
    int x;
    int y;
    int z;
    short scale;
};
struct Dst {
    int pad_00;
    int pad_04;
    int x;
    int y;
    int z;
};

void func_020ff434(struct Src *src, struct Dst *dst)
{
    dst->x += (int) (((long long) src->scale * (src->x - dst->x) + 0x800) >> 12);
    dst->y += (int) (((long long) src->scale * (src->y - dst->y) + 0x800) >> 12);
    dst->z += (int) (((long long) src->scale * (src->z - dst->z) + 0x800) >> 12);
}
