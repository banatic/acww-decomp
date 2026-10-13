/* func_ov002_0220880c @ 0x0220880c, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0220880c {
    int unk_00;
    int unk_04;
    int unk_08;
} *self;

int func_ov002_0220880c(struct UnkStruct_0220880c *self)
{
    int f8 = self->unk_08;
    if (f8 == 0) {
        return 1;
    }
    if (f8 > self->unk_04) {
        self->unk_08 = f8 - self->unk_04;
    } else {
        self->unk_08 = 0;
    }
    return 0;
}
