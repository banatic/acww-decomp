/* music_list_view: 4 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_02299694 @ 0x02299694, 0x40 bytes, Thumb
 * func_ov144_02299680 @ 0x02299680, 0x12 bytes, Thumb
 * func_ov144_02299670 @ 0x02299670, 0xe bytes, Thumb
 * func_ov144_02299660 @ 0x02299660, 0xe bytes, Thumb
 */

typedef struct UnkStruct_02299694 {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
    char pad_A4[0x14];
    short unk_B8;
} UnkStruct_02299694;

typedef struct {
    char pad_00[0xb4];
    unsigned short unk_B4;
} UnkStruct_02299680;

struct UnkStruct_02299670 {
    char pad_00[0xb4];
    unsigned short unk_B4;
};

struct func_ov144_02299660_unk {
    unsigned char pad_00[0xb4];
    unsigned short unk_B4;
};

extern void func_ov144_02299e6c(UnkStruct_02299694 *self, int n);
extern void func_ov144_0229a378(UnkStruct_02299694 *self);

void func_ov144_02299694(UnkStruct_02299694 *self, int param)
{
    int n = param - 3;
    int upper = self->unk_B8 - 8;
    if (upper < 0) {
        upper = 0;
    }
    if (n < 0) {
        n = 0;
    } else if (n > upper) {
        n = upper;
    }
    func_ov144_02299e6c(self, n << 4);
    self->unk_A0 = self->unk_9C;
    func_ov144_0229a378(self);
}

int func_ov144_02299680(UnkStruct_02299680 *p, unsigned short mask)
{
    if (p->unk_B4 & mask) {
        return 1;
    }
    return 0;
}

void func_ov144_02299670(struct UnkStruct_02299670 *s, unsigned short v)
{
    s->unk_B4 |= v;
}

void func_ov144_02299660(struct func_ov144_02299660_unk *self, unsigned short mask)
{
    self->unk_B4 &= ~mask;
}
