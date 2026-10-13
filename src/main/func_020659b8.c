/* func_020659b8 @ 0x020659b8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char pad_04[4];
    unsigned char unk_08;
    unsigned char pad_09[1];
} RecT;

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
    int unk_54;
    unsigned char pad_58[0x16a - 0x58];
    unsigned short unk_16A;
    unsigned short unk_16C;
    unsigned short unk_16E;
    unsigned short unk_170;
    unsigned char pad_172[0x178 - 0x172];
    unsigned char unk_178;
} SelfT;

extern SelfT *data_021cd864;
extern int func_020b65c4(void);
extern unsigned char data_020ccc48[];
extern RecT data_020ccc7c[];
extern void func_02065a7c(SelfT *self);
extern void func_02065218(void *rec);
extern void func_02064e28(void *rec);
extern void func_020654c8(void *addr);

int func_020659b8(SelfT *self)
{
    int idx;

    data_021cd864 = self;
    idx = func_020b65c4();
    self->unk_50 = data_020ccc48[idx];

    if (idx == 0x21) {
        self->unk_16A = 0x3e99;
        self->unk_16C = 0x3caa;
        self->unk_16E = 0x494a;
        self->unk_170 = 0x518c;
        self->unk_178 = 0xb;
    } else {
        RecT *rec = &data_020ccc7c[idx];
        self->unk_16A = rec->unk_00;
        self->unk_16C = 0;
        self->unk_16E = rec->unk_02;
        self->unk_170 = 0;
        self->unk_178 = rec->unk_08;
    }

    func_02065a7c(self);

    {
        unsigned char *p = (unsigned char *) self + 0x58;
        int i;
        for (i = 0; i < self->unk_54; i++) {
            func_02065218(p);
            func_02064e28(p);
            p += 0x44;
        }
    }

    func_020654c8((unsigned char *) self + 0x124);

    return 1;
}
