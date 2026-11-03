/* clock_panel_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208df44 @ 0x0208df44, 0xa0 bytes, Thumb
 * func_0208def4 @ 0x0208def4, 0x50 bytes, Thumb
 * func_0208de9c @ 0x0208de9c, 0x58 bytes, Thumb
 * func_0208de10 @ 0x0208de10, 0x8c bytes, Thumb
 */

struct UnkStruct_0208df44 {
    char *unk_00;
    char pad_04[8];
    char sub1[20];
    int words[10];
    char bytes[8];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    unsigned short unk_60;
    unsigned short unk_62;
    int unk_64;
    char sub68[0x1c];
    char sub84[0x1c];
    char suba0[0x1c];
    char subbc[0x1c];
};

typedef struct {
    int *unk_00;
    char pad_04[8];
    int unk_0C;
    char pad_10[0x58];
    int unk_68;
    char pad_6C[0x18];
    int unk_84;
    char pad_88[0x18];
    int unk_A0;
    char pad_A4[0x18];
    int unk_BC;
} UnkStruct_0208def4;

typedef struct {
    char pad_00[0x0c];
    int sub;
    char pad_10[0x10];
    int flag32;
    char pad_24[0x2c];
    int unk_50;
    char pad_54[0x10];
    int unk_64;
} UnkStruct_0208de10;

extern void func_0208af30(void *self);
extern void func_0208a1f8(char *sub);
extern void *func_0208e024(char *sub);
extern int data_020e226c;
extern void *func_0208a144(void *);
extern void func_0208dd60(void *);
extern void *func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

struct UnkStruct_0208df44 *func_0208df44(struct UnkStruct_0208df44 *self)
{
    func_0208af30(self);
    self->unk_00 = ((char *) &data_020e226c);
    func_0208a1f8(self->sub1);
    self->words[0] = 0;
    self->words[1] = 0;
    self->words[2] = 0;
    self->words[3] = 0;
    self->words[4] = 0;
    self->words[5] = 0;
    self->words[6] = 0;
    self->words[7] = 0;
    self->words[8] = 0;
    self->words[9] = 0;
    self->bytes[0] = 0;
    self->bytes[1] = 0;
    self->bytes[2] = 0;
    self->bytes[3] = 0;
    self->bytes[4] = 0;
    self->bytes[5] = 0;
    self->bytes[6] = 0;
    self->bytes[7] = 0;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = 0;
    self->unk_5C = -1;
    self->unk_64 = 0;
    func_0208e024(self->sub68);
    func_0208e024(self->sub84);
    func_0208e024(self->suba0);
    func_0208e024(self->subbc);
    {
        unsigned short *p = (unsigned short *) ((char *) self + 0x60);
        *p = 0;
        p = (unsigned short *) ((char *) self + 0x62);
        *p = 0;
    }
    return self;
}

void *func_0208def4(UnkStruct_0208def4 *self)
{
    self->unk_00 = &data_020e226c;
    func_0208a144(&self->unk_0C);
    func_0208dd60(self);
    func_0208e00c(&self->unk_BC);
    func_0208e00c(&self->unk_A0);
    func_0208e00c(&self->unk_84);
    func_0208e00c(&self->unk_68);
    func_0208a1f4(&self->unk_0C);
    func_0208af00(self);
    return self;
}

void *func_0208de9c(void *self)
{
    *(void **) self = (void *) &data_020e226c;
    func_0208a144((char *) self + 0xc);
    func_0208dd60(self);
    func_0208e00c((char *) self + 0xbc);
    func_0208e00c((char *) self + 0xa0);
    func_0208e00c((char *) self + 0x84);
    func_0208e00c((char *) self + 0x68);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0208de10(UnkStruct_0208de10 *p)
{
    int ret1, ret2, ret3, ret4, r4_calc, r3_calc, tmp;
    int arg5;
    if (p->flag32 == 0) {
        return;
    }
    ret1 = func_0208a1d0(&p->sub);
    if (ret1 == 0) {
        return;
    }
    ret2 = func_0208a1b0(&p->sub, -1);
    ret3 = func_0208a198(&p->sub, -1);
    ret4 = func_0208aef0(p);
    r4_calc = (p->unk_50 + 0x800) >> 12;
    tmp = func_0208aeec(p);
    r3_calc = tmp + r4_calc;
    if (p->unk_64 == 0) {
        arg5 = 15;
    } else {
        arg5 = 9;
    }
    func_02088df8(0, ret1, ret4 + ret2, r3_calc + ret3, arg5, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
