/* pockets_wallet_2: 3 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_02299ad0 @ 0x02299ad0, 0x32 bytes, Thumb
 * func_ov094_02299acc @ 0x02299acc, 0x4 bytes, Thumb
 * func_ov094_02299ac4 @ 0x02299ac4, 0x6 bytes, Thumb
 */

struct UnkStruct_02299ad0 {
    unsigned char pad_00[0xf];
    unsigned char unk_0F;
    unsigned char unk_10;
};

typedef struct {
    unsigned char pad_00[16];
    unsigned char unk_10;
} UnkStruct_02299ac4;

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

void func_ov094_02299acc(unsigned char *p0, int p1)
{
    p0[16] = p1;
}

void func_ov094_02299ac4(UnkStruct_02299ac4 *p)
{
    p->unk_10 = 2;
}
