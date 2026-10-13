/* func_ov094_02299ad0 @ 0x02299ad0, 0x32 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299ad0 {
    unsigned char pad_00[0xf];
    unsigned char unk_0F;
    unsigned char unk_10;
};

extern void func_ov094_02299f88(struct UnkStruct_02299ad0 *self);
extern void func_ov094_02299f64(struct UnkStruct_02299ad0 *self);
extern void func_ov094_02299f40(struct UnkStruct_02299ad0 *self);

void func_ov094_02299ad0(struct UnkStruct_02299ad0 *self)
{
    if (self->unk_10 != self->unk_0F) {
        self->unk_0F = self->unk_10;
        func_ov094_02299f88(self);
        switch (self->unk_0F) {
            case 0:
                func_ov094_02299f64(self);
                break;
            case 1:
                func_ov094_02299f40(self);
                break;
        }
    }
}
