/* func_ov142_02299830 @ 0x02299830, 0xd8 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299668(void *self, int arg);
extern void func_ov142_0229a4d4(void *self, int _x);
extern void func_ov142_02299a54(void *self);
extern void func_ov002_0220a4c8(void *addr);

struct UnkStruct_02299830 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    char pad_A8[0x14c - 0xa8];
};

void func_ov142_02299830(struct UnkStruct_02299830 *self)
{
    int old = self->unk_9C;

    if (func_ov142_02299668(self, 0x1000) != 0) {
        int low = self->unk_9C & 0xf;
        if (low != 0) {
            self->unk_9C -= low;
        } else {
            self->unk_9C -= 0x10;
        }
        if (self->unk_9C < 0) {
            self->unk_9C = 0;
        }
    } else {
        int low = self->unk_9C & 0xf;
        if (low != 0) {
            self->unk_9C += 0x10 - low;
        } else {
            self->unk_9C += 0x10;
        }
        if (self->unk_9C > self->unk_A4) {
            self->unk_9C = self->unk_A4;
        }
    }

    if (old != self->unk_9C) {
        func_ov142_0229a4d4(self, self->unk_9C);
        self->unk_A0 = self->unk_9C;
        func_ov142_02299a54(self);
        func_ov002_0220a4c8((char *) self + 0x14c);
    }
}