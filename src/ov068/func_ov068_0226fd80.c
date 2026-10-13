/* func_ov068_0226fd80 @ 0x0226fd80, 0x80 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short pad0 : 6;
    unsigned short bit6 : 1;
    unsigned short pad7 : 3;
    unsigned short bit10 : 1;
} Flags378;

typedef struct {
    char pad0[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xa8 - 0x68];
    int unk_A8;
    char pad_AC[0x274 - 0xac];
    int unk_274;
    char pad_278[0x2f0 - 0x278];
    int unk_2F0;
    int unk_2F4;
    char pad_2F8[0x378 - 0x2f8];
    Flags378 unk_378;
} UnkStruct_0226fd80;

void func_ov068_0226fd80(UnkStruct_0226fd80 *self)
{
    if (self->unk_274 & 1) {
        self->unk_A8 = 0;
    } else {
        self->unk_A8 += 0x6d;
        if (self->unk_A8 > 0x200) {
            self->unk_A8 = 0x200;
        }
    }
    self->unk_60 -= self->unk_A8;
    if (self->unk_378.bit6) {
        return;
    }
    if (self->unk_378.bit10) {
        return;
    }
    self->unk_5C += self->unk_2F0;
    self->unk_64 += self->unk_2F4;
}
