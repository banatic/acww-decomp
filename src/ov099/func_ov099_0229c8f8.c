/* func_ov099_0229c8f8 @ 0x0229c8f8, 0x30 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *p);
extern int func_ov002_02209d7c(void *p);

struct UnkStruct_0229c8f8 {
    char pad_00[0x225c];
    char unk_225C;
    char pad_225D[0x27f8 - 0x225c - 1];
    int unk_27F8;
    int unk_27FC;
};

void func_ov099_0229c8f8(struct UnkStruct_0229c8f8 *self)
{
    self->unk_27F8 = func_ov002_02209d84(&self->unk_225C);
    self->unk_27FC = func_ov002_02209d7c(&self->unk_225C);
}
