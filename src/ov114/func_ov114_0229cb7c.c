/* func_ov114_0229cb7c @ 0x0229cb7c, 0x68 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x127c];
    int unk_127C;
    char pad_1280[4];
    int unk_1284;
    char pad_1288[4];
    int unk_128C;
    char pad_1290[8];
    int unk_1298;
} UnkStruct_0229cb7c;

int func_ov114_0229cb7c(UnkStruct_0229cb7c *self, int value)
{
    int clamped;
    int counter;
    clamped = value;
    if (clamped < 0) {
        clamped = 0;
    }
    if (clamped >= self->unk_1298) {
        clamped = self->unk_1298;
    }
    self->unk_127C = clamped;
    counter = self->unk_128C;
    self->unk_1284 = 0x22 - clamped;
    self->unk_128C = 0;
    while (self->unk_1284 < 8) {
        self->unk_1284 += 0x1b;
        self->unk_128C++;
    }
    return (counter == self->unk_128C) ? 0 : 1;
}
