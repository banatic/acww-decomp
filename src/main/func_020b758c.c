/* func_020b758c @ 0x020b758c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b758c {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_020b758c(struct UnkStruct_020b758c *src, struct UnkStruct_020b758c *dst)
{
    if (dst != 0) {
        dst->unk_00 = src->unk_00;
        dst->unk_04 = src->unk_04;
        dst->unk_08 = src->unk_08;
    }
    return (src->unk_00 != 0xffed4000);
}
