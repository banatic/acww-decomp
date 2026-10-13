/* func_0200364c @ 0x0200364c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003658(unsigned char value);

struct UnkStruct_0200364c {
    unsigned char pad_00[0x0E];
    unsigned char unk_0E;
};

void func_0200364c(struct UnkStruct_0200364c *s)
{
    func_02003658(s->unk_0E);
}
