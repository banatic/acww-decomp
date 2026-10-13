/* func_020653b0 @ 0x020653b0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[14];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_020653b0;

extern void func_020654d8(void *ptr, int a, int b);

void func_020653b0(UnkStruct_020653b0 *s)
{
    s->unk_04 = 0;
    s->unk_14 = 2;
    s->unk_1C = 0;
    s->unk_20 = 0x800;
    s->unk_18 = 0;
    func_020654d8((char *) s + 0x24, 0, 0xB4);
}
