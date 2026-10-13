/* func_ov002_02207d00 @ 0x02207d00, 0x22 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02207d00 {
    char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char unk_CD;
    unsigned char unk_CE;
};

void func_ov002_02207d00(struct UnkStruct_02207d00 *s)
{
    s->unk_CE = 0;
    if (s->unk_CD != 0) {
        s->unk_CC = 1;
    }
    s->unk_CD = 0;
}
