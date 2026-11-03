/* order_catalog_cursor: 9 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229a0d4 @ 0x0229a0d4, 0x22 bytes, Thumb
 * func_ov142_0229a09c @ 0x0229a09c, 0x36 bytes, Thumb
 * func_ov142_0229a07c @ 0x0229a07c, 0x1e bytes, Thumb
 * func_ov142_0229a05c @ 0x0229a05c, 0x1e bytes, Thumb
 * func_ov142_02299fbc @ 0x02299fbc, 0x9e bytes, Thumb
 * func_ov142_02299fa4 @ 0x02299fa4, 0x18 bytes, Thumb
 * func_ov142_02299f8c @ 0x02299f8c, 0x18 bytes, Thumb
 * func_ov142_02299f5c @ 0x02299f5c, 0x30 bytes, Thumb
 * func_ov142_02299c64 @ 0x02299c64, 0x2f8 bytes, Thumb
 */

struct UnkStruct_0229a09c {
    char pad_00[0xc0];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc0 - 1];
    int value_e8;
};

struct UnkStruct_0229a07c {
    unsigned char pad_00[0xa4];
    void *unk_A4;
};

typedef struct UnkStruct_0229a05c {
    char pad_00[0xa4];
    void *unk_A4;
} UnkStruct_0229a05c;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xc0 - 0xa4];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc1];
    char unk_E8;
} UnkStruct_02299fbc;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xc0 - 0xa8];
    volatile unsigned char unk_C0;
} UnkStruct_02299c64;

extern int func_ov002_02209eec(void *);
extern int func_ov142_0229a6d8(void *p);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

void func_ov142_02299f8c(int r0);
void func_ov142_02299f5c(char *obj);

int func_ov142_0229a0d4(void *arg)
{
    char *p = (char *) arg;
    if (func_ov002_02209eec(p + 0xe8) > 0x89) {
        p[0xc0] = 0x13;
        return 0x13;
    } else {
        p[0xc0] = 0x12;
        return 0x12;
    }
}

int func_ov142_0229a09c(struct UnkStruct_0229a09c *self)
{
    if (func_ov002_02209eec((void *) (&self->value_e8)) < 0x2b) {
        self->unk_C0 = 0x15;
        return 0x15;
    } else if (func_ov002_02209eec((void *) (&self->value_e8)) > 0x93) {
        self->unk_C0 = 0x16;
        return 0x16;
    } else {
        self->unk_C0 = 0x14;
        return 0x14;
    }
}

int func_ov142_0229a07c(struct UnkStruct_0229a07c *self)
{
    if (self->unk_A4 == 0) {
        return func_ov142_0229a0d4((void *) self);
    } else {
        return func_ov142_0229a09c((struct UnkStruct_0229a09c *) self);
    }
}

void func_ov142_0229a05c(UnkStruct_0229a05c *p)
{
    if (p->unk_A4 == 0) {
        func_ov142_02299f8c((int) p);
    } else {
        func_ov142_0229a09c((struct UnkStruct_0229a09c *) p);
    }
}

int func_ov142_02299fbc(UnkStruct_02299fbc *self)
{
    int v;
    int a;
    int b;
    int e;

    v = func_ov142_0229a6d8(self);
    if (v == 0) {
        return 0;
    }
    if (v > 9) {
        v = 9;
    }
    a = func_ov002_02209eec(&self->unk_E8);
    if (a < 0x20) {
        a = 0x20;
    }
    if (a >= 0xa0) {
        a = 0x9f;
    }
    b = self->unk_A0 & 0xf;
    e = (a - (0x20 - b)) >> 4;
    if (e >= v) {
        e = v - 1;
    }
    self->unk_C0 = (unsigned char) (e + 9);

    if (b == 0) {
        goto done;
    }
    if (e == 0) {
        self->unk_A0 = self->unk_A0 - b;
        goto done;
    }
    if (e != v - 1) {
        goto done;
    }
    self->unk_C0 = (unsigned char) (self->unk_C0 - 1);
    self->unk_A0 = self->unk_A0 + (0x10 - (self->unk_A0 & 0xf));

done:
    return 1;
}

int func_ov142_02299fa4(int a)
{
    int res = func_ov142_02299fbc((UnkStruct_02299fbc *) a);
    if (res != 0) {
        return res;
    }
    return func_ov142_0229a07c((struct UnkStruct_0229a07c *) a);
}

void func_ov142_02299f8c(int r0)
{
    int r4 = r0;
    if (func_ov142_02299fbc((UnkStruct_02299fbc *) ((void *) r0)) == 0) {
        func_ov142_02299f5c((char *) r4);
    }
}

void func_ov142_02299f5c(char *obj)
{
    int result;
    int mask;
    result = func_ov002_02209eec(obj + 0xe8);
    mask = result & 0xf;
    if (mask == 0) {
        result--;
    }
    if (result < 0x18) {
        result = 0x18;
    }
    if (result >= 0xa8) {
        result = 0xa7;
    }
    result -= 0x18;
    result >>= 4;
    obj[0xc0] = result;
}

int func_ov142_02299c64(UnkStruct_02299c64 *self, void *pad)
{
    unsigned char old = self->unk_C0;

    if (pad == 0) {
        return 0;
    }

    if (old <= 8) {
        if (func_ov002_0220889c(pad)) {
            func_ov142_02299fa4((int) self);
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C0 != 0) {
                self->unk_C0 = self->unk_C0 - 1;
            }
        } else if (func_ov002_022088bc(pad)) {
            if (self->unk_C0 < 8) {
                self->unk_C0 = self->unk_C0 + 1;
            }
        }
    } else if (old >= 9 && old <= 0x11) {
        if (func_ov002_022088ac(pad)) {
            func_ov142_02299f5c((char *) self);
        } else if (func_ov002_0220889c(pad)) {
            func_ov142_0229a07c((struct UnkStruct_0229a07c *) self);
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C0 > 9) {
                self->unk_C0 = self->unk_C0 - 1;
                if (self->unk_C0 == 9) {
                    int t = self->unk_A0 & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 - t;
                    }
                }
            } else {
                if (self->unk_A0 >= 0x10) {
                    self->unk_A0 = self->unk_A0 - 0x10;
                    return 1;
                }
            }
        } else if (func_ov002_022088bc(pad)) {
            int n = self->unk_A4;
            if (n == 0) {
                if (self->unk_C0 < func_ov142_0229a6d8((void *) self) + 8) {
                    self->unk_C0 = self->unk_C0 + 1;
                }
            } else {
                if (self->unk_C0 < 0x10) {
                    self->unk_C0 = self->unk_C0 + 1;
                } else {
                    int a = self->unk_A0;
                    int t = a & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 + (0x10 - t);
                        return 1;
                    }
                    if (a <= n - 0x10) {
                        self->unk_A0 = self->unk_A0 + 0x10;
                        return 1;
                    }
                }
            }
        }
    } else {
        switch (old) {
            case 0x13:
                if (func_ov002_022088ac(pad)) {
                    func_ov142_0229a05c((UnkStruct_0229a05c *) self);
                } else if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x12;
                }
                break;
            case 0x12:
                if (func_ov002_022088ac(pad)) {
                    func_ov142_0229a05c((UnkStruct_0229a05c *) self);
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x13;
                }
                break;
            case 0x14:
                if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x15;
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x16;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c((int) self);
                }
                break;
            case 0x15:
                if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x14;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c((int) self);
                }
                break;
            case 0x16:
                if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x14;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c((int) self);
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x13;
                }
                break;
        }
    }

    if (old != self->unk_C0) {
        return 1;
    }
    return 0;
}
