/* order_catalog_list_2: 17 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_02299c1c @ 0x02299c1c, 0x48 bytes, Thumb
 * func_ov142_02299ba4 @ 0x02299ba4, 0x78 bytes, Thumb
 * func_ov142_02299b94 @ 0x02299b94, 0x10 bytes, Thumb
 * func_ov142_02299b08 @ 0x02299b08, 0x8c bytes, Thumb
 * func_ov142_02299ae0 @ 0x02299ae0, 0x28 bytes, Thumb
 * func_ov142_02299ab8 @ 0x02299ab8, 0x28 bytes, Thumb
 * func_ov142_02299a80 @ 0x02299a80, 0x36 bytes, Thumb
 * func_ov142_02299a54 @ 0x02299a54, 0x2c bytes, Thumb
 * func_ov142_02299a24 @ 0x02299a24, 0x30 bytes, Thumb
 * func_ov142_02299a08 @ 0x02299a08, 0x1c bytes, Thumb
 * func_ov142_022999ec @ 0x022999ec, 0x1c bytes, Thumb
 * func_ov142_022999a4 @ 0x022999a4, 0x48 bytes, Thumb
 * func_ov142_02299938 @ 0x02299938, 0x6c bytes, Thumb
 * func_ov142_02299928 @ 0x02299928, 0x10 bytes, Thumb
 * func_ov142_02299918 @ 0x02299918, 0x10 bytes, Thumb
 * func_ov142_02299908 @ 0x02299908, 0x10 bytes, Thumb
 * func_ov142_02299830 @ 0x02299830, 0xd8 bytes, Thumb
 */

struct UnkStruct_02299c1c {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
};

struct UnkStruct_02299ba4 {
    char pad_00[0xA8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x14C - 0xB4];
    void *unk_14C;
};

struct UnkStruct_02299b08 {
    char pad_00[0xa8];
    int unk_A8;
};

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
    char pad_98[0x10];
    unsigned int unk_A8;
} UnkStruct_02299ab8;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV142_02299A80_STRUCT;

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
} OV142_02299A54_STRUCT;

typedef struct {
    char pad_00[0x9C];
    unsigned int unk_9C;
    unsigned int unk_A0;
    char pad_A4[0x14];
    short unk_B8;
    char pad_BA[4];
    unsigned char unk_BE;
} UnkStruct_022999a4;

typedef struct UnkStruct_02299938 UnkStruct_02299938;

struct UnkStruct_02299938 {
    unsigned char pad_00[0x9c];
    unsigned int unk_9C;
    unsigned int unk_A0;
    unsigned int unk_A4;
    unsigned char pad_A8[0xb4 - 0xa8];
    short unk_B4;
};

struct UnkStruct_02299830 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    char pad_A8[0x14c - 0xa8];
};

extern int func_ov002_0220a58c(void *p, int unused1, int unused2);
extern void func_ov002_0220a574(void *p);
extern int func_020e895c(void *addr, int val, int size);
extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov002_0220a568(void *arg);
extern unsigned short data_021fbe40;
extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);
extern void func_0208ea70(char *, unsigned int, unsigned int);
extern void func_ov142_0229a4d4(OV142_02299A80_STRUCT *, int);
extern void func_0206fdd4(unsigned short *buffer, int first_col, int first_row, int last_col, int last_row,
                          unsigned int value);
extern void func_ov142_02299658(int, int);
extern void func_ov142_02299648(void *param, int arg);
extern void func_ov142_0229ab80(UnkStruct_022999a4 *s, unsigned char b);
extern int func_ov142_0229a6d8(UnkStruct_02299938 *self);
extern int func_ov142_02299668(void *self, int arg);

void func_ov142_02299ab8(UnkStruct_02299ab8 *self);
void func_ov142_02299a80(OV142_02299A80_STRUCT *self);

int func_ov142_02299c1c(struct UnkStruct_02299c1c *self, int unused, int value)
{
    if (func_ov002_0220a58c((char *) self + 0x14c, unused, value) != 0) {
        self->unk_AC = self->unk_A8 - value;
        func_ov002_0220a574((char *) self + 0x14c);
        self->unk_B0 = self->unk_A8;
        return 1;
    }
    return 0;
}

void func_ov142_02299ba4(struct UnkStruct_02299ba4 *obj, int val, int flag)
{
    if (flag != 0) {
        val -= 0x34;
    } else {
        val += obj->unk_AC;
    }

    if (val < 0) {
        val = 0;
    }
    if (val > 90) {
        val = 90;
    }

    if (flag != 0) {
        func_020e895c(&obj->unk_A8, val, 8);
    } else {
        obj->unk_A8 = val;
    }

    func_ov142_02299a80((OV142_02299A80_STRUCT *) obj);
    func_ov142_02299ab8((UnkStruct_02299ab8 *) obj);

    {
        int diff = obj->unk_B0 - obj->unk_A8;
        if (diff >= 4 || diff <= -4) {
            func_ov002_0220a4c8(&obj->unk_14C);
            obj->unk_B0 = obj->unk_A8;
        }
    }
}

