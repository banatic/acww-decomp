/* func_ov135_0229c564 @ 0x0229c564, 0xe bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c564 {
    char pad_00[0x92];
    unsigned short flags;
};

void func_ov135_0229c564(struct UnkStruct_0229c564 *p, unsigned short val)
{
    p->flags |= val;
}
