/* func_ov103_0229c964 @ 0x0229c964, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *p);
extern int func_ov002_02209d7c(void *p);

struct UnkStruct_0229c964 {
    char pad_00[0x225c];
    char sub;
    char pad_225D[0x93b];
    int unk_2B98;
    int unk_2B9C;
};

void func_ov103_0229c964(struct UnkStruct_0229c964 *self)
{
    self->unk_2B98 = func_ov002_02209d84(&self->sub);
    self->unk_2B9C = func_ov002_02209d7c(&self->sub);
}
