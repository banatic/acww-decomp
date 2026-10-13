/* func_ov095_0229adc4 @ 0x0229adc4, 0x98 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Entry8;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[0x44 - 0x34];
    Entry8 *arr;
} UnkStruct_0229adc4;

extern int func_ov095_0229ae5c(UnkStruct_0229adc4 *p, int key);
extern int func_02088d94(Entry8 *ptr);
extern int func_ov095_022999b0(UnkStruct_0229adc4 *p, int a);

int func_ov095_0229adc4(UnkStruct_0229adc4 *self)
{
    int v = self->unk_28;
    if (v > 0x109) {
        goto big;
    }
    if (v >= 0x109) {
        goto med;
    }
    if (v > 0xfa) {
        goto fail;
    }
    if (v < 0xf8) {
        goto fail;
    }
    if (v == 0xf8) {
        goto common;
    }
    if (v == 0xf9) {
        goto common;
    }
    if (v != 0xfa) {
        goto fail;
    }
    goto common;
big:
    if (v != 0x10a) {
        goto fail;
    }
    goto big2;
common:
    self->unk_2C = func_ov095_0229ae5c(self, v);
    self->unk_30 = func_02088d94(&self->arr[v - 0xf8]) + 0x68;
    return 1;
med:
    self->unk_2C = 0x18;
    self->unk_30 = 0x54;
    if (func_ov095_022999b0(self, 4) == 0) {
        self->unk_30 -= 8;
    }
    return 1;
big2:
    self->unk_2C = 0xe8;
    self->unk_30 = 0x54;
    if (func_ov095_022999b0(self, 4) == 0) {
        self->unk_30 -= 8;
    }
    return 1;
fail:
    return 0;
}
