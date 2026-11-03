/* design_editor_input_6: 12 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229b77c @ 0x0229b77c, 0x3c bytes, Thumb
 * func_ov123_0229b754 @ 0x0229b754, 0x28 bytes, Thumb
 * func_ov123_0229b6e8 @ 0x0229b6e8, 0x6c bytes, Thumb
 * func_ov123_0229b6d0 @ 0x0229b6d0, 0x16 bytes, Thumb
 * func_ov123_0229b67c @ 0x0229b67c, 0x52 bytes, Thumb
 * func_ov123_0229b65c @ 0x0229b65c, 0x20 bytes, Thumb
 * func_ov123_0229b644 @ 0x0229b644, 0x16 bytes, Thumb
 * func_ov123_0229b620 @ 0x0229b620, 0x24 bytes, Thumb
 * func_ov123_0229b600 @ 0x0229b600, 0x20 bytes, Thumb
 * func_ov123_0229b5cc @ 0x0229b5cc, 0x34 bytes, Thumb
 * func_ov123_0229b598 @ 0x0229b598, 0x34 bytes, Thumb
 * func_ov123_0229b56c @ 0x0229b56c, 0x2c bytes, Thumb
 */

struct UnkStruct_0229b77c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[23];
    unsigned char unk_A5;
    unsigned char pad_A6[4];
    unsigned char unk_AA;
    unsigned char pad_AB[289];
    char unk_1CC;
};

struct UnkStruct_0229b6e8 {
    char pad_00[0x1cc];
    unsigned char unk_1CC;
    char pad_1CD[0x4e63];
    unsigned char unk_5030;
};

struct UnkStruct_0229b67c {
    unsigned char pad_00[0xac];
    unsigned char unk_AC;
    unsigned char pad_AD[2];
    unsigned char unk_AF;
};

typedef struct {
    char pad_00[0xaa];
    unsigned char unk_AA;
} UnkStruct_0229b620;

extern int func_0208e484(void *p);
extern void func_ov123_0229ae84(struct UnkStruct_0229b77c *self);
extern void func_ov123_02299ca0(struct UnkStruct_0229b77c *self);
extern void func_ov123_02299ce0(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_0220a700(void *p);
extern int func_0208e4bc(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int x);
extern int func_ov002_0220a72c(void *p, int x);
extern void func_ov002_0220a0b4(void *p, int x, int y);
extern void func_ov123_02299d00(void *p);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov123_02299d44(struct UnkStruct_0229b67c *);
extern int func_ov123_0229ae7c(struct UnkStruct_0229b67c *, unsigned char);
extern void func_020041bc(int);
extern void func_ov002_02207fb0(struct UnkStruct_0229b67c *, int, int, int);
extern void func_ov002_02207fc0(struct UnkStruct_0229b67c *);
extern int func_0206fe60(void);
extern void func_0200467c(int);
extern void func_ov123_02299630(void *, int);
extern void func_ov123_02299640(void *self, int arg);
extern void func_ov002_02208090(unsigned int, unsigned int);
extern void *func_ov002_0220a720(unsigned int, unsigned int);

void func_ov123_0229b56c(unsigned int a, unsigned int b, unsigned int c);

void func_ov123_0229b77c(struct UnkStruct_0229b77c *self)
{
    if (func_0208e484(&self->unk_1CC)) {
        self->unk_A5 = self->unk_AA;
        func_ov123_0229ae84(self);
        if (self->unk_8D == 0xa) {
            func_ov123_02299ca0(self);
        }
    }
}

void func_ov123_0229b754(void *self)
{
    if (func_0208e484((char *) self + 0x1cc)) {
        func_ov123_02299ce0(self);
        func_ov002_02208098(self, 3);
    }
}

void func_ov123_0229b6e8(struct UnkStruct_0229b6e8 *self)
{
    if (func_ov002_0220a700(&self->unk_5030)) {
        if (func_0208e4bc(&self->unk_1CC)) {
            int v1 = func_ov002_0220a6e0(&self->unk_5030);
            int v2 = func_ov002_0220a768(&self->unk_5030, -1);
            int v3 = func_ov002_0220a72c(&self->unk_5030, -1);
            func_ov002_0220a0b4(&self->unk_1CC, v1 + v2, v1 + v3);
        }
    } else {
        func_ov123_02299d00(self);
        func_ov002_022080a0(self, 1);
    }
}

void func_ov123_0229b6d0(int r0)
{
    func_ov002_02208098((void *) r0, 0);
    func_ov123_02299d00((void *) r0);
}

void func_ov123_0229b67c(struct UnkStruct_0229b67c *param)
{
    if (param->unk_AC == 2) {
        func_ov123_02299d00((void *) param);
        func_ov002_02207fb0(param, 5, 0, 5);
        func_ov002_02208098((void *) param, 4);
        func_020041bc((unsigned char) func_ov123_0229ae7c(param, param->unk_AF));
    } else {
        func_ov123_02299d44(param);
        func_ov002_02207fc0(param);
        func_ov002_02208098((void *) param, 3);
    }
}

void func_ov123_0229b65c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov123_0229b6d0(r4);
    } else {
        func_ov123_0229b67c((struct UnkStruct_0229b67c *) r4);
    }
}

void func_ov123_0229b644(int param)
{
    int r4 = param;
    func_ov123_02299d00((void *) param);
    func_ov002_02208098((void *) r4, 1);
}

void func_ov123_0229b620(UnkStruct_0229b620 *self)
{
    func_ov002_02207fc0((struct UnkStruct_0229b67c *) self);
    self->unk_AA = 0x20;
    func_ov123_02299d44((struct UnkStruct_0229b67c *) self);
    func_ov002_02208098(self, 8);
}

void func_ov123_0229b600(void *param)
{
    if (func_0206fe60() != 0) {
        func_ov123_0229b644((int) param);
    } else {
        func_ov123_0229b620((UnkStruct_0229b620 *) param);
    }
}

void func_ov123_0229b5cc(void *r0)
{
    void *r4 = r0;
    func_0200467c(0x29);
    func_ov123_02299630(r4, 8);
    if (((unsigned char *) r4)[0xac] == 2) {
        ((unsigned char *) r4)[0xac] = 0;
    }
    func_ov123_0229b56c((unsigned int) r4, 6, 9);
}

void func_ov123_0229b598(void *self)
{
    func_0200467c(0x2a);
    func_ov123_02299640(self, 8);
    if (*(unsigned char *) ((char *) self + 0xac) == 2) {
        *(unsigned char *) ((char *) self + 0xac) = 0;
    }
    func_ov123_0229b56c((unsigned int) self, 6, 8);
}

void func_ov123_0229b56c(unsigned int a, unsigned int b, unsigned int c)
{
    func_ov002_02208090(a, b);
    func_ov002_0220a720(a + 0x5030, c);
    func_ov002_02208098((void *) a, 12);
}
