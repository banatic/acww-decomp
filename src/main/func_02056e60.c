/* func_02056e60 @ 0x02056e60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int __arm FX_Div(unsigned int, unsigned int);

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned int unk_38;
} UnkStruct_02056e60;

void func_02056e60(UnkStruct_02056e60 *s, unsigned int size)
{
    s->unk_34 = 0;
    if (size == 0) {
        s->unk_38 = 0;
    } else {
        s->unk_38 = FX_Div(0x1000, size << 12);
    }
}
