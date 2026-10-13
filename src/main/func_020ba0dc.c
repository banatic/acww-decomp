/* func_020ba0dc @ 0x020ba0dc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ba0dc {
    unsigned int unk_00;
    unsigned char unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

extern unsigned int func_02002a88(unsigned int, unsigned char, unsigned int, unsigned int, unsigned int);

unsigned int func_020ba0dc(struct UnkStruct_020ba0dc *p)
{
    return func_02002a88(p->unk_00, p->unk_04, p->unk_08, p->unk_0C, p->unk_10);
}
