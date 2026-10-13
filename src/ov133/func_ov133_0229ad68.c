/* func_ov133_0229ad68 @ 0x0229ad68, 0xe bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ad68 {
    char pad_00[0x98];
    unsigned short unk_98;
};

void func_ov133_0229ad68(struct UnkStruct_0229ad68 *p, unsigned short mask)
{
    unsigned short tmp;

    tmp = p->unk_98;
    p->unk_98 = tmp & ~mask;
}
