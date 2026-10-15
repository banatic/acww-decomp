/* func_ov142_02299b08 @ 0x02299b08, 0x8c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

struct UnkStruct_02299b08 {
    char pad_00[0xa8];
    int unk_A8;
};

extern void func_ov142_02299a80(struct UnkStruct_02299b08 *s);
extern void func_ov142_02299ab8(struct UnkStruct_02299b08 *s);
extern void func_ov002_0220a4c8(void *receiver);

void func_ov142_02299b08(struct UnkStruct_02299b08 *self)
{
    int old = self->unk_A8;
    if (data_021fbe40 & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (data_021fbe40 & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 90) {
            self->unk_A8 = 90;
        }
    }
    if (old != self->unk_A8) {
        func_ov142_02299a80(self);
        func_ov142_02299ab8(self);
        func_ov002_0220a4c8((char *) self + 0x14c);
    }
}
