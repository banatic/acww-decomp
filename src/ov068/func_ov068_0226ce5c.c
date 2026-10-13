/* func_ov068_0226ce5c @ 0x0226ce5c, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226ce5c {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[8];
    int unk_18;
    char pad_1C[4];
    int unk_20;
    int unk_24;
    int unk_28;
    unsigned short unk_2C;
    char pad_2E[6];
    unsigned short unk_34;
    short unk_36;
    unsigned char unk_38;
    char pad_39[1];
    unsigned short unk_3A;
    char sub[4];
    char pad_40[152];
    short unk_D8;
    unsigned short unk_DA;
    unsigned short unk_DC;
    unsigned short unk_DE;
    unsigned char unk_E0;
    char pad_E1[3];
    int unk_E4;
    char pad_E8[12];
    int unk_F4;
    int unk_F8;
} UnkStruct_0226ce5c;

extern void func_020139f0(void *);
extern void func_020139bc(void *);

UnkStruct_0226ce5c *func_ov068_0226ce5c(UnkStruct_0226ce5c *self)
{
    func_020139f0(&self->sub);
    self->unk_E4 = 0;
    self->unk_18 = 0x18;
    self->unk_00 = 0x10000;
    self->unk_04 = 0x10000;
    self->unk_08 = 0x1a000;
    self->unk_0C = 0xa000;
    self->unk_24 = 0;
    func_020139bc(&self->sub);
    {
        int zero = 0;
        int neg1 = ~zero;
        self->unk_20 = zero;
        self->unk_D8 = neg1;
        self->unk_DA = zero;
        self->unk_F4 = zero;
        self->unk_F8 = zero;
        self->unk_28 = zero;
        self->unk_34 = zero;
        self->unk_36 = neg1;
        self->unk_2C = zero;
        self->unk_38 = zero;
        self->unk_3A = zero;
        self->unk_DC = zero;
        self->unk_DE = zero;
        self->unk_E0 = zero;
    }
    return self;
}
