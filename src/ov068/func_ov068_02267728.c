/* func_ov068_02267728 @ 0x02267728, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02267728 {
    unsigned char pad_00[0x1c];
    char unk_1C;
    unsigned char pad_1D[0x38 - 0x1c - 1];
    char unk_38;
    unsigned char pad_39[0x3a - 0x38 - 1];
    unsigned short unk_3A;
    unsigned char pad_3C[0xf4 - 0x3a - 2];
    int unk_F4;
} UnkStruct_02267728;

typedef struct UnkStruct_02267728_2 {
    unsigned char data[0xa0c];
    int unk_A0C;
} UnkStruct_02267728_2;

extern int func_02014868(const void *ptr);
extern void func_ov068_0226ad78(UnkStruct_02267728 *a, UnkStruct_02267728_2 *b, int, int, int);
extern void func_0203eddc(UnkStruct_02267728_2 *b);
extern int func_0203e020(UnkStruct_02267728_2 *b);
extern void func_0201ce5c(UnkStruct_02267728_2 *b, int);
extern void func_0201ce44(UnkStruct_02267728_2 *b, int);
extern void func_ov068_0226cce4(UnkStruct_02267728 *a, int);

void func_ov068_02267728(UnkStruct_02267728 *a, UnkStruct_02267728_2 *b)
{
    if (func_02014868(&b->data[0x618]) != 0) {
        return;
    }
    func_ov068_0226ad78(a, b, 4, 1, 1);
    func_0203eddc(b);
    func_0203e020(b);
    func_0201ce5c(b, 0);
    func_0201ce44(b, 0);
    func_ov068_0226cce4(a, 0);
    a->unk_38 = 0;
    a->unk_3A = 0;
    b->unk_A0C = 3;
    a->unk_F4 = 0x4b0;
    a->unk_1C = 2;
}
