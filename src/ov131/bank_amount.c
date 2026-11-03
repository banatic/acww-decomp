/* bank_amount: 8 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229af0c @ 0x0229af0c, 0x18 bytes, Thumb
 * func_ov131_0229aee4 @ 0x0229aee4, 0x28 bytes, Thumb
 * func_ov131_0229ae0c @ 0x0229ae0c, 0xd8 bytes, Thumb
 * func_ov131_0229ad5c @ 0x0229ad5c, 0xb0 bytes, Thumb
 * func_ov131_0229ad44 @ 0x0229ad44, 0x18 bytes, Thumb
 * func_ov131_0229ad34 @ 0x0229ad34, 0x10 bytes, Thumb
 * func_ov131_0229acf8 @ 0x0229acf8, 0x3c bytes, Thumb
 * func_ov131_0229acc0 @ 0x0229acc0, 0x38 bytes, Thumb
 */

struct UnkStruct_0229aee4 {
    unsigned char pad_00[0x8D];
    unsigned char unk_8D;
    unsigned char pad_8E[0x14C8];
    unsigned char unk_1556;
};

typedef struct {
    char pad_00[0x2c4];
    char unk_2C4;
} UnkStruct_0229ae0c;

struct UnkStruct_0229ad44 {
    unsigned char pad_00[0x1554];
    unsigned short flag;
};

typedef struct {
    void *unk_00;
    char pad_04[0x90];
    char unk_94[4];
    char pad_98[0x60];
    char unk_F8[4];
    char pad_FC[0x1c8];
    char unk_2C4[4];
} UnkStruct_0229acc0;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *p);
extern int func_0206fca4(void);
extern void *func_020984e8(void);
extern int func_020992fc(int argument0);
extern int func_020983f0(int a);
extern int func_02099734(void *h);
extern int func_02098cf8(int a, int b);
extern int func_02098cc0(int a, int b, int c);
extern int func_02060d3c(void *p);
extern void func_ov130_02299de0(void *p, int a, int b, int c);
extern char data_021ebcd4[];
extern int func_ov130_02299ddc(void *p);
extern int func_ov130_02299dd8(void *p);
extern int func_ov130_02299dd4(void *p);
extern void func_020983ec(int a, int b);
extern void func_02098a24(int a, int b, int c);
extern void func_02060d24(int a, int b);
extern void *func_ov130_0229a790(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern unsigned char data_ov131_0229b8f0[];

void func_ov131_0229af0c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098((void *) (self), 4);
}

void func_ov131_0229aee4(struct UnkStruct_0229aee4 *self)
{
    func_ov002_0220a164((char *) self + 0x94);
    self->unk_1556 = self->unk_8D;
    func_ov002_02208098((void *) (self), 5);
}

void func_ov131_0229ae0c(UnkStruct_0229ae0c *self)
{
    int hi;
    void *h;
    int q;
    int val;
    int kind;
    int cur;

    kind = func_0206fca4();
    h = func_020984e8();
    q = func_020992fc((int) h);

    switch (kind) {
        case 0x38:
            hi = 0x98967f;
            break;
        case 0x3a:
            hi = 0x63;
            break;
        case 0x36:
            hi = func_020983f0(q);
            break;
        default:
            hi = func_02098cf8(func_02099734(h), 1);
            break;
    }

    cur = 0;
    {
        char *p = data_021ebcd4;
        switch (kind) {
            case 0x34:
                cur = func_02060d3c(p);
                break;
            case 0x35:
                cur = func_020983f0(q);
                break;
            case 0x36:
                cur = func_02098cf8(func_02099734(h), 1);
                break;
        }
    }

    val = hi;
    switch (kind) {
        case 0x34:
            if (cur < hi) {
                val = cur;
            }
            break;
        case 0x35: {
            int d = 0x3b9ac9ff - cur;
            if (d < hi) {
                val = d;
            }
        } break;
        case 0x36: {
            int m = func_02098cc0(func_02099734(h), 1, 0);
            if (m < hi) {
                val = m;
            }
        } break;
    }

    func_ov130_02299de0(&self->unk_2C4, val, hi, cur);
}

void func_ov131_0229ad5c(void *obj)
{
    int r4;
    int r5;
    int r6;
    int r7;
    int local0;
    int local4;
    r4 = func_ov130_02299ddc(((char *) obj) + 0x2c4);
    local4 = func_ov130_02299dd8(((char *) obj) + 0x2c4);
    r6 = func_ov130_02299dd4(((char *) obj) + 0x2c4);
    r7 = (int) func_020984e8();
    local0 = func_020992fc(r7);
    r5 = func_0206fca4();
    switch (r5) {
        case 0x36:
            func_020983ec(local0, local4 - r4);
            break;

        case 0x37:

        default:
            func_02098a24(func_02099734((void *) r7), -r4, 1);
            break;

        case 0x38:

        case 0x39:

        case 0x3a:
            break;
    }

    if (r5 == 0x34) {
        goto L34;
    }
    if (r5 == 0x35) {
        goto L35;
    }
    if (r5 == 0x36) {
        goto L36;
    }
    goto Ldone;
Ldone:
    return;

L34:
    func_02060d24((unsigned int) ((unsigned char *) data_021ebcd4), r6 - r4);

    goto Ldone;
L35:
    func_020983ec(local0, r6 + r4);

    goto Ldone;
L36:
    func_02098a24(func_02099734((void *) r7), r4, 1);

    goto Ldone;
}

int func_ov131_0229ad44(struct UnkStruct_0229ad44 *s, unsigned short mask)
{
    if (s->flag & mask) {
        return 1;
    }
    return 0;
}

void func_ov131_0229ad34(char *base, int value)
{
    *(unsigned short *) (base + 0x1554) |= value;
}

void *func_ov131_0229acf8(void *self)
{
    *(int *) self = (int) ((int *) data_ov131_0229b8f0);
    func_ov130_0229a790((char *) self + 0x2c4);
    func_ov002_0220afdc((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov131_0229acc0(UnkStruct_0229acc0 *self)
{
    self->unk_00 = (void *) data_ov131_0229b8f0;
    func_ov130_0229a790(&self->unk_2C4);
    func_ov002_0220afdc(&self->unk_F8);
    func_ov002_02209cb4(&self->unk_94);
    func_ov002_0220826c(self);
    return self;
}
