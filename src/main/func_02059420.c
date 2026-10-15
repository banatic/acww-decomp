/* func_02059420 @ 0x02059420, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205967c(void *obj, void *field);
extern unsigned char data_020cbb00[];
extern unsigned char data_021c9348;

struct UnkStruct_02059420 {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x68 - 0x64];
    int unk_68;
    unsigned char pad_6C[0x90 - 0x6c];
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9C;
    int unk_A0;
    int unk_A4;
    unsigned char pad_A8[0xd4 - 0xa8];
    unsigned char d4;
    unsigned short d6;
};

void func_02059420(void *self_raw)
{
    struct UnkStruct_02059420 *self;
    int d, v1, v2, v3;

    self = (struct UnkStruct_02059420 *) self_raw;
    func_0205967c(self, &self->unk_60);
    self->d6++;
    if (self->d6 < data_020cbb00[self->d4]) {
        return;
    }
    self->d4++;
    d = data_021c9348;

    v1 = (self->unk_9C - self->unk_60) / d;
    if (v1 < 0) {
        v1 = -v1;
    }
    self->unk_90 = v1;

    v2 = self->unk_A0 / d;
    if (v2 < 0) {
        v2 = -v2;
    }
    self->unk_94 = v2;

    v3 = (self->unk_A4 - self->unk_68) / d;
    if (v3 < 0) {
        v3 = -v3;
    }
    self->unk_98 = v3;
}
