/* func_02081878 @ 0x02081878, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short flags;
} UnkStruct_02081878;

void func_02081878(UnkStruct_02081878 *s)
{
    s->flags &= ~0x20;
}
