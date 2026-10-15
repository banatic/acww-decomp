/* func_ov146_02299ba8 @ 0x02299ba8, 0x8c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov146_02299b1c(void *p);
extern void func_ov146_02299b58(void *p);
extern void func_ov002_0220a4c8(void);

struct UnkStruct_02299ba8 {
    char pad_00[0x98];
    int unk_98;
};

void func_ov146_02299ba8(struct UnkStruct_02299ba8 *self)
{
    int old = self->unk_98;
    unsigned short flags = data_021fbe40;

    if (flags & 0x40) {
        self->unk_98 -= 4;
        if (self->unk_98 < 0) {
            self->unk_98 = 0;
        }
    } else if (flags & 0x80) {
        self->unk_98 += 4;
        if (self->unk_98 > 0x50) {
            self->unk_98 = 0x50;
        }
    }

    if (old != self->unk_98) {
        func_ov146_02299b1c(self);
        func_ov146_02299b58(self);
        asm {
            ldr r0, =0x1fb4
            add r0, self, r0
        }
        func_ov002_0220a4c8();
    }
}
