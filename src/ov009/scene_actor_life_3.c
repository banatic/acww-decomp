/* scene_actor_life_3: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264fb8 @ 0x02264fb8, 0x6c bytes, Thumb
 * func_ov009_02264f68 @ 0x02264f68, 0x50 bytes, Thumb
 */

struct UnkStruct_02264fb8 {
    unsigned char pad_00[0x136];
    unsigned char unk_136[6];
    unsigned char unk_13C[1];
    unsigned char pad_13D[0xf9];
    unsigned char b0 : 1;
    unsigned char pad_237[1];
    unsigned char unk_238[1];
};

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

extern void *func_0203efdc(void *self);
extern void func_ov009_02262f0c(void *p);
extern void func_ov009_02264580(struct UnkStruct_02264fb8 *self);
extern void func_ov009_02264398(struct UnkStruct_02264fb8 *self);
extern int func_02055f1c(void *p);
extern int func_ov003_02220240(struct UnkStruct_02264fb8 *self);
extern void func_0203f364(void);
extern int func_0204bba8(void *p);
extern void func_020ad78c(int n);
extern void *func_ov009_02264884(void *);

int func_ov009_02264fb8(struct UnkStruct_02264fb8 *self)
{
    if (!func_0203efdc(self)) {
        return 0;
    }
    func_ov009_02262f0c(self->unk_238);
    func_ov009_02264580(self);
    func_ov009_02264398(self);
    func_02055f1c(self->unk_13C);
    func_ov003_02220240(self);
    if (self->b0) {
        func_0203f364();
        if (func_0204bba8(self->unk_136) != 0) {
            func_020ad78c(1);
        }
    }
    return 1;
}

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
