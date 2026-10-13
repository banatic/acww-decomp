/* func_ov108_0229c918 @ 0x0229c918, 0x28 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c918 {
    char c;
};

struct UnkStruct_0229c918_2 {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0x23D4];
    struct UnkStruct_0229c918 sub;
};

extern int func_ov002_02209d84(void *);
extern int func_ov002_02209d7c(void *);

void func_ov108_0229c918(struct UnkStruct_0229c918_2 *self)
{
    self->unk_A4 = func_ov002_02209d84(&self->sub);
    self->unk_A8 = func_ov002_02209d7c(&self->sub);
}
