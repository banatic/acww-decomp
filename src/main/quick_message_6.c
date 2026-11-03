/* quick_message_6: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02039f30 @ 0x02039f30, 0x68 bytes, Thumb
 * func_02039f0c @ 0x02039f0c, 0x22 bytes, Thumb
 * func_02039efc @ 0x02039efc, 0x10 bytes, Thumb
 * func_02039edc @ 0x02039edc, 0x1e bytes, Thumb
 * func_02039ebc @ 0x02039ebc, 0x1e bytes, Thumb
 * func_02039e84 @ 0x02039e84, 0x36 bytes, Thumb
 * func_02039e44 @ 0x02039e44, 0x3e bytes, Thumb
 * func_02039e34 @ 0x02039e34, 0xe bytes, Thumb
 * func_02039e08 @ 0x02039e08, 0x2a bytes, Thumb
 * func_02039d98 @ 0x02039d98, 0x70 bytes, Thumb
 * func_02039cf8 @ 0x02039cf8, 0xa0 bytes, Thumb
 * func_02039cb4 @ 0x02039cb4, 0x44 bytes, Thumb
 * func_02039c4c @ 0x02039c4c, 0x68 bytes, Thumb
 * func_02039c0c @ 0x02039c0c, 0x40 bytes, Thumb
 * func_02039b90 @ 0x02039b90, 0x7c bytes, Thumb
 * func_02039b30 @ 0x02039b30, 0x60 bytes, Thumb
 */

typedef struct {
    char pad_00[0xc];
    int flag;
    char pad_10[0x40];
    int result;
} UnkStruct_02039f30;

struct UnkStruct_02039e84 {
    char pad_00[0x50];
    int unk_50;
};

struct Main {
    char pad_00[0x9c];
    struct UnkStruct_02039e84 *unk_9C;
    struct UnkStruct_02039e84 *unk_A0;
};

typedef struct {
    unsigned char pad_00[0xb0];
    unsigned int unk_B0;
} UnkStruct_02039e08;

struct UnkStruct_02039cf8 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x3c];
    int unk_4C;
    char pad_50[0x58];
    int unk_A8;
};

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x34];
    int unk_44;
    char pad_48[0x60];
    int unk_A8;
    char pad_AC[0x4];
    int unk_B0;
} UnkStruct_02039c4c;

struct UnkStruct_02039c0c {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x94];
    int unk_A4;
    int unk_A8;
    char pad_AC[8];
    char unk_B4;
};

struct UnkStruct_02039b90 {
    char pad_00[0xc];
    int c;
    char pad_10[0x3c];
    int unk_4C;
    char pad_50[0x58];
    int a8;
    int ac;
};

typedef struct UnkStruct_02039b30_2 {
    int a;
    int b;
} UnkStruct_02039b30_2;

typedef struct UnkStruct_02039b30 {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x04];
    int unk_14;
    int unk_18;
    char unk_1C[0x14];
    char unk_30[0x04];
} UnkStruct_02039b30;

extern int func_0206fd10(void);
extern int func_0206fd34(void);
extern int FX_MulFunc(int, int);
extern void func_02051a78(void *, void *);
extern void *func_020a8bb8(void *, void *);
extern void func_02051694(struct UnkStruct_02039e84 *item);
extern void func_020a8c1c(void *);
extern void func_02051ad8(void *);
extern void func_020399c8(void *);
extern void func_0203990c(void *);
extern void func_020399e4(UnkStruct_02039e08 *);
extern void func_02039928(UnkStruct_02039e08 *);
extern void func_02039a94(UnkStruct_02039e08 *);
extern int func_0209d368(int id, int index);
extern void func_0200467c(int);
extern int func_020e895c(void *, int, int);
extern UnkStruct_02039b30_2 data_020d5b3c[];
extern void func_0208a1f0(void *base, void *ptr);
extern void func_0208a1ec(void *base, int value);
extern void *func_0208a1e8(void *base, int value);

