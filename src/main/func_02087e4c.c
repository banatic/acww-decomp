/* func_02087e4c @ 0x02087e4c, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087e4c;
typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087e4c_2;
void func_02087e4c(UnkStruct_02087e4c *src, UnkStruct_02087e4c_2 *dst)
{
    dst->x = src->a;
    dst->y = src->b;
}
