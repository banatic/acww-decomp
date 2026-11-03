/* carried_letters_9: 8 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229d6f0 @ 0x0229d6f0, 0x34 bytes, Thumb
 * func_ov103_0229d664 @ 0x0229d664, 0x8c bytes, Thumb
 * func_ov103_0229d580 @ 0x0229d580, 0xe4 bytes, Thumb
 * func_ov103_0229d4e4 @ 0x0229d4e4, 0x9c bytes, Thumb
 * func_ov103_0229d450 @ 0x0229d450, 0x94 bytes, Thumb
 * func_ov103_0229d430 @ 0x0229d430, 0x20 bytes, Thumb
 * func_ov103_0229d3b4 @ 0x0229d3b4, 0x7c bytes, Thumb
 * func_ov103_0229d364 @ 0x0229d364, 0x50 bytes, Thumb
 */

typedef struct UnkStruct_0229d580_2 UnkStruct_0229d580;

struct UnkStruct_0229d580_2 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x218c - 0x8d];
    int unk_218C;
    unsigned char pad_2190[0x2da4 - 0x2190];
    unsigned char unk_2DA4;
};

typedef struct {
    unsigned char pad_00[0x2da3];
    unsigned char unk_2DA3;
    unsigned char unk_2DA4;
} UnkStruct_0229d4e4;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_0229d450;

struct UnkStruct_0229d364 {
    char pad_00[0x26c5];
    unsigned char array[0x6e3];
    unsigned char b0;
    unsigned char b1;
};

extern int func_ov002_02208054(int a1, int a2);
extern int func_ov002_0220b498(void *);
extern void func_ov103_0229c30c(int a1);
extern unsigned char data_021fbdd8; // 0x021fbdd8
extern unsigned char data_021fbddc; // 0x021fbddc
extern unsigned char data_021f6c58; // 0x021f6c58
extern unsigned char data_021f6c54; // 0x021f6c54
extern void func_ov103_0229c4fc(void *self);
extern int func_ov002_02208b00(void *ptr, int a, int b);
extern void func_ov002_02209114(void *ptr, int a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229d580 *self);
extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_02207d00(void *ptr);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229d580 *self, unsigned char value);
extern int func_ov103_0229c350(UnkStruct_0229d580 *self, int a, int b);
extern void func_ov103_0229cffc(UnkStruct_0229d580 *self);
extern void func_ov103_0229ca48(UnkStruct_0229d580 *self);
extern void func_ov103_0229c774(UnkStruct_0229d580 *self);
extern int func_ov103_0229cc3c(UnkStruct_0229d580 *self, unsigned char byte);
extern int func_ov103_0229cdfc(UnkStruct_0229d580 *self, unsigned char byte);
extern int func_ov103_0229cc08(UnkStruct_0229d580 *self, unsigned char byte);
extern void func_ov103_0229c444(UnkStruct_0229d580 *self, unsigned char byte);
extern void func_ov103_0229c7ec(UnkStruct_0229d580 *self);
extern void func_ov103_0229c2d4(UnkStruct_0229d580 *self, int value);
extern volatile unsigned short data_021fbe40[2];
extern void func_ov103_0229c604(void *, unsigned char);
extern void func_ov103_0229c5b8(void *, unsigned char);
extern void func_ov103_0229c994(void *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220b5ec(unsigned char *, int);
extern int func_ov002_0220b59c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern void func_ov002_0220a1dc(unsigned char *);
extern int func_0208e484(void *);
extern int func_ov002_02209044(char *p, int a, char *q, int b);
extern void func_ov103_0229c720(char *p);

void func_ov103_0229d6f0(int a1)
{
    int v1;
    int v2;

    v1 = func_ov002_02208054(a1, 1);
    if (v1 != 0) {
        func_ov002_02208098((void *) a1, 7);
        return;
    }
    v2 = func_ov002_0220b498((void *) (a1 + 0x2b10));
    if (v2 != 0) {
        func_ov103_0229c30c(a1);
    }
}

void func_ov103_0229d664(unsigned char *self)
{
    if (func_ov002_02208054((int) self, 1) != 0) {
        func_ov103_0229c4fc(self);
    } else {
        unsigned int cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (cond > 0) {
            int ret = func_ov002_02208b00(self + 0x22d8, data_021f6c58, data_021f6c54);
            if (ret >= 0) {
                func_ov002_02209114(self + 0x22d8, ret, 1);
                *(self + 0x2da8) = *(self + ret + 0x26c5);
                func_ov002_02208098(self, 0x15);
            }
        }
    }
}

void func_ov103_0229d580(UnkStruct_0229d580 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov103_0229cffc(self);
        func_ov002_02207d24(&self->unk_218C, 1);
        return;
    }

    if (func_ov103_0229c350(self, func_ov002_02208008(self), 0) != 0) {
        func_ov103_0229ca48(self);
        func_ov103_0229c774(self);
        func_ov002_02207d24(&self->unk_218C, 0);
        return;
    }

    if (func_ov103_0229cc3c(self, self->unk_2DA4) == 0 && (data_021fbe40[1] & 1) != 0) {
        if (func_ov103_0229cdfc(self, self->unk_2DA4) == 0) {
            return;
        }
        if (func_ov103_0229cc08(self, self->unk_2DA4) == 0) {
            func_ov103_0229c444(self, self->unk_2DA4);
        }
        return;
    }

    if ((data_021fbe40[1] & 0x800) != 0) {
        self->unk_8C = 3;
        func_ov002_022080a0(self, 1);
        func_ov002_02207d24(&self->unk_218C, 1);
        func_ov103_0229c7ec(self);
        func_ov103_0229c2d4(self, 0x100);
        return;
    }

    func_ov002_02207d00(&self->unk_218C);
}

