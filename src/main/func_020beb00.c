/* func_020beb00 @ 0x020beb00, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[12];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
} S_020beb00;

void func_020beb00(S_020beb00 *s, unsigned int a, unsigned int b, unsigned int c, unsigned char d)
{
    s->unk_0C = a;
    s->unk_10 = b;
    s->unk_14 = c;
    s->unk_18 = d;
}
