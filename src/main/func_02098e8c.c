/* func_02098e8c @ 0x02098e8c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098f70(int);

struct UnkStruct_02098e8c {
    char pad_00[0xA6C];
    unsigned int unk_A6C;
};

int func_02098e8c(struct UnkStruct_02098e8c *param0, int param1)
{
    int shift = param1 << 1;
    if (func_02098f70(param1) == 1) {
        return (param0->unk_A6C >> shift) & 3;
    }
    return 0;
}
