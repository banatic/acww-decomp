/* func_ov068_02271de8 @ 0x02271de8, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *self, int value);
extern int func_0200d554(void *self, int a, int b);

struct UnkStruct_02271de8 {
    char pad_00[0x2d0];
    void *unk_2D0;
    char pad_2D4[0x51c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

void func_ov068_02271de8(struct UnkStruct_02271de8 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d554(self, 9, -1);
    }
}
