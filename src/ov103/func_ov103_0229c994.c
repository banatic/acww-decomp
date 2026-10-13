/* func_ov103_0229c994 @ 0x0229c994, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *ptr);
extern int func_ov002_02209f14(void *ptr);

struct struct_ov103_0229c994 {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x923];
    int unk_2B98;
    int unk_2B9C;
};

void func_ov103_0229c994(struct struct_ov103_0229c994 *self)
{
    self->unk_2B98 = func_ov002_02209f3c(&self->unk_2274) - 2;
    self->unk_2B9C = func_ov002_02209f14(&self->unk_2274) - 4;
}
