/* func_020bee60 @ 0x020bee60, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int pad_04;
    unsigned char unk_08;
    unsigned char unk_09;
} UnkStruct_020bee60;

void func_020bee60(UnkStruct_020bee60 *s, unsigned int value)
{
    if (value != s->unk_00) {
        s->unk_08 = 0;
        s->unk_09 = 1;
        s->unk_00 = value;
    }
}
