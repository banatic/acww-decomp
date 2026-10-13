/* func_ov142_02299fbc @ 0x02299fbc, 0x9e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a6d8(void *p);
extern int func_ov002_02209eec(void *p);

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xc0 - 0xa4];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc1];
    char unk_E8;
} UnkStruct_02299fbc;

int func_ov142_02299fbc(UnkStruct_02299fbc *self)
{
    int v;
    int a;
    int b;
    int e;

    v = func_ov142_0229a6d8(self);
    if (v == 0) {
        return 0;
    }
    if (v > 9) {
        v = 9;
    }
    a = func_ov002_02209eec(&self->unk_E8);
    if (a < 0x20) {
        a = 0x20;
    }
    if (a >= 0xa0) {
        a = 0x9f;
    }
    b = self->unk_A0 & 0xf;
    e = (a - (0x20 - b)) >> 4;
    if (e >= v) {
        e = v - 1;
    }
    self->unk_C0 = (unsigned char) (e + 9);

    if (b == 0) {
        goto done;
    }
    if (e == 0) {
        self->unk_A0 = self->unk_A0 - b;
        goto done;
    }
    if (e != v - 1) {
        goto done;
    }
    self->unk_C0 = (unsigned char) (self->unk_C0 - 1);
    self->unk_A0 = self->unk_A0 + (0x10 - (self->unk_A0 & 0xf));

done:
    return 1;
}
