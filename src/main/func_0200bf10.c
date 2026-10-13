/* func_0200bf10 @ 0x0200bf10, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2e4];
    unsigned char unk_2E4;
    unsigned char pad_2E5[0x7d4 - 0x2e4 - 1];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
} UnkStruct_0200bf10;

extern unsigned char data_020c7600[];
extern void func_0200c9a8(UnkStruct_0200bf10 *s, unsigned char val, int a, int b);

void func_0200bf10(UnkStruct_0200bf10 *s)
{
    unsigned char *p = &s->unk_7D4;
    unsigned char *q = p + 1;
    if (*q != 0) {
        *q = *q - 1;
    }
    if (s->unk_2E4 != 0) {
        return;
    }
    if (*q != 0) {
        return;
    }
    func_0200c9a8(s, data_020c7600[*p - 1], 5, -1);
}
