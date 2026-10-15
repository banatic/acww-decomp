/* func_020159f0 @ 0x020159f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
    char unk_68[0x44];
    char unk_AC;
    char unk_AD;
} UnkStruct_020159f0;

extern void func_0201599c(UnkStruct_020159f0 *s, char *buf);

void func_020159f0(UnkStruct_020159f0 *s)
{
    s->unk_64 = 12;
    s->unk_AC = 0;
    s->unk_AD = 0;
    func_0201599c(s, s->unk_68);
}
