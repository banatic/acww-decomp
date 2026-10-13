/* func_ov112_0229fb7c @ 0x0229fb7c, 0x10 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fb7c {
    char pad_00[0xb7];
    char unk_B7;
};
extern void func_ov112_0229fe60(struct UnkStruct_0229fb7c *p, int n);

void func_ov112_0229fb7c(struct UnkStruct_0229fb7c *p, char c)
{
    p->unk_B7 = c;
    func_ov112_0229fe60(p, 0x20);
}
