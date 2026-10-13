/* func_ov126_022a08c4 @ 0x022a08c4, 0x40 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051d08(void *, int);

struct UnkStruct_022a08c4 {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    char pad_A0[0xa8 - 0xa0];
    unsigned char unk_A8;
    char pad_A9[0xab - 0xa9];
    unsigned char unk_AB;
    char pad_AC[0x4248 - 0xac];
    char unk_4248;
};

void func_ov126_022a08c4(struct UnkStruct_022a08c4 *p)
{
    p->unk_98 = p->unk_AB;
    p->unk_9C = 0x28;
    p->unk_98 += (unsigned char) func_02051d08(&p->unk_4248, p->unk_A8);
}