void func_ov103_0229d4e4(UnkStruct_0229d4e4 *self)
{
    if (func_ov103_0229c350((UnkStruct_0229d580 *) self, func_ov002_02208008((UnkStruct_0229d580 *) self), 1) != 0) {
        func_ov103_0229ca48((UnkStruct_0229d580 *) self);
        func_ov103_0229c774((UnkStruct_0229d580 *) self);
        func_ov002_02207d24((char *) self + 0x218c, 0);
        return;
    }

    {
        unsigned short flags = ((unsigned short *) data_021fbe40)[1];

        if (flags & 1) {
            if (func_ov103_0229cc08((UnkStruct_0229d580 *) self, self->unk_2DA4) != 0) {
                func_ov103_0229c604(self, self->unk_2DA4);
                return;
            } else {
                func_ov103_0229c5b8(self, self->unk_2DA4);
                return;
            }
        } else if (flags & 2) {
            func_ov103_0229c604(self, self->unk_2DA3);
            return;
        } else {
            func_ov103_0229c994(self);
            func_ov002_02207d00((char *) self + 0x218c);
        }
    }
}

void func_ov103_0229d450(unsigned char *p)
{
    if (func_0208e4bc(p + 0x2274) == 0) {
        int a = func_ov002_0220b5ec(p + 0x2b10, 1);
        int b = func_ov002_0220b59c(p + 0x2b10, 1);
        func_ov002_0220a0b4(p + 0x2274, a, b);
        func_ov002_0220a374(p + 0x2274, 1);
    }
    if (func_ov002_02208014(p) != 0) {
        func_ov103_0229c7ec((UnkStruct_0229d580 *) p);
        func_ov002_02208098((void *) p, 3);
    } else {
        if ((((*(UnkStruct_0229d450 *) data_021fbe40).unk_02 & 1) != 0) || (((*(UnkStruct_0229d450 *) data_021fbe40).unk_02 & 2) != 0)) {
            func_ov002_0220a1dc(p + 0x2274);
            func_ov002_02208098((void *) p, 8);
        }
    }
}

void func_ov103_0229d430(void *self)
{
    if (func_0208e484((char *) self + 0x2274)) {
        func_ov103_0229c30c((int) self);
    }
}

void func_ov103_0229d3b4(char *p)
{
    if (func_ov002_02208014(p)) {
        func_ov103_0229c4fc((void *) p);
        return;
    }
    if (func_ov002_02209044(p + 0x22d8, func_ov002_02208008((UnkStruct_0229d580 *) p), p + 0x2da9, 0)) {
        func_ov103_0229c720(p);
        return;
    }
    if (((unsigned short *) data_021fbe40)[1] & 1) {
        func_ov002_0220a1dc((unsigned char *) (p + 0x2274));
        func_ov002_02208098((void *) p, 0xA);
        return;
    }
    if (((unsigned short *) data_021fbe40)[1] & 2) {
        func_ov103_0229c4fc((void *) p);
    }
}

void func_ov103_0229d364(struct UnkStruct_0229d364 *self)
{
    if (func_0208e484((void *) ((char *) self + 0x2274)) == 0) {
        return;
    }
    func_ov002_02209114((void *) ((char *) self + 0x22d8), self->b1, 1);
    self->b0 = self->array[self->b1];
    func_ov002_02208098(self, 0x15);
}
