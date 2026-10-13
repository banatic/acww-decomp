/* func_02070adc @ 0x02070adc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02070adc {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
};

struct UnkStruct_02070adc_2 {
    unsigned char pad_00[0x68];
    struct UnkStruct_02070adc *unk_68;
};

extern void func_02070b84(struct UnkStruct_02070adc_2 *a);
extern struct UnkStruct_02070adc *func_020a9034(int x, int y, int mode);
extern void func_02070b24(struct UnkStruct_02070adc_2 *a, struct UnkStruct_02070adc *b, unsigned char flag1,
                          unsigned char flag2);

extern unsigned char data_021c82e8[];

void func_02070adc(struct UnkStruct_02070adc_2 *a, struct UnkStruct_02070adc *b, int x, int y, unsigned char flag1,
                   unsigned char flag2, int flag3)
{
    if (a->unk_68 != 0) {
        func_02070b84(a);
    }
    a->unk_68 = func_020a9034(x, y, 2);
    func_02070b24(a, b, flag1, flag2);
    if (flag3 != 0) {
        a->unk_68->unk_28 = (unsigned int) data_021c82e8;
    }
}
