/* func_ov099_0229c928 @ 0x0229c928, 0x34 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(int *);
extern int func_ov002_02209f14(int *);

struct UnkStruct_0229c928 {
    char pad_00[0x2274];
    int sub;
    char pad_2278[0x580];
    int unk_27F8;
    int unk_27FC;
};

void func_ov099_0229c928(struct UnkStruct_0229c928 *self)
{
    self->unk_27F8 = func_ov002_02209f3c(&self->sub) - 2;
    self->unk_27FC = func_ov002_02209f14(&self->sub) - 4;
}
