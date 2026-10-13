/* func_0209bd30 @ 0x0209bd30, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
} UnkStruct_0209bd30;

void func_0209bd30(UnkStruct_0209bd30 *s, unsigned char a, unsigned short *h, unsigned char b)
{
    s->unk_0A = a;
    s->unk_08 = *h;
    s->unk_0B = (s->unk_0B & ~0x1f) | (b & 0x1f);
}
