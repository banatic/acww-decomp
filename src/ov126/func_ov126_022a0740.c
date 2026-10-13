/* func_ov126_022a0740 @ 0x022a0740, 0x28 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a0740 {
    char pad_00[0xa9];
    unsigned char b1;
    unsigned char b2;
};

extern int func_ov126_0229f7c8(struct UnkStruct_022a0740 *p, int x);

int func_ov126_022a0740(struct UnkStruct_022a0740 *p)
{
    if ((func_ov126_0229f7c8(p, 4) == 0) || (p->b1 == p->b2)) {
        return 0;
    }
    return 1;
}
