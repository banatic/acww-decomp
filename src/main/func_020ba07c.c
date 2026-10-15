/* func_020ba07c @ 0x020ba07c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002bd0(void *, unsigned char, unsigned char, unsigned char, unsigned char);

struct UnkStruct_020ba07c {
    void *unk_00;
    unsigned char unk_04;
    unsigned int unk_08;
};

void func_020ba07c(struct UnkStruct_020ba07c *arg)
{
    unsigned char mask = (unsigned char) arg->unk_08;
    func_02002bd0(arg->unk_00, arg->unk_04, mask, mask, mask);
}
