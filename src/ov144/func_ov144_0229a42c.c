/* func_ov144_0229a42c @ 0x0229a42c, 0x8c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a42c {
    char pad_00[0xa8];
    int unk_A8;
};

extern unsigned short data_021fbe40;
extern void func_ov144_0229a3a4(struct UnkStruct_0229a42c *);
extern void func_ov144_0229a3dc(struct UnkStruct_0229a42c *);
extern void func_ov002_0220a4c8(void *);

void func_ov144_0229a42c(struct UnkStruct_0229a42c *self)
{
    int original = self->unk_A8;
    unsigned short flags = data_021fbe40;

    if (flags & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (flags & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 0x78) {
            self->unk_A8 = 0x78;
        }
    }

    if (original != self->unk_A8) {
        func_ov144_0229a3a4(self);
        func_ov144_0229a3dc(self);
        func_ov002_0220a4c8((char *) self + 0x128);
    }
}
