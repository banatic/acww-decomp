/* func_020bf924 @ 0x020bf924, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bf924 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x4c - 0x28];
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
};

void func_020bf924(struct UnkStruct_020bf924 *p)
{
    p->unk_00 = 0xd;
    p->unk_04 = 0;
    p->unk_08 = 0x34;
    p->unk_0C = 0x2e;
    p->unk_24 = 5;
    p->unk_4C = 0x1000;
    p->unk_50 = 0x1000;
    p->unk_54 = 0;
}
