/* donation_list_5: 10 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229a2e0 @ 0x0229a2e0, 0x30 bytes, Thumb
 * func_ov145_0229a298 @ 0x0229a298, 0x48 bytes, Thumb
 * func_ov145_0229a220 @ 0x0229a220, 0x78 bytes, Thumb
 * func_ov145_0229a210 @ 0x0229a210, 0x10 bytes, Thumb
 * func_ov145_0229a184 @ 0x0229a184, 0x8c bytes, Thumb
 * func_ov145_0229a15c @ 0x0229a15c, 0x28 bytes, Thumb
 * func_ov145_0229a134 @ 0x0229a134, 0x28 bytes, Thumb
 * func_ov145_0229a0fc @ 0x0229a0fc, 0x36 bytes, Thumb
 * func_ov145_0229a0d0 @ 0x0229a0d0, 0x2c bytes, Thumb
 * func_ov145_0229a080 @ 0x0229a080, 0x50 bytes, Thumb
 */

typedef struct {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
} UnkStruct_0229a298;

typedef struct UnkStruct_0229a220 {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x78];
    int unk_12C;
} UnkStruct_0229a220;

struct UnkStruct_0229a184 {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0x80];
    char unk_12C[1];
};

typedef struct {
    char pad_00[0x94];
    int unk_94;
    char pad_98[0x10];
    int unk_A8;
    char pad_AC[0x80];
    char unk_12C;
} struct_ov145_0229a134;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV145_0229A0FC_STRUCT;

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
} OV142_02299A54_STRUCT;

extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(void *, int);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220a58c(void *p, int unused1, int unused2);
extern void func_ov002_0220a574(void *p);
extern int func_020e895c(void *ptr, int value, int size);
extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov002_0220a568(int);
extern unsigned short data_021fbe40;
extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);
extern void func_0208ea70(void *a, int b, int c);
extern void func_ov145_02299b94(OV145_0229A0FC_STRUCT *, int);
extern int func_02071298(int addr, unsigned short *ptr);
extern unsigned char data_021f38f8[];

void func_ov145_0229a134(struct_ov145_0229a134 *p);
void func_ov145_0229a0fc(OV145_0229A0FC_STRUCT *self);

void func_ov145_0229a2e0(void *self)
{
    func_0206fc4c(1);
    func_ov002_0220a720((char *) self + 0x174, 6);
    func_ov002_02208090(self, 2);
    func_ov002_02208098((void *) (self), 9);
}

int func_ov145_0229a298(UnkStruct_0229a298 *self, int unused, int delta)
{
    if (func_ov002_0220a58c((char *) self + 0x12c, unused, delta)) {
        self->unk_AC = self->unk_A8 - delta;
        func_ov002_0220a574((char *) self + 0x12c);
        self->unk_B0 = self->unk_A8;
        return 1;
    } else {
        return 0;
    }
}

void func_ov145_0229a220(UnkStruct_0229a220 *self, int value, int flag)
{
    int clamped;
    int diff;

    if (flag) {
        clamped = value - 0x1d;
    } else {
        clamped = value + self->unk_AC;
    }
    if (clamped < 0) {
        clamped = 0;
    }
    if (clamped > 0x78) {
        clamped = 0x78;
    }

    if (flag) {
        func_020e895c(&self->unk_A8, clamped, 8);
    } else {
        self->unk_A8 = clamped;
    }

    func_ov145_0229a0fc((OV145_0229A0FC_STRUCT *) self);
    func_ov145_0229a134((struct_ov145_0229a134 *) self);

    diff = self->unk_B0 - self->unk_A8;
    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(&self->unk_12C);
        self->unk_B0 = self->unk_A8;
    }
}

int func_ov145_0229a210(int arg)
{
    return func_ov002_0220a568(arg + 0x12c);
}

void func_ov145_0229a184(struct UnkStruct_0229a184 *self)
{
    int orig = self->unk_A8;
    if (data_021fbe40 & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (data_021fbe40 & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 0x78) {
            self->unk_A8 = 0x78;
        }
    }
    if (orig != self->unk_A8) {
        func_ov145_0229a0fc((OV145_0229A0FC_STRUCT *) self);
        func_ov145_0229a134((struct_ov145_0229a134 *) self);
        func_ov002_0220a4c8(self->unk_12C);
    }
}

int func_ov145_0229a15c(void *arg0)
{
    if (func_0208e930((char *) arg0 + 0x12c)) {
        func_ov002_0220a580((char *) arg0 + 0x12c);
        return 1;
    }
    return 0;
}

void func_ov145_0229a134(struct_ov145_0229a134 *p)
{
    func_0208ea70(&p->unk_12C, 0x63, p->unk_94 + (p->unk_A8 - 0x4b));
}

void func_ov145_0229a0fc(OV145_0229A0FC_STRUCT *self)
{
    int result;
    int a = self->unk_A4;
    result = (self->unk_A8 * a) / 0x78;
    if (result < 0) {
        result = 0;
    }
    if (result > a) {
        result = a;
    }
    func_ov145_02299b94(self, result);
    self->unk_A0 = result;
}

void func_ov145_0229a0d0(OV142_02299A54_STRUCT *self)
{
    if (self->unk_A4 > 0) {
        self->unk_A8 = (self->unk_9C * 120) / self->unk_A4;
        func_ov145_0229a134((struct_ov145_0229a134 *) self);
    }
}

int func_ov145_0229a080(int unused, unsigned short *arr, unsigned short start, int count, int delta)
{
    int n = 0;
    unsigned short cur = 0xfff1;
    int i;

    for (i = 0; i < count; i++) {
        cur = start;
        if (func_02071298((unsigned int) data_021f38f8, &cur)) {
            arr[n] = start;
            n++;
        }
        start = (unsigned short) (start + delta);
    }
    return n;
}
