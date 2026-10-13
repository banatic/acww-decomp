/* func_020871d4 @ 0x020871d4, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short f;
} UnkStruct_020871d4;
typedef struct {
    unsigned char pad_00[0x1e];
    unsigned short f;
} UnkStruct_020871d4_2;
void func_020871d4(UnkStruct_020871d4_2 *dst, UnkStruct_020871d4 *src)
{
    dst->f = src->f;
}
