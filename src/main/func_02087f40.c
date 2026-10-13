/* func_02087f40 @ 0x02087f40, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087f40;
typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087f40_2;
void func_02087f40(UnkStruct_02087f40 *src, UnkStruct_02087f40_2 *dst)
{
    dst->x = src->a;
    dst->y = src->b;
}
