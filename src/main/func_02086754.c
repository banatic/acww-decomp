/* func_02086754 @ 0x02086754, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short f;
} UnkStruct_02086754;
typedef struct {
    unsigned char pad_00[0x3e];
    unsigned short f;
} UnkStruct_02086754_2;
void func_02086754(UnkStruct_02086754_2 *dst, UnkStruct_02086754 *src)
{
    dst->f = src->f;
}
