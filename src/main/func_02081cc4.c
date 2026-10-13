/* func_02081cc4 @ 0x02081cc4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7c];
    unsigned short unk_7C;
} UnkStruct_02081cc4;

void func_02081cc4(UnkStruct_02081cc4 *p)
{
    p->unk_7C = (p->unk_7C & ~1) | 1;
}
