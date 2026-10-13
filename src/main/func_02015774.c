/* func_02015774 @ 0x02015774, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x86];
    unsigned char unk_86;
    unsigned char pad_87;
    unsigned char unk_88;
    unsigned char pad_89[0x13];
    unsigned int unk_9C;
    unsigned int unk_A0;
} UnkStruct_02015774;

void func_02015774(UnkStruct_02015774 *s, unsigned char a, unsigned int b, unsigned int c, unsigned char d)
{
    s->unk_86 = a;
    s->unk_9C = b;
    s->unk_A0 = c;
    s->unk_88 = d;
}