void func_02039e34(void *arg);
void func_02039d98(void *self);
void func_02039cb4(int *self);
void func_02039c0c(struct UnkStruct_02039c0c *p);
void func_02039b30(UnkStruct_02039b30 *p);

void func_02039f30(UnkStruct_02039f30 *s)
{
    int flag = s->flag;
    if (flag == 0) {
        int t = func_0206fd10();
        int a = FX_MulFunc(0x4c000, t);
        int b = FX_MulFunc(0xc0000, 0x1000 - t);
        s->result = (a + b) >> 12;
    } else {
        int t = func_0206fd34();
        int a = FX_MulFunc(-0x5c000, t);
        int b = FX_MulFunc(0x30000, 0x1000 - t);
        s->result = (a + b) >> 12;
    }
}

void func_02039f0c(void *param0, void *param1, void *param2, void *param3)
{
    void *r5 = param0;
    void *r6 = param2;
    void *r4 = param3;

    func_02051a78((char *) r5 + 0x88, param1);
    func_020a8bb8((char *) r5 + 0x54, r6);
    *(unsigned int *) ((char *) r5 + 0x10) = (unsigned int) ((char *) r4 + 5);
}

void func_02039efc(int r0, int r1, int r2, int r3)
{
    *(int *) (r0 + 0xc) = r1;
    *(int *) (r0 + 0x14) = r2;
    *(int *) (r0 + 0x18) = r3;
    func_02039b30((UnkStruct_02039b30 *) ((void *) r0));
}

int func_02039edc(int arg0)
{
    int val;
    int val2;

    val = *(int *) (arg0 + 0xa4);
    if (val == 0) {
        val2 = 1;
    } else {
        val2 = 0;
    }
    if (val2 != 0) {
        *(int *) (arg0 + 0xb0) = 2;
    }
    return val2;
}

int func_02039ebc(int arg0)
{
    int *ptr;
    int result;
    int *field;

    ptr = (int *) (arg0 + 0xa4);
    if (*ptr != 0) {
        result = 1;
    } else {
        result = 0;
    }
    if (result != 0) {
        field = (int *) (arg0 + 0xb0);
        *field = 0;
    }
    return result;
}

void func_02039e84(struct Main *obj)
{
    if (obj->unk_9C) {
        obj->unk_9C->unk_50 = 3;
        func_02051694(obj->unk_9C);
    }
    if (obj->unk_A0) {
        obj->unk_A0->unk_50 = 3;
        func_02051694(obj->unk_A0);
    }
}

void func_02039e44(void *p)
{
    func_020a8c1c((char *) p + 0x54);
    func_02051ad8((char *) p + 0x88);
    func_020399c8(p);
    func_0203990c(p);
    ((int *) ((char *) p + 0xa8))[0] = 0;
    ((int *) ((char *) p + 0xac))[0] = 0;
    ((int *) ((char *) p + 0xb0))[0] = 0;
    func_02039e34(p);
}

void func_02039e34(void *arg)
{
    *((unsigned int *) ((unsigned char *) arg + 0xa4)) = 0;
    *((unsigned char *) arg + 0xb4) = 0;
}

void func_02039e08(UnkStruct_02039e08 *param)
{
    if (param->unk_B0) {
        func_020399e4(param);
        func_02039928(param);
        func_02039a94(param);
        func_02039d98((void *) param);
    }
}

void func_02039d98(void *self)
{
    int r4;
    int r1;
    int r0;
    int *p;
    unsigned char *pb;

    r4 = 0;
    r1 = 0;
    p = (int *) ((char *) self + 0xa4);
    *p = 1;
    pb = (unsigned char *) ((char *) self + 0xb4);
    *pb = 1;
    if (*(int *) ((char *) self + 0xc) == 0) {
        r0 = func_0209d368(0x136, 2);
        r4 = r0 + 3;
    } else {
        r0 = func_0209d368(0x12c, 2);
        r4 = r0 + 3;
    }
    if (*(int *) ((char *) self + 0xc) == 0) {
        r0 = func_0209d368(0x136, 3);
        r1 = r0 + 5;
    } else {
        r0 = func_0209d368(0x12c, 3);
        r1 = r0 - 5;
    }
    p = (int *) ((char *) self + 0xa8);
    *p = r4;
    *(int *) ((char *) self + 0x4c) = r1;
    if (*(int *) ((char *) self + 0xc) != 0) {
        func_0200467c(0x3f);
    }
}

