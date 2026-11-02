/* soft_keyboard_cursor: 6 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_02299b7c @ 0x02299b7c, 0x38 bytes, Thumb
 * func_ov095_02299b38 @ 0x02299b38, 0x44 bytes, Thumb
 * func_ov095_02299b30 @ 0x02299b30, 0x6 bytes, Thumb
 * func_ov095_02299aec @ 0x02299aec, 0x44 bytes, Thumb
 * func_ov095_02299a54 @ 0x02299a54, 0x98 bytes, Thumb
 * func_ov095_02299a00 @ 0x02299a00, 0x52 bytes, Thumb
 */

struct UnkStruct_02299b7c {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad_30[4];
    int unk_34;
    char pad_38[11];
    unsigned char unk_43;
};

struct UnkStruct_02299aec {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    int unk_28;
};

typedef struct {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x28 - 0x17];
    void *unk_28;
    char pad_2C[0x43 - 0x2C];
    char unk_43;
} UnkStruct_02299a54;

typedef struct UnkStruct_02299a00 UnkStruct_02299a00;

struct UnkStruct_02299a00 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x24 - 0x17];
    int unk_24;
    int unk_28;
};

extern int func_ov095_0229c52c(void *self, int field);
extern int func_ov095_022999b0(void *self, int arg);
extern void func_ov095_0229ab68(void *unused0);
extern void func_ov095_0229aae0(void *unused0);
extern void func_ov095_0229aaac(void *unused0);
extern void func_ov095_022999a0(void *, int);
extern void func_ov095_0229a720(void *, void *);
extern void func_ov095_0229a4d4(void *, void *);
extern void func_ov095_0229a2d8(void *, void *);
extern void func_ov095_0229aa74(void *);
extern int func_ov095_0229cddc(void *, void *);
extern int func_ov095_0229cda4(void *, void *);
extern int func_ov095_0229ce08(UnkStruct_02299a00 *p, int val);

int func_ov095_02299b7c(struct UnkStruct_02299b7c *p)
{
    if (p->unk_28 == 0x103) {
        p->unk_2C = p->unk_34;
    }
    switch (p->unk_43) {
        case 1:
            return p->unk_2C - 0x100;
        case 2:
            return p->unk_2C + 0x100;
        default:
            return p->unk_2C;
    }
}

int func_ov095_02299b38(void *self)
{
    if (*(int *) ((char *) self + 0x28) == 0x103) {
        *(int *) ((char *) self + 0x30) = *(int *) ((char *) self + 0x38);
        return *(int *) ((char *) self + 0x30);
    }
    if (func_ov095_0229c52c(self, *(int *) ((char *) self + 0x28)) != -1) {
        return *(int *) ((char *) self + 0x30);
    }
    if (func_ov095_022999b0(self, 4) == 0) {
        return *(int *) ((char *) self + 0x30) - 8;
    }
    return *(int *) ((char *) self + 0x30);
}

void func_ov095_02299b30(int *p, int a, int b)
{
    p[0xd] = a;
    p[0xe] = b;
}

void func_ov095_02299aec(struct UnkStruct_02299aec *self)
{
    switch (self->unk_16) {
        case 0:
            break;
        case 1:
            self->unk_28 = 0x3b;
            func_ov095_0229ab68(self);
            break;
        case 2:
            self->unk_28 = 0x70;
            func_ov095_0229aae0(self);
            break;
        case 3:
            break;
        case 4:
            self->unk_28 = 0xc9;
            func_ov095_0229aaac(self);
            break;
    }
}

int func_ov095_02299a54(UnkStruct_02299a54 *s, void *p)
{
    void *saved = s->unk_28;

    s->unk_43 = 0;
    func_ov095_022999a0(s, 0x10);

    switch (s->unk_16) {
        case 0:
            break;
        case 1:
            func_ov095_0229a720(s, p);
            break;
        case 2:
            func_ov095_0229a4d4(s, p);
            break;
        case 3:
            break;
        case 4:
            func_ov095_0229a2d8(s, p);
            break;
    }

    if (func_ov095_022999b0(s, 0x10) != 0) {
        return 4;
    }

    if (saved != s->unk_28) {
        func_ov095_0229aa74(s);
        if (func_ov095_0229cddc(s, s->unk_28) != 0) {
            return 2;
        }
        if (func_ov095_0229cda4(s, s->unk_28) != 0) {
            return 3;
        }
        return 1;
    }
    return 0;
}

int func_ov095_02299a00(UnkStruct_02299a00 *p)
{
    if (func_ov095_0229ce08(p, p->unk_28) != 0) {
        return -1;
    }
    switch (p->unk_28) {
        case 0xf8:
            if (p->unk_16 == 4) {
                return -1;
            }
            break;
        case 0xf9:
            if (p->unk_16 == 1) {
                return -1;
            }
            break;
        case 0xfa:
            if (p->unk_16 == 2) {
                return -1;
            }
            break;
    }
    p->unk_24 = p->unk_28;
    return p->unk_28;
}
