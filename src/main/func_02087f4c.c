/* func_02087f4c @ 0x02087f4c, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087f4c;
typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087f4c_2;
void func_02087f4c(UnkStruct_02087f4c *dst, UnkStruct_02087f4c_2 *src)
{
    dst->a = src->x;
    dst->b = src->y;
}