void func_02039cf8(struct UnkStruct_02039cf8 *self)
{
    int r4;
    int r6;
    int t;

    if (self->unk_0C == 0) {
        r4 = func_0209d368(0x136, 4) + 2;
    } else {
        r4 = func_0209d368(0x12c, 4) + 2;
    }

    if (self->unk_0C == 0) {
        r6 = func_0209d368(0x136, 5) - 6;
    } else {
        r6 = func_0209d368(0x12c, 5) + 6;
    }

    if (self->unk_0C == 0) {
        t = func_0209d368(0x136, 6) + 2;
    } else {
        t = func_0209d368(0x12c, 6) - 2;
    }

    if (self->unk_A8 > r4) {
        self->unk_4C += r6;
    } else {
        self->unk_4C += t;
    }

    self->unk_A8 -= 1;

    if (self->unk_A8 <= 0) {
        self->unk_4C = 0;
        func_02039cb4((int *) self);
    }
}

void func_02039cb4(int *self)
{
    int *p;
    int v;

    self[0x29] = 2;
    *((unsigned char *) self + 0xb4) = 1;

    if (self[3] == 0) {
        v = func_0209d368(0x137, 2) + 0x258;
    } else {
        v = func_0209d368(0x12d, 2) + 0x258;
    }

    self[0x2a] = v;
}

void func_02039c4c(UnkStruct_02039c4c *self)
{
    int r2;

    if (self->unk_0C == 0) {
        r2 = func_0209d368(0x137, 3) + 6;
    } else {
        r2 = func_0209d368(0x12d, 3) + 6;
    }
    func_020e895c((char *) self + 0x48, self->unk_44, r2);
    self->unk_A8--;
    if (self->unk_A8 <= 0) {
        self->unk_B0 = 0;
    }
    if (self->unk_B0 == 0) {
        func_02039c0c((struct UnkStruct_02039c0c *) self);
    }
}

void func_02039c0c(struct UnkStruct_02039c0c *p)
{
    int res;

    p->unk_A4 = 3;
    p->unk_B4 = 1;
    if (p->unk_0C == 0) {
        res = func_0209d368(0x138, 2) + 2;
    } else {
        res = func_0209d368(0x12e, 2) + 2;
    }
    p->unk_A8 = res;
}

void func_02039b90(struct UnkStruct_02039b90 *p)
{
    int r;

    if (p->c == 0) {
        r = func_0209d368(0x138, 3) + 0xb;
    } else {
        r = func_0209d368(0x12e, 3) - 0xb;
    }
    p->unk_4C += r;

    p->a8--;
    if (p->a8 > 0) {
        goto out;
    }

    func_020399c8(p);
    func_0203990c(p);
    func_02039e34(p);

    if (p->c == 0) {
        r = func_0209d368(0x138, 4);
    } else {
        r = func_0209d368(0x12e, 4) + 0xa;
    }
    p->ac = r;

out:
    return;
}

void func_02039b30(UnkStruct_02039b30 *p)
{
    UnkStruct_02039b30_2 *base = data_020d5b3c;
    UnkStruct_02039b30_2 *ptr18 = base + p->unk_18;

    if (p->unk_0C != 0) {
        func_0208a1f0(&p->unk_1C, base + p->unk_14);
        func_0208a1ec(&p->unk_1C, 1);
        func_0208a1e8(&p->unk_1C, 0);
    }

    func_0208a1f0(&p->unk_30, ptr18);
    func_0208a1ec(&p->unk_30, 1);
    func_0208a1e8(&p->unk_30, 0);
}
