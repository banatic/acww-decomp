/* snowball_3: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226fd80 @ 0x0226fd80, 0x80 bytes, Thumb
 * func_ov068_0226fd28 @ 0x0226fd28, 0x58 bytes, Thumb
 * func_ov068_0226fcbc @ 0x0226fcbc, 0x6c bytes, Thumb
 * func_ov068_0226fc48 @ 0x0226fc48, 0x74 bytes, Thumb
 * func_ov068_0226fc2c @ 0x0226fc2c, 0x1c bytes, Thumb
 */

typedef struct {
    unsigned short pad0 : 6;
    unsigned short bit6 : 1;
    unsigned short pad7 : 3;
    unsigned short bit10 : 1;
} Flags378;

typedef struct {
    char pad0[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xa8 - 0x68];
    int unk_A8;
    char pad_AC[0x274 - 0xac];
    int unk_274;
    char pad_278[0x2f0 - 0x278];
    int unk_2F0;
    int unk_2F4;
    char pad_2F8[0x378 - 0x2f8];
    Flags378 unk_378;
} UnkStruct_0226fd80;

typedef struct UnkStruct_0226fcbc UnkStruct_0226fcbc;

struct UnkStruct_0226fcbc {
    char pad_00[0x5c];
    char unk_5C[0x210];
    int unk_26C;
    char pad_270[0x98];
    char unk_308[0x20];
    char unk_328[0x10];
};

extern void func_01ffd070(void *, void *, void *);
extern short FX_Div(int, int);
extern int func_020912d4(int, void *, int, void *);
extern int func_020044c0(void *, unsigned, unsigned, int);
extern int data_020c904c;
extern int func_ov003_02228400(void *, int);

void func_ov068_0226fd80(UnkStruct_0226fd80 *self)
{
    if (self->unk_274 & 1) {
        self->unk_A8 = 0;
    } else {
        self->unk_A8 += 0x6d;
        if (self->unk_A8 > 0x200) {
            self->unk_A8 = 0x200;
        }
    }
    self->unk_60 -= self->unk_A8;
    if (self->unk_378.bit6) {
        return;
    }
    if (self->unk_378.bit10) {
        return;
    }
    self->unk_5C += self->unk_2F0;
    self->unk_64 += self->unk_2F4;
}

int func_ov068_0226fd28(int param)
{
    if (param < 0x99a) {
        return 3;
    }
    if (param < 0xb33) {
        return 2;
    }
    if (param < 0xccd) {
        return 1;
    }
    if (param < 0xe66) {
        return 0;
    }
    if (param < 0x1000) {
        return 1;
    }
    if (param < 0x119a) {
        return 2;
    }
    return 3;
}

void func_ov068_0226fcbc(UnkStruct_0226fcbc *param)
{
    short result;
    int buffer[2];

    func_01ffd070(buffer, param->unk_5C, param->unk_308);
    buffer[1] += param->unk_26C - 0x400;
    result = FX_Div(param->unk_26C, 0x1000);
    func_020912d4(0x3e, buffer, 0, &result);
    func_020044c0(param->unk_328, 0x81f, 0x7f, 0);
}

void func_ov068_0226fc48(void *p)
{
    struct {
        short a;
        int b;
        int c;
        int d;
    } local;

    local.b = *(int *) ((char *) p + 0x5c);
    local.c = *(int *) ((char *) p + 0x60);
    local.d = *(int *) ((char *) p + 0x64);
    local.c = data_020c904c + 0x100;
    local.a = (short) FX_Div(*(int *) ((char *) p + 0x26c), 0x1000);
    func_020912d4(0x3f, (void *) (&local.b), 0, (void *) (&local.a));
    func_020044c0((char *) p + 0x328, 0x821, 0x7f, 0);
    func_ov003_02228400((char *) p + 0x5c, 0x5000);
}

int func_ov068_0226fc2c(unsigned short *p)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x378);
    *q |= 0x10;
    *q &= ~0x20;
    return 1;
}
