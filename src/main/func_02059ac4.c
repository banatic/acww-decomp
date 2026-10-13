/* func_02059ac4 @ 0x02059ac4, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02059ac4 {
    unsigned char pad_00[0x50];
    unsigned short u16_50;
    unsigned char pad_52[0x58 - 0x52];
    unsigned char u8_58;
    unsigned char pad_59[0x78 - 0x59];
    unsigned int u32_78;
    unsigned int u32_7c;
    unsigned int u32_80;
    unsigned int u32_84;
    unsigned int u32_88;
    unsigned int u32_8c;
    unsigned char pad_90[0xa8 - 0x90];
    unsigned int u32_a8;
    unsigned int u32_ac;
    unsigned int u32_b0;
    unsigned char pad_B4[0xbc - 0xb4];
    unsigned int u32_bc;
    unsigned int u32_c0;
    unsigned int u32_c4;
    unsigned char u8_c8;
    unsigned char pad_C9[0xcc - 0xc9];
    unsigned int u32_cc[2];
    unsigned char u8_d4;
    unsigned char pad_D5[0xd6 - 0xd5];
    unsigned short u16_d6;
    unsigned char u8_d8;
} UnkStruct_02059ac4;

extern unsigned int data_020cbafc;
extern void func_02059920(UnkStruct_02059ac4 *);
extern void func_02059674(UnkStruct_02059ac4 *, int);

void func_02059ac4(UnkStruct_02059ac4 *self)
{
    int i;

    self->u8_c8 = 0;
    for (i = 0; i < 2; i++) {
        self->u32_cc[i] = 0;
    }

    self->u16_50 = 0xfff1;
    self->u8_58 = 0xc;
    self->u16_d6 = 0;
    self->u8_d4 = 0;

    func_02059920(self);

    self->u32_84 = 0;
    self->u32_88 = 0;
    self->u32_8c = 0;
    self->u32_78 = 0;
    self->u32_7c = 0;
    self->u32_80 = 0;
    self->u32_a8 = 0;
    self->u32_ac = 0;
    self->u32_b0 = 0;
    self->u8_d8 = 0;

    func_02059674(self, 0);

    self->u32_bc = data_020cbafc;
    self->u32_c4 = -1;
}
