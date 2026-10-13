/* func_ov100_0229cdf4 @ 0x0229cdf4, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *addr);
extern int func_ov002_02209d7c(void *addr);

struct UnkStruct_0229cdf4 {
    char pad_00[0x225c];
    char ptr_area[0x678];
    int unk_28D4;
    int unk_28D8;
};

void func_ov100_0229cdf4(struct UnkStruct_0229cdf4 *this)
{
    this->unk_28D4 = func_ov002_02209d84(this->ptr_area);
    this->unk_28D8 = func_ov002_02209d7c(this->ptr_area);
}
