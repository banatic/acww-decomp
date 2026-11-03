/* phone_clock: 8 functions, module ov135
 * mwccarm 1.2/base -O4,s
 * func_ov135_0229c654 @ 0x0229c654, 0x18 bytes, Thumb
 * func_ov135_0229c630 @ 0x0229c630, 0x24 bytes, Thumb
 * func_ov135_0229c588 @ 0x0229c588, 0xa8 bytes, Thumb
 * func_ov135_0229c574 @ 0x0229c574, 0x12 bytes, Thumb
 * func_ov135_0229c564 @ 0x0229c564, 0xe bytes, Thumb
 * func_ov135_0229c554 @ 0x0229c554, 0xe bytes, Thumb
 * func_ov135_0229c518 @ 0x0229c518, 0x3c bytes, Thumb
 * func_ov135_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb
 */

typedef struct UnkStruct_0229c630 UnkStruct_0229c630;

struct UnkStruct_0229c630 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x6];
    unsigned char unk_94;
    char pad_95[0x3];
    unsigned char unk_98;
};

struct UnkStruct_0229c564 {
    char pad_00[0x92];
    unsigned short flags;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char v);
extern void func_ov002_0220a164(void *p);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern const unsigned char data_ov135_0229d4fc[];
extern const unsigned char data_ov135_0229d504[];
extern const unsigned char data_ov135_0229d514[];
extern const unsigned char data_ov135_0229d50c[];
extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern char data_ov135_0229d610;

void func_ov135_0229c654(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x98);
    func_ov002_02208098(self, 0xb);
}

void func_ov135_0229c630(UnkStruct_0229c630 *self)
{
    func_ov002_0220a164(&self->unk_98);
    self->unk_94 = self->unk_8D;
    func_ov002_02208098((void *) (self), 12);
}

int func_ov135_0229c588(void *self, void *arg)
{
    unsigned char old;
    unsigned char *p;

    p = (unsigned char *) self + 0x95;
    old = *p;

    if (func_ov002_022088ac(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d4fc[*p];
    } else if (func_ov002_0220889c(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d504[*p];
    }

    p = (unsigned char *) self + 0x95;
    if (old != *p) {
        return 1;
    }

    if (func_ov002_022088cc(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d514[*p];
    } else if (func_ov002_022088bc(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d50c[*p];
    }

    p = (unsigned char *) self + 0x95;
    if (old != *p) {
        return 1;
    }

    return 0;
}

int func_ov135_0229c574(char *p, unsigned int mask)
{
    unsigned int tmp;
    tmp = *(unsigned short *) (p + 0x92) & mask;
    if (tmp == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov135_0229c564(struct UnkStruct_0229c564 *p, unsigned short val)
{
    p->flags |= val;
}

void func_ov135_0229c554(unsigned short *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x92);
    r2 &= ~r1;
    *(unsigned short *) ((char *) r0 + 0x92) = r2;
}

void *func_ov135_0229c518(void *self)
{
    *(void **) self = &data_ov135_0229d610;
    func_ov134_0229beb0((char *) self + 0x2C8);
    func_ov002_0220afdc((char *) self + 0xFC);
    func_ov002_02209cb4((char *) self + 0x98);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov135_0229c4e0(void *p)
{
    *(unsigned int *) p = (unsigned int) ((unsigned int *) &data_ov135_0229d610);
    func_ov134_0229beb0((char *) p + 0x2c8);
    func_ov002_0220afdc((char *) p + 0xfc);
    func_ov002_02209cb4((char *) p + 0x98);
    func_ov002_0220826c(p);
    return p;
}
