/* wfc_host_list_rows: 11 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_02299dec @ 0x02299dec, 0x3a bytes, Thumb
 * func_ov146_02299d84 @ 0x02299d84, 0x68 bytes, Thumb
 * func_ov146_02299d04 @ 0x02299d04, 0x7e bytes, Thumb
 * func_ov146_02299cbc @ 0x02299cbc, 0x48 bytes, Thumb
 * func_ov146_02299c44 @ 0x02299c44, 0x78 bytes, Thumb
 * func_ov146_02299c34 @ 0x02299c34, 0x10 bytes, Thumb
 * func_ov146_02299ba8 @ 0x02299ba8, 0x8c bytes, Thumb
 * func_ov146_02299b80 @ 0x02299b80, 0x28 bytes, Thumb
 * func_ov146_02299b58 @ 0x02299b58, 0x28 bytes, Thumb
 * func_ov146_02299b1c @ 0x02299b1c, 0x3c bytes, Thumb
 * func_ov146_02299af4 @ 0x02299af4, 0x28 bytes, Thumb
 */

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} Self_t;

typedef struct UnkStruct_02299cbc {
    int pad_00;
} UnkStruct_02299cbc;

typedef struct UnkStruct_02299cbc_2 {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    int unk_A0;
    char pad_A4[0x1F10];
    UnkStruct_02299cbc sub;
} UnkStruct_02299cbc_2;

typedef struct {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    int unk_A0;
    char pad_A4[0x1fb4 - 0xa4];
    char unk_1FB4;
} UnkStruct_02299c44;

struct UnkStruct_02299ba8 {
    char pad_00[0x98];
    int unk_98;
};

extern void func_0200284c(int, int, int);
extern void func_ov146_02299660(int, int);
extern void MIi_CpuClear16(unsigned short a, char *b, unsigned int c);
extern void MIi_CpuCopy16(char *dst, char *src, unsigned int size);
extern int func_ov002_0220a58c(UnkStruct_02299cbc *, int arg1, int arg2);
extern void func_ov002_0220a574(UnkStruct_02299cbc *);
extern int func_020e895c(void *p, int v, int n);
extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov002_0220a568(void *p);
extern unsigned short data_021fbe40;
extern int func_0208e930(char *p);
extern void func_ov002_0220a580(char *p);
extern void func_0208ea70(void *dest, int size, int value);
extern int _s32_div_f(void *, int);

void func_ov146_02299d84(char *obj);
void func_ov146_02299b58(char *p);
void func_ov146_02299b1c(void *self);
void func_ov146_02299af4(void *self);

void func_ov146_02299dec(int *param1, int param2)
{
    int *p;
    int temp;

    p = (int *) ((char *) param1 + 0xa4);
    *p = param2;
    func_0200284c(4, 0, *p - 0x38);
    temp = param2 >> 4;
    *(short *) ((char *) param1 + 0xae) = (short) temp;
    func_ov146_02299d84((char *) ((int) param1));
    func_ov146_02299660((int) param1, 4);
}

void func_ov146_02299d84(char *obj)
{
    volatile unsigned short tmp = 16;
    int i;

    MIi_CpuClear16(tmp, obj + 0xd8a, 0x800);

    for (i = 0; i < 7; i++) {
        int sum = *(short *) (obj + 0xae) + i;
        int rem = sum % 7;
        char *dst = obj + 0x58a + ((rem * 2 + 7) * 64);
        char *src = obj + 0xd8a + ((sum & 0xf) * 128);
        MIi_CpuCopy16(dst, src, 128);
    }

    func_ov146_02299660((int) obj, 2);
}

int func_ov146_02299d04(Self_t *self)
{
    if (self->unk_A4 != self->unk_A8) {
        if (self->unk_A4 > self->unk_A8) {
            self->unk_A4 -= 6;
            if (self->unk_A4 < self->unk_A8) {
                self->unk_A4 = self->unk_A8;
            }
        } else {
            self->unk_A4 += 6;
            if (self->unk_A4 > self->unk_A8) {
                self->unk_A4 = self->unk_A8;
            }
        }
        func_ov146_02299dec((int *) self, self->unk_A4);
        func_ov146_02299af4((void *) self);
        return 1;
    } else {
        return 0;
    }
}

int func_ov146_02299cbc(UnkStruct_02299cbc_2 *self, int unused, int value)
{
    if (func_ov002_0220a58c(&self->sub, unused, value)) {
        self->unk_9C = self->unk_98 - value;
        func_ov002_0220a574(&self->sub);
        self->unk_A0 = self->unk_98;
        return 1;
    } else {
        return 0;
    }
}

void func_ov146_02299c44(UnkStruct_02299c44 *obj, int param2, int param3)
{
    if (param3 != 0) {
        param2 -= 0x40;
    } else {
        param2 += obj->unk_9C;
    }

    if (param2 < 0) {
        param2 = 0;
    }
    if (param2 > 0x50) {
        param2 = 0x50;
    }

    if (param3 != 0) {
        func_020e895c(&obj->unk_98, param2, 8);
    } else {
        obj->unk_98 = param2;
    }

    func_ov146_02299b1c(obj);
    func_ov146_02299b58((char *) obj);

    {
        int diff = obj->unk_A0 - obj->unk_98;

        if (diff < 4) {
            if (diff > -4) {
                return;
            }
        }

        func_ov002_0220a4c8(&obj->unk_1FB4);
        obj->unk_A0 = obj->unk_98;
    }
}

void func_ov146_02299c34(void *p)
{
    func_ov002_0220a568((char *) p + 0x1fb4);
}

void func_ov146_02299ba8(struct UnkStruct_02299ba8 *self)
{
    int old = self->unk_98;
    unsigned short flags = data_021fbe40;

    if (flags & 0x40) {
        self->unk_98 -= 4;
        if (self->unk_98 < 0) {
            self->unk_98 = 0;
        }
    } else if (flags & 0x80) {
        self->unk_98 += 4;
        if (self->unk_98 > 0x50) {
            self->unk_98 = 0x50;
        }
    }

    if (old != self->unk_98) {
        func_ov146_02299b1c(self);
        func_ov146_02299b58((char *) self);
        func_ov002_0220a4c8((char *) self + 0x1fb4);
    }
}

int func_ov146_02299b80(char *p)
{
    if (func_0208e930(p + 0x1fb4) != 0) {
        func_ov002_0220a580(p + 0x1fb4);
        return 1;
    }
    return 0;
}

void func_ov146_02299b58(char *p)
{
    func_0208ea70(p + 0x1fb4, 0x62, *(int *) (p + 0x94) + (*(int *) (p + 0x98) - 0x28));
}

void func_ov146_02299b1c(void *self)
{
    int r0;
    int r4;
    int r5;
    int temp;

    r5 = (int) self;
    r0 = *(int *) (r5 + 0x98);
    r0 = r0 * 0x1a0;
    r4 = _s32_div_f((void *) r0, 0x50);
    if (r4 < 0) {
        r4 = 0;
    }
    if (r4 > 0x1a0) {
        r4 = 0x1a0;
    }
    func_ov146_02299dec((int *) ((void *) r5), r4);
    *(int *) (r5 + 0xa8) = r4;
}

void func_ov146_02299af4(void *self)
{
    int index;
    void *ptr;

    index = *(int *) ((char *) self + 0xa4);
    ptr = (void *) _s32_div_f((void *) (index * 0x50), 0x1a0);
    *(void **) ((char *) self + 0x98) = ptr;
    func_ov146_02299b58((char *) self);
}
