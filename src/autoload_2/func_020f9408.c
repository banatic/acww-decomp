/* func_020f9408 @ 0x020f9408, 0x1e8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

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

extern UnkStruct_020f9408 *data_021fd1f8;

extern void func_020f9728(UnkStruct_020f9408_2 *);
extern void func_020f92d0(UnkStruct_020f9408_2 *);
extern void func_020f920c(UnkStruct_020f9408_2 *);
extern void func_020f8fa8(UnkStruct_020f9408_2 *);
extern void NNS_SndPlayerReadVariable(UnkStruct_020f9408 **, int, short *);

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
    func_020f92d0(self);
    func_020f920c(self);

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
    func_020f8fa8(self);
}
