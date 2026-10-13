/* func_ov003_02211da0 @ 0x02211da0, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Dst {
    char tag;
    int x;
    int y;
    int z;
};

struct Src {
    int x;
    int y;
    int z;
};

void func_ov003_02211da0(struct Dst *dst, char tag, const struct Src *src)
{
    dst->tag = tag;
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