void func_ov142_02299b94(void *p)
{
    func_ov002_0220a568((char *) p + 0x14c);
}

void func_ov142_02299b08(struct UnkStruct_02299b08 *self)
{
    int old = self->unk_A8;
    if (data_021fbe40 & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (data_021fbe40 & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 90) {
            self->unk_A8 = 90;
        }
    }
    if (old != self->unk_A8) {
        func_ov142_02299a80((OV142_02299A80_STRUCT *) self);
        func_ov142_02299ab8((UnkStruct_02299ab8 *) self);
        func_ov002_0220a4c8((char *) self + 0x14c);
    }
}

int func_ov142_02299ae0(void *self)
{
    if (func_0208e930((char *) self + 0x14c)) {
        func_ov002_0220a580((char *) self + 0x14c);
        return 1;
    }
    return 0;
}

void func_ov142_02299ab8(UnkStruct_02299ab8 *self)
{
    func_0208ea70((char *) self + 0x14c, 0x38, self->unk_94 + (self->unk_A8 - 0x34));
}

void func_ov142_02299a80(OV142_02299A80_STRUCT *self)
{
    int result;
    int a = self->unk_A4;
    result = (self->unk_A8 * a) / 0x5a;
    if (result < 0) {
        result = 0;
    }
    if (result > a) {
        result = a;
    }
    func_ov142_0229a4d4(self, result);
    self->unk_A0 = result;
}

void func_ov142_02299a54(OV142_02299A54_STRUCT *self)
{
    if (self->unk_A4 > 0) {
        self->unk_A8 = (self->unk_9C * 90) / self->unk_A4;
        func_ov142_02299ab8((UnkStruct_02299ab8 *) self);
    }
}

void func_ov142_02299a24(int r0, int r1)
{
    int sp[2];
    sp[0] = 0x13;
    sp[1] = r1;
    func_0206fdd4((unsigned short *) (r0 + 0x2860), 0x17, 4, 0x18, sp[0], sp[1]);
    func_ov142_02299658(r0, 0x10);
}

void func_ov142_02299a08(void *param)
{
    func_ov142_02299648(param, 0x100);
    func_ov142_02299a24((int) param, 2);
}

void func_ov142_022999ec(void *param)
{
    func_ov142_02299658((int) param, 0x100);
    func_ov142_02299a24((int) param, 3);
}

void func_ov142_022999a4(UnkStruct_022999a4 *self)
{
    func_ov142_0229ab80(self, self->unk_BE);
    func_ov142_0229a4d4((OV142_02299A80_STRUCT *) self, (self->unk_B8 - 3) << 4);
    self->unk_A0 = self->unk_9C;
    func_ov142_02299a54((OV142_02299A54_STRUCT *) self);
    func_ov142_022999ec((void *) self);
    func_ov142_02299658((int) self, 0x200);
}

void func_ov142_02299938(UnkStruct_02299938 *self)
{
    int r5;
    int result;

    r5 = self->unk_B4;
    result = func_ov142_0229a6d8(self) - 8;
    if (result < 0) {
        result = 0;
    }
    if (r5 < 0) {
        r5 = 0;
    } else if (r5 > result) {
        r5 = result;
    }

    func_ov142_0229a4d4((OV142_02299A80_STRUCT *) self, r5 * 16);

    self->unk_A0 = self->unk_9C;
    func_ov142_02299a54((OV142_02299A54_STRUCT *) self);

    if (self->unk_A4 == 0) {
        func_ov142_022999ec((void *) self);
    } else {
        func_ov142_02299a08((void *) self);
    }

    func_ov142_02299648((void *) self, 0x200);
}

void func_ov142_02299928(int a)
{
    func_ov142_02299658(a, 0x1000);
}

void func_ov142_02299918(int a)
{
    func_ov142_02299658(a, 0x2000);
}

void func_ov142_02299908(int a)
{
    func_ov142_02299648((void *) a, 0x3000);
}

void func_ov142_02299830(struct UnkStruct_02299830 *self)
{
    int old = self->unk_9C;

    if (func_ov142_02299668(self, 0x1000) != 0) {
        int low = self->unk_9C & 0xf;
        if (low != 0) {
            self->unk_9C -= low;
        } else {
            self->unk_9C -= 0x10;
        }
        if (self->unk_9C < 0) {
            self->unk_9C = 0;
        }
    } else {
        int low = self->unk_9C & 0xf;
        if (low != 0) {
            self->unk_9C += 0x10 - low;
        } else {
            self->unk_9C += 0x10;
        }
        if (self->unk_9C > self->unk_A4) {
            self->unk_9C = self->unk_A4;
        }
    }

    if (old != self->unk_9C) {
        func_ov142_0229a4d4((OV142_02299A80_STRUCT *) self, self->unk_9C);
        self->unk_A0 = self->unk_9C;
        func_ov142_02299a54((OV142_02299A54_STRUCT *) self);
        func_ov002_0220a4c8((char *) self + 0x14c);
    }
}
