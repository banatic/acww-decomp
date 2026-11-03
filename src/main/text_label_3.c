/* text_label_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070adc @ 0x02070adc, 0x48 bytes, Thumb
 * func_02070a98 @ 0x02070a98, 0x44 bytes, Thumb
 * func_02070a54 @ 0x02070a54, 0x44 bytes, Thumb
 */

struct UnkStruct_02070adc {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
};

struct UnkStruct_02070adc_2 {
    unsigned char pad_00[0x68];
    struct UnkStruct_02070adc *unk_68;
};

typedef struct {
    char pad_00[0x68];
    void *unk_68;
} UnkStruct_02070a98;

typedef struct {
    char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_02070a98_2;

struct UnkStruct_02070a54 {
    unsigned char pad_00[0x38];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x1E];
    unsigned int unk_58;
};

struct UnkStruct_02070a54_2 {
    unsigned char pad_00[0x68];
    struct UnkStruct_02070a54 *b;
};

extern void func_02070b84(struct UnkStruct_02070adc_2 *a);
extern struct UnkStruct_02070adc *func_020a9034(int x, int y, int mode);
extern void func_02070b24(struct UnkStruct_02070adc_2 *a, struct UnkStruct_02070adc *b, unsigned char flag1,
                          unsigned char flag2);
extern unsigned char data_021c82e8[];
extern unsigned char data_021c828c[];
extern struct UnkStruct_02070a54 *func_020a8fe8(int, int, int);

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

void func_02070a98(UnkStruct_02070a98 *p1, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag)
{
    if (p1->unk_68 != 0) {
        func_02070b84((struct UnkStruct_02070adc_2 *) p1);
    }
    p1->unk_68 = (void *) func_020a9034(p3, p4, 1);
    func_02070b24((struct UnkStruct_02070adc_2 *) p1, (struct UnkStruct_02070adc *) p2, p5, p6);
    ((UnkStruct_02070a98_2 *) p1->unk_68)->unk_28 = (unsigned int) data_021c828c;
}

void func_02070a54(struct UnkStruct_02070a54_2 *a, int arg1, int arg2, int arg3, unsigned char arg4)
{
    if (a->b) {
        func_02070b84((struct UnkStruct_02070adc_2 *) a);
    }
    a->b = func_020a8fe8(arg1, arg2, 2);
    if (a->b) {
        a->b->unk_39 = arg4;
        a->b->unk_38 = (unsigned char) arg3;
        a->b->unk_58 = 2;
    }
}
