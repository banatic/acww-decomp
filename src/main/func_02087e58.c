/* func_02087e58 @ 0x02087e58, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long a;
    unsigned long b;
} UnkStruct_02087e58;
typedef struct {
    unsigned long x;
    unsigned char pad_04[4];
    unsigned long y;
} UnkStruct_02087e58_2;
void func_02087e58(UnkStruct_02087e58 *dst, UnkStruct_02087e58_2 *src)
{
    dst->a = src->x;
    dst->b = src->y;
}
