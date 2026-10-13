/* func_ov002_02209eb8 @ 0x02209eb8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e600(void *self);
extern int func_0208aef0(void *self);

struct UnkStruct_02209eb8 {
    char pad_00[0x20];
    int unk_20;
};

void func_ov002_02209eb8(struct UnkStruct_02209eb8 *self)
{
    int save;

    func_0208e600(self);
    save = self->unk_20;
    if (save + func_0208aef0(self) > 0xe0) {
        self->unk_20 = self->unk_20 - 0x100;
        func_0208e600(self);
        self->unk_20 = save;
    }
}
