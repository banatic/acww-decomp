/* func_ov126_022a0728 @ 0x022a0728, 0x18 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov126_0229f7a8(void *p, int arg);

struct UnkStruct_022a0728 {
    char pad_00[0xa9];
    unsigned char b1;
    unsigned char b2;
};

void func_ov126_022a0728(struct UnkStruct_022a0728 *p)
{
    p->b1 = 0;
    p->b2 = 0;
    func_ov126_0229f7a8(p, 4);
}
