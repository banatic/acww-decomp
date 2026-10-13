/* func_ov103_0229c9c8 @ 0x0229c9c8, 0x38 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229c9c8 {
    char pad_00[0x2b90];
    unsigned int src1;
    unsigned int src2;
    unsigned int dst1;
    unsigned int dst2;
};

void func_ov103_0229c9c8(struct UnkStruct_0229c9c8 *p)
{
    p->dst1 = p->src1 + data_021f6c58;
    p->dst2 = p->src2 + data_021f6c54;
}
