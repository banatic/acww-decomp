/* func_ov009_02264f68 @ 0x02264f68, 0x50 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct SelfType {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x294 - 0x68];
    int unk_294;
    int unk_298;
    int unk_29C;
    int unk_2A0;
    int unk_2A4;
} SelfType;

typedef struct PType {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
} PType;

extern void *func_ov009_02264884(void *);

void func_ov009_02264f68(SelfType *self)
{
    PType *p;
    int a;
    int b;
    int c;

    p = (PType *) func_ov009_02264884(self);
    if (p != 0) {
        a = self->unk_64 + p->unk_44;
        b = self->unk_60;
        c = self->unk_5C + p->unk_40;
        self->unk_294 = c;
        self->unk_298 = b;
        self->unk_29C = a;
        self->unk_2A0 = p->unk_48;
        self->unk_2A4 = p->unk_4C;
    }
}
