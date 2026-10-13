/* func_ov134_02299a90 @ 0x02299a90, 0x60 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a90 {
    char pad_00[0x64];
    int unk_64;
};

extern unsigned short data_021fbe40;

extern void func_ov134_02299a14(struct UnkStruct_02299a90 *self);
extern void func_ov134_02299a00(struct UnkStruct_02299a90 *self);
extern void func_ov002_0220a4c8(void *addr);

void func_ov134_02299a90(struct UnkStruct_02299a90 *self)
{
    int old = self->unk_64;
    unsigned short flags = data_021fbe40;

    if ((flags & 0x40) != 0) {
        self->unk_64 = old - 4;
        if (self->unk_64 < 0x20) {
            self->unk_64 = 0x20;
        }
    } else if ((flags & 0x80) != 0) {
        self->unk_64 = old + 4;
        if (self->unk_64 > 0xa0) {
            self->unk_64 = 0xa0;
        }
    }
    if (old != self->unk_64) {
        func_ov134_02299a14(self);
        func_ov134_02299a00(self);
        func_ov002_0220a4c8((char *) self + 0x18);
    }
}
