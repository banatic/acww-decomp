/* catalog_screen: 5 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229d824 @ 0x0229d824, 0x58 bytes, Thumb
 * func_ov114_0229d700 @ 0x0229d700, 0x124 bytes, Thumb
 * func_ov114_0229d688 @ 0x0229d688, 0x78 bytes, Thumb
 * func_ov114_0229d5b8 @ 0x0229d5b8, 0xd0 bytes, Thumb
 * func_ov114_0229d564 @ 0x0229d564, 0x54 bytes, Thumb
 */

#include "types.h"

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

extern void func_ov114_0229d168(void *arg0);
extern void func_ov002_0220a544(void *);
extern void func_ov114_0229c720(void *);
extern int func_ov114_0229c1a0(void *, int);
extern int func_020b9b6c(void *, void *, unsigned char, int);
extern void func_ov114_0229c180(void *, int);
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
extern int func_02002c6c(const void *data, void *ctx, u8 val, int a, int b, int c);
extern int func_02002d14(const void *data, void *ctx, u8 val, int a, int b, int c);
extern int func_02064af4(const void *src, void *dst, unsigned int size);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);
extern int func_02002ca4(const void *data, void *ctx, u8 val);
extern const char data_ov114_0229dbcc[];
extern const char data_ov114_0229dbe4[];
extern const char data_ov114_0229dbf8[];
extern const char data_ov114_0229dc0c[];
extern int func_020896b8(int a, void *b, int c, void *d, int e, int f, int g);
extern void func_02088df8(int a, void *b, int c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int data_ov114_0229dac8[];
extern int data_ov114_0229db00[];
extern int data_ov114_0229db08[];
extern int data_ov114_0229db10[];
extern int func_02088d34(const void *ptr, int a, int b, int c, int d);
extern int func_ov114_0229cf18(int);
extern int func_ov114_0229cee0(int);
extern char data_ov114_0229dad0;

void func_ov114_0229d824(void *self)
{
    func_ov114_0229d168((void *) self);
    func_ov002_0220a544((char *) self + 0x121c);
    func_ov114_0229c720(self);
    if (func_ov114_0229c1a0(self, 1) != 0) {
        if (func_020b9b6c((char *) self + 0x924, (char *) self + 0x968, *(unsigned char *) ((char *) self + 0x12b1), 4) != 0) {
            func_ov114_0229c180(self, 1);
        }
    }
}

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

void func_ov114_0229d688(void *receiver)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov114_0229dbcc, p, (u8) 8, 7, 7, 14);
    func_02002d14(data_ov114_0229dbe4, p, (u8) 8, 4, 4, 6);
    func_02002c6c(data_ov114_0229dbf8, p, (u8) 8, 0xc0, 0xc0, 0x140);
    func_02002c6c(data_ov114_0229dc0c, p, (u8) 8, 0x141, 0x141, 0x1bf);
}

void func_ov114_0229d5b8(u8 *self, u8 *arg1)
{
    u8 *base;
    int i;
    int v;
    u8 *q;
    u8 *p;

    base = arg1 + 0x60;
    for (i = 0; i < 2; i++) {
        v = *(int *) (self + i * 4 + 0x129c);
        q = self + i + 0x12ae;
        if (*q != 0) {
            *q = *q - 1;
            v = 6;
        }
        func_020896b8(1, &data_ov114_0229dac8[i * 2], 0x80, base, v, 1, 0);
    }

    p = base;
    if (self[0x12bb] == 0) {
        p = base + 2;
    }
    func_020896b8(1, data_ov114_0229db00, 0x80, p, -1, 1, 0);

    p = base;
    if (self[0x12bb] == 1) {
        p = base + 2;
    }
    func_020896b8(1, data_ov114_0229db08, 0x80, p, -1, 1, 0);

    func_02088df8(1, data_ov114_0229db10, 0x80, base, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}

int func_ov114_0229d564(int p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    if (func_02088d34(((char *) data_ov114_0229dac8), a, b, 2, 2)) {
        return func_ov114_0229cf18(p0);
    }
    if (func_02088d34(&data_ov114_0229dad0, a, b, 2, 2)) {
        return func_ov114_0229cee0(p0);
    }
    return 0;
}
