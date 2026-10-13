/* func_020103c0 @ 0x020103c0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0c8c];
    int unk_C8C;
    unsigned short unk_C90;
} UnkStruct_020103c0;

int func_020103c0(UnkStruct_020103c0 *s, unsigned short *b)
{
    if (s->unk_C8C == 2) {
        s->unk_C8C = 0;
        s->unk_C90 = *b;
        return 1;
    }
    return 0;
}
