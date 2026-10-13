/* func_ov121_02299a3c @ 0x02299a3c, 0xe bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a3c {
    char pad_00[0xa2];
    unsigned short unk_A2;
};

void func_ov121_02299a3c(struct UnkStruct_02299a3c *p, unsigned short mask)
{
    p->unk_A2 &= ~mask;
}
