/* func_ov143_0229ae64 @ 0x0229ae64, 0x1e bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ae64 {
    char pad_00[0x8c];
    char flag;
};

extern void func_ov143_0229a98c(struct UnkStruct_0229ae64 *this);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229ae64 *this, unsigned char arg1);

int func_ov143_0229ae64(struct UnkStruct_0229ae64 *this)
{
    func_ov143_0229a98c(this);
    this->flag = 0;
    func_ov002_022080a0(this, 0);
    return 1;
}
