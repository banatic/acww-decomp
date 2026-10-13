/* func_02097f88 @ 0x02097f88, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0a04];
    unsigned short unk_A04;
} UnkStruct_02097f88;

void func_02097f88(UnkStruct_02097f88 *s, unsigned short val)
{
    s->unk_A04 |= val;
}
