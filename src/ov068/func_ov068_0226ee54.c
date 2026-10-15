/* func_ov068_0226ee54 @ 0x0226ee54, 0xb0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);
extern int func_ov003_0221a35c(void *self, int n);

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C; // 0x5c
    int unk_60; // 0x60
    int unk_64; // 0x64
    unsigned char pad_68[0xa8 - 0x68];
    int unk_A8; // 0xa8
    unsigned char pad_AC[0x26c - 0xac];
    int unk_26C; // 0x26c
    int unk_270; // 0x270
    unsigned char pad_274[0x314 - 0x274];
    int unk_314; // 0x314
    int unk_318; // 0x318
    unsigned char pad_31C[0x37c - 0x31c];
    int unk_37C; // 0x37c
    int unk_380; // 0x380
    int unk_384; // 0x384
    unsigned char pad_388[0x399 - 0x388];
    unsigned char unk_399; // 0x399
} UnkStruct_0226ee54;

void func_ov068_0226ee54(UnkStruct_0226ee54 *self)
{
    int ret;
    int limit;
    unsigned char old;

    self->unk_270 = self->unk_26C;
    self->unk_5C = self->unk_5C + self->unk_314;
    self->unk_64 = self->unk_64 + self->unk_318;

    ret = FX_Div(0, 0x02710000);

    self->unk_A8 = self->unk_A8 + (ret + 0xdf);
    self->unk_60 = self->unk_60 - self->unk_A8;

    if (self->unk_A8 >= 0) {
        limit = self->unk_380 - 0x200;
        if (self->unk_60 < limit) {
            self->unk_60 = limit;
            func_ov003_0221a35c(self, 10);
        }
    }

    old = self->unk_399;
    self->unk_399 = old + 1;
    if (old >= 0x10) {
        self->unk_5C = self->unk_37C;
        self->unk_64 = self->unk_384;
    }
}
