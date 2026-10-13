/* func_020871cc @ 0x020871cc, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short f;
} UnkStruct_020871cc;
typedef struct {
    unsigned char pad_00[0x1e];
    unsigned short f;
} UnkStruct_020871cc_2;
void func_020871cc(UnkStruct_020871cc *dst, UnkStruct_020871cc_2 *src)
{
    dst->f = src->f;
}
