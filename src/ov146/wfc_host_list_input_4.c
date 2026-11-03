/* wfc_host_list_input_4: 11 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229a7f4 @ 0x0229a7f4, 0x38 bytes, Thumb
 * func_ov146_0229a7a4 @ 0x0229a7a4, 0x50 bytes, Thumb
 * func_ov146_0229a778 @ 0x0229a778, 0x2c bytes, Thumb
 * func_ov146_0229a760 @ 0x0229a760, 0x16 bytes, Thumb
 * func_ov146_0229a744 @ 0x0229a744, 0x1c bytes, Thumb
 * func_ov146_0229a724 @ 0x0229a724, 0x20 bytes, Thumb
 * func_ov146_0229a6dc @ 0x0229a6dc, 0x48 bytes, Thumb
 * func_ov146_0229a6a4 @ 0x0229a6a4, 0x36 bytes, Thumb
 * func_ov146_0229a62c @ 0x0229a62c, 0x78 bytes, Thumb
 * func_ov146_0229a5e8 @ 0x0229a5e8, 0x44 bytes, Thumb
 * func_ov146_0229a59c @ 0x0229a59c, 0x4c bytes, Thumb
 */

struct UnkStruct_0229a7a4 {
    char pad_00[0xb2];
    unsigned char flag_b2;
    unsigned char flag_b3;
    char pad_B4[0x15cc - 0xb4];
    int unk_15CC;
};

struct UnkStruct_0229a6dc {
    unsigned char pad_00[0xB0];
    unsigned char unk_B0;
    unsigned char pad_B1[9];
    unsigned char unk_BA;
    unsigned char unk_BB;
};

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned int unk_A8;
    unsigned char pad_AC[0xb2 - 0xa8 - 4];
    unsigned char unk_B2;
    unsigned char pad_B3[0x15cc - 0xb2 - 1];
    int unk_15CC;
} UnkStruct_0229a62c;

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned int unk_A8;
    unsigned char pad_AC[6];
    unsigned char unk_B2;
} UnkStruct_0229a59c;

extern int func_0208e484(void *);
extern int func_ov146_02299a4c(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov146_0229a464(void *);
extern int func_ov146_0229a4b0(void *p);
extern int func_ov146_02299670(void *p, int n);
extern void func_ov146_02299650(void *p, int n);
extern void func_ov146_0229a534(void *p);
extern void func_ov146_0229a578(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);
extern void func_0206fc4c(int);
extern void func_0206fc80(int);
extern void func_ov146_02299660(struct UnkStruct_0229a6dc *, int);
extern void func_ov002_02208090(struct UnkStruct_0229a6dc *, int);
extern void func_0200467c(int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);
extern int func_ov002_0220a4f8(unsigned char *);
extern unsigned int func_ov002_0220a4d4(void *p);

void func_ov146_0229a62c(UnkStruct_0229a62c *param);
int func_ov146_0229a5e8(unsigned char *arg);
unsigned int func_ov146_0229a59c(UnkStruct_0229a59c *self);

void func_ov146_0229a7f4(void *self)
{
    if (func_0208e484((char *) self + 0x15cc)) {
        if (func_ov146_02299a4c(self, *(unsigned char *) ((char *) self + 0xb2)) == 0) {
            func_ov002_02208098(self, 3);
            func_ov146_0229a464(self);
        }
    }
}

void func_ov146_0229a7a4(struct UnkStruct_0229a7a4 *p)
{
    if (func_0208e484((void *) (&p->unk_15CC)) != 0) {
        func_ov146_0229a4b0(p);
        func_ov002_02208098(p, p->flag_b3);
        if (func_ov146_02299670(p, 16) != 0) {
            func_ov146_02299650(p, 16);
            p->flag_b2 = 1;
            func_ov146_0229a534(p);
        }
    }
}

void func_ov146_0229a778(void *param)
{
    if (((volatile unsigned char *) param)[0xba] != 0) {
        ((volatile unsigned char *) param)[0xba] = ((volatile unsigned char *) param)[0xba] - 1;
    } else {
        func_ov146_0229a578(param);
        func_ov002_022080a0(param, 1);
    }
}

void func_ov146_0229a760(void *p)
{
    func_ov146_0229a578((void *) p);
    func_ov002_02208098(p, 0);
}

void func_ov146_0229a744(void *p)
{
    func_ov146_0229a62c((UnkStruct_0229a62c *) p);
    func_ov002_02207fc0(p);
    func_ov002_02208098(p, 3);
}

void func_ov146_0229a724(int param)
{
    if (func_0206fe60() != 0) {
        func_ov146_0229a760((void *) param);
    } else {
        func_ov146_0229a744((void *) param);
    }
}

void func_ov146_0229a6dc(struct UnkStruct_0229a6dc *self)
{
    func_0206fc4c(1);
    func_0206fc80(self->unk_BB);
    self->unk_B0 = 10;
    func_ov146_02299660(self, 0x40);
    self->unk_BA = 5;
    func_ov002_02208090(self, 2);
    func_ov002_02208098((void *) self, 9);
    func_0200467c(0x27);
}

void func_ov146_0229a6a4(void *r0)
{
    func_0206fc4c(0);
    ((unsigned char *) r0)[0xb1] = 0xa;
    ((unsigned char *) r0)[0xba] = 5;
    func_ov002_02208090((struct UnkStruct_0229a6dc *) r0, 2);
    func_ov002_02208098(r0, 9);
    func_0200467c(0x28);
}

void func_ov146_0229a62c(UnkStruct_0229a62c *param)
{
    if (param->unk_B2 == 3) {
        unsigned int mask = param->unk_A8 & 0xf;
        if (mask) {
            param->unk_A8 -= mask;
        }
    }
    {
        int v1 = func_ov146_0229a5e8((unsigned char *) param);
        int v2 = (int) func_ov146_0229a59c((UnkStruct_0229a59c *) param);
        func_ov002_0220a0b4(&param->unk_15CC, v1, v2);
    }
    if (param->unk_B2 == 2) {
        func_ov002_0220a374(&param->unk_15CC, 1);
    } else {
        func_ov002_0220a374(&param->unk_15CC, 7);
    }
    func_ov146_0229a4b0(param);
}

int func_ov146_0229a5e8(unsigned char *arg)
{
    unsigned char b = arg[0xb2];

    if (b >= 3 && b <= 9) {
        return 0x1c;
    }

    switch (b) {
        case 0:
            return 0x47;
        case 1:
            return 0x99;
        case 2:
            return func_ov002_0220a4f8(arg + 0x1fb4);
        default:
            return 0x80;
    }
}

unsigned int func_ov146_0229a59c(UnkStruct_0229a59c *self)
{
    unsigned char b = self->unk_B2;
    if (b >= 3 && b <= 9) {
        return 0x40 + (b - 3) * 16 - (self->unk_A8 & 0xf);
    } else {
        switch (b) {
            case 0:
            case 1:
                return 0xad;
            case 2:
                return func_ov002_0220a4d4((unsigned char *) self + 0x1fb4);
            default:
                return 0x60;
        }
    }
}
