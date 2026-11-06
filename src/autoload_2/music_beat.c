/* music_beat: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f9408 @ 0x020f9408, 0x1e8 bytes, ARM
 * func_020f92d0 @ 0x020f92d0, 0x138 bytes, ARM
 * func_020f920c @ 0x020f920c, 0xc4 bytes, ARM
 * func_020f8fa8 @ 0x020f8fa8, 0x264 bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x38];
    unsigned short unk_38;
} UnkStruct_020f9408;

typedef struct {
    unsigned char pad_00[0x14];
    signed char unk_14;
    unsigned char pad_15[0x1c - 0x15];
    int unk_1C, unk_20, unk_24;
    unsigned char unk_28;
    unsigned char unk_29;
    unsigned char unk_2A;
} UnkStruct_020f9408_2;

typedef struct {
    char pad_00[0x15];
    signed char unk_15;
} UnkStruct_020f92d0;

typedef struct {
    char pad_00[0x16];
    char unk_16;
    char unk_17;
    char unk_18;
    char pad_19[0x13];
    short unk_2C;
    unsigned char unk_2E;
} UnkStruct_020f920c;

struct UnkStruct_020f8fa8 {
    u8 pad_00[0x14];
    s8 type; // +0x14
    u8 pad_15[0x1c - 0x15];
    int freqA; // +0x1c
    int freqB; // +0x20
    int freqC; // +0x24
    u8 pad_28[0x2a - 0x28];
    u8 flag1; // +0x2a
    u8 pad_2B[0x2c - 0x2b];
    s16 note; // +0x2c
    u8 flag2; // +0x2e
};

extern UnkStruct_020f9408 *data_021fd1f8;
extern void func_020f9728(UnkStruct_020f9408_2 *);
extern int NNS_SndPlayerReadVariable(UnkStruct_020f9408 **, int, short *);
extern int func_0210b498(void *p, int i, unsigned char *buf);
extern int FX_Div(int, int);

void func_020f92d0(UnkStruct_020f92d0 *self);
void func_020f920c(UnkStruct_020f920c *out);
void func_020f8fa8(struct UnkStruct_020f8fa8 *self);

void func_020f9408(UnkStruct_020f9408_2 *self)
{
    short tmp;
    unsigned int ok;
    unsigned short v;
    UnkStruct_020f9408 **pp;

    if (self->unk_28 == 0) {
        return;
    }

    func_020f9728(self);
    func_020f92d0((UnkStruct_020f92d0 *) self);
    func_020f920c((UnkStruct_020f920c *) self);

    if (self->unk_14 != -1) {
        goto tail;
    }

    pp = &data_021fd1f8;
    ok = (unsigned int) (*pp != 0);
    if (ok == 0) {
        return;
    }

    NNS_SndPlayerReadVariable(pp, 4, &tmp);
    self->unk_14 = (unsigned char) tmp;
    self->unk_1C = 0;
    self->unk_20 = 0;
    self->unk_24 = 0;

    v = (*pp)->unk_38;
    switch (v) {
        case 0x6d:
        case 0xa3:
            self->unk_29 = 1;
            break;
        case 0x6e:
            self->unk_29 = 2;
            break;
    }

    switch (v) {
        case 0x6d:
        case 0x9f:
        case 0xa2:
        case 0xa4:
            self->unk_2A = 1;
            break;
        case 0x67:
        case 0x68:
        case 0x6c:
        case 0x6e:
        case 0x6f:
        case 0x77:
        case 0x85:
        case 0x9e:
        case 0xa6:
            self->unk_2A = 2;
            break;
        case 0x94:
            self->unk_2A = 3;
            break;
        default:
            self->unk_2A = 0;
            break;
    }
    return;
tail:
    func_020f8fa8((struct UnkStruct_020f8fa8 *) self);
}

void func_020f92d0(UnkStruct_020f92d0 *self)
{
    unsigned char buf[28];
    void *pp;
    int i;

    pp = ((void **) &data_021fd1f8);
    self->unk_15 = -1;

    for (i = 2; i <= 13; i++) {
        if (func_0210b498(pp, i, buf) == 0) {
            continue;
        }
        if (i == 10) {
            continue;
        }
        if (buf[9] == 0) {
            continue;
        }

        switch (i) {
            case 11:
                self->unk_15 = 0;
                return;
            case 6:
                self->unk_15 = 1;
                return;
            case 3:
            case 9:
                self->unk_15 = 2;
                return;
            case 5:
            case 8:
                self->unk_15 = 3;
                return;
            case 2:
            case 7:
            case 12:
                self->unk_15 = 4;
                return;
            case 4:
            case 13:
                self->unk_15 = 5;
                return;
            case 0:
            case 1:
            case 10:
            default:
                self->unk_15 = 0;
                return;
        }
    }
}

void func_020f920c(UnkStruct_020f920c *out)
{
    unsigned int valid;
    short vars[4];
    int *p = ((int *) &data_021fd1f8);

    valid = (*p != 0);
    if (valid == 0) {
        return;
    }

    NNS_SndPlayerReadVariable((UnkStruct_020f9408 **) p, 1, &vars[0]);
    NNS_SndPlayerReadVariable((UnkStruct_020f9408 **) p, 0, &vars[1]);
    NNS_SndPlayerReadVariable((UnkStruct_020f9408 **) p, 2, &vars[2]);
    NNS_SndPlayerReadVariable((UnkStruct_020f9408 **) p, 3, &vars[3]);

    out->unk_16 = vars[1];
    out->unk_17 = vars[2];
    out->unk_18 = vars[3];

    if (out->unk_2C > vars[0]) {
        out->unk_2E = (out->unk_2E == 0) ? 1 : 0;
    }
    out->unk_2C = vars[0];
}

void func_020f8fa8(struct UnkStruct_020f8fa8 *self)
{
    int r0;
    int r1;

    self->freqA = FX_Div((int) self->note << 12, 0x3000);

    r1 = self->type;
    r0 = self->note;
    switch (r1) {
        case 3:
            r1 = 0x4800;
            break;
        case 4:
        default:
            switch (self->flag1) {
                case 0:
                default:
                    r0 = (s16) (r0 % 96);
                    r1 = 0x3000;
                    break;
                case 1:
                    r0 = (s16) (r0 % 48);
                    r1 = 0x1800;
                    break;
                case 2:
                    r0 = (s16) (r0 % 192);
                    r1 = 0x6000;
                    break;
            }
            break;
    }
    r0 = FX_Div(r0 << 12, r1);
    r0 = r0 + 0xc000;
    if (r0 >= 0x20000) {
        r0 -= 0x20000;
    }
    self->freqC = r0;

    r1 = self->type;
    r0 = self->note;
    switch (r1) {
        case 4:
        default:
            switch (self->flag1) {
                case 0:
                default:
                    r0 = (s16) (r0 % 96);
                    r1 = 0x4ccd;
                    break;
                case 1:
                    r0 = (s16) (r0 % 48);
                    r1 = 0x2666;
                    break;
                case 2:
                    r0 = (s16) (r0 % 192);
                    r1 = 0x999a;
                    break;
            }
            break;
        case 3:
            switch (self->flag1) {
                case 3:
                    r1 = self->flag2;
                    if (r1 == 0) {
                        r0 = (s16) (r0 + 0x90);
                    }
                    r1 = 0xe666;
                    break;
                default:
                    r1 = self->flag2;
                    if (r1 == 0) {
                        r0 = (s16) (r0 + 0x30);
                    }
                    r0 = (s16) (r0 % 96);
                    r1 = 0x4ccd;
                    break;
            }
            break;
    }
    r0 = FX_Div(r0 << 12, r1);
    r0 = r0 + 0x4000;
    if (r0 >= 0x14000) {
        r0 -= 0x14000;
    }
    self->freqB = r0;
}
