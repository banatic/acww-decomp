/* func_ov052_022618a8 @ 0x022618a8, 0x30 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019c6c(void *p, int a, unsigned short b);
extern unsigned short data_020c80f8;

struct UnkStruct_022618a8 {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x1B7];
    unsigned short unk_71C;
};

int func_ov052_022618a8(struct UnkStruct_022618a8 *self)
{
    func_02019c6c(&self->unk_564, 1, self->unk_71C);
    self->unk_71C = data_020c80f8;
    return 1;
}
