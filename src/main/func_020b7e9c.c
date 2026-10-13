/* func_020b7e9c @ 0x020b7e9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b7e9c {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
};

void func_020b7e9c(struct UnkStruct_020b7e9c *p, unsigned char param)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_00 = 0xffed4000;
    p->unk_18 = 0;
    p->unk_19 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_14 = 0;
    p->unk_1A = param;
}
