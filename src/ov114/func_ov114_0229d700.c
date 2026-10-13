/* func_ov114_0229d700 @ 0x0229d700, 0x124 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021fbe94;
extern void *data_ov114_0229dce4;

extern const char data_ov114_0229dc20[];
extern const char data_ov114_0229dc34[];
extern const char data_ov114_0229dc48[];
extern const char data_ov114_0229dc60[];
extern const char data_ov114_0229dc74[];
extern const char data_ov114_0229dc8c[];
extern const char data_ov114_0229dca0[];
extern const char data_ov114_0229dcb4[];
extern const char data_ov114_0229dcc8[];

extern void func_02002c6c(const void *data, void *ctx, u8 val, int a, int b, int c);
extern void func_02002d14(const void *data, void *ctx, u8 val, int a, int b, int c);
extern void func_02064af4(const void *src, void *dst, unsigned int size);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);
extern void func_02002ca4(const void *data, void *ctx, u8 val);

struct UnkStruct_0229d700 {
    char pad_00[0x948];
    char arr1[0x20];
    char arr2[0x20];
    char pad_988[0x12b1 - 0x988];
    u8 unk_12B1;
    u8 unk_12B2;
    u8 unk_12B3;
    char pad_12B4[3];
    u8 unk_12B7;
};

void func_ov114_0229d700(struct UnkStruct_0229d700 *s)
{
    void *ctx = data_021fbe94;

    func_02002c6c(data_ov114_0229dc20, ctx, s->unk_12B1, 0x109, 0x109, 0x153);
    func_02002c6c(data_ov114_0229dc34, ctx, s->unk_12B1, 0x154, 0x154, 0x19f);

    if (s->unk_12B7 == 1) {
        func_02002c6c(data_ov114_0229dc48, ctx, s->unk_12B1, 0x150, 0x150, 0x164);
    }

    switch (s->unk_12B7) {
        case 0:
            data_ov114_0229dce4 = (void *) data_ov114_0229dc60;
            break;
        case 1:
            data_ov114_0229dce4 = (void *) data_ov114_0229dc74;
            break;
    }

    func_02002d14(data_ov114_0229dce4, ctx, s->unk_12B1, 1, 1, 6);

    func_02064af4(data_ov114_0229dc8c, s->arr1, 0x20);
    MIi_CpuCopy16(s->arr1, s->arr2, 0x20);

    func_02002ca4(data_ov114_0229dca0, ctx, s->unk_12B1);
    func_02002ca4(data_ov114_0229dcb4, ctx, s->unk_12B2);
    func_02002ca4(data_ov114_0229dcc8, ctx, s->unk_12B3);
}
