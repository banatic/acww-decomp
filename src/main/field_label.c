/* field_label: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b8a5c @ 0x020b8a5c, 0x94 bytes, Thumb
 * func_020b8a4c @ 0x020b8a4c, 0x10 bytes, Thumb
 * func_020b8a3c @ 0x020b8a3c, 0x10 bytes, Thumb
 * func_020b8a10 @ 0x020b8a10, 0x2a bytes, Thumb
 * func_020b89cc @ 0x020b89cc, 0x44 bytes, Thumb
 * func_020b88f0 @ 0x020b88f0, 0xdc bytes, Thumb
 * func_020b88d8 @ 0x020b88d8, 0x18 bytes, Thumb
 * func_020b88c0 @ 0x020b88c0, 0x18 bytes, Thumb
 * func_020b889c @ 0x020b889c, 0x24 bytes, Thumb
 * func_020b8878 @ 0x020b8878, 0x24 bytes, Thumb
 * func_020b8854 @ 0x020b8854, 0x24 bytes, Thumb
 * func_020b884c @ 0x020b884c, 0x6 bytes, Thumb
 * func_020b87ac @ 0x020b87ac, 0xa0 bytes, Thumb
 * func_020b87a4 @ 0x020b87a4, 0x6 bytes, Thumb
 * func_020b8744 @ 0x020b8744, 0x60 bytes, Thumb
 * func_020b873c @ 0x020b873c, 0x6 bytes, Thumb
 * func_020b86e4 @ 0x020b86e4, 0x58 bytes, Thumb
 * func_020b86d0 @ 0x020b86d0, 0x14 bytes, Thumb
 * func_020b866c @ 0x020b866c, 0x64 bytes, Thumb
 */

struct UnkStruct_020b8a5c {
    long long data[6];
};

typedef struct {
    unsigned char pad_00[8];
    unsigned char data[0xEC];
    unsigned int unk_F4;
} UnkStruct_020b8a10;

typedef struct {
    int pad_00;
    char data[0x58];
} UnkStruct_020b89cc;

struct SelfData {
    char pad_00[0x100];
    unsigned int unk_100;
};

typedef struct UnkStruct_020b88f0 {
    unsigned char pad_00[8];
    unsigned char sub[0xf4];
    int unk_FC;
    unsigned char pad_100[4];
    int unk_104;
    unsigned char pad_108[4];
    unsigned char unk_10C;
} UnkStruct_020b88f0;

typedef struct Locals {
    unsigned char byte_var;
    unsigned char pad_01[3];
    unsigned char buf[0x60];
} Locals;

typedef struct {
    char pad_00[0xFC];
    unsigned int index;
    char pad_100[8];
    int value;
    char flag;
} UnkStruct_020b889c;

typedef struct {
    unsigned char pad_00[0xfc];
    int unk_FC;
    unsigned char pad_100[8];
    int unk_108;
} UnkStruct_020b8854;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_020b884c;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_020b87a4;

typedef struct {
    unsigned char pad_00[0xf4];
    unsigned short *sub;
    unsigned short id;
} UnkStruct_020b8744;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_020b873c;

typedef struct {
    unsigned char pad_00[0x108];
    int unk_108;
    unsigned char pad_10C;
    unsigned char flag;
} UnkStruct_020b86e4;

struct UnkStruct_020b866c {
    char pad_00;
};

struct UnkStruct_020b866c_2 {
    char pad_00[8];
    struct UnkStruct_020b866c sub;
    char pad_09[0x108 - 0x08 - 1];
    int counter;
};

extern struct UnkStruct_020b8a5c *func_0203ab20(void);
extern int *func_02095794(int);
extern int func_0203f844(void *, void *);
extern void MTX_MultVec43(void *, void *, void *);
extern int func_0203c53c(void *);
extern int FX_Div(int, int);
extern void func_020eabc8(void *, int);
extern void func_0208aa60(void *, int, int);
extern struct UnkStruct_020b8a5c data_021fbe48;
extern void *data_021c67a4;
extern void *func_02062f90(void *buf, unsigned int val);
extern void func_0208aa48(void *a, void *b);
extern void *func_02062f4c(void *b);
extern unsigned char data_020d226c[];
void *func_020a8228(UnkStruct_020b89cc *s);
int func_020b4980(UnkStruct_020b89cc *s, unsigned char *b, int flag);
void *func_020a8210(UnkStruct_020b89cc *s);
extern unsigned char data_020d2270[];
extern void func_0208a9e4(void *, int);
extern void func_020b8fe0(void *);
extern unsigned char data_020d227c[];
extern void func_020b9068(void *, unsigned char);
extern short data_020d2298[];
extern int func_0208a9c8(void *self);
extern int func_0208a844(void *arg);
extern void *func_0208a9ac(void *arg);
extern void func_020b90a4(void *);
extern int func_020b9030(struct UnkStruct_020b866c *sub);
extern int func_020b904c(struct UnkStruct_020b866c *sub);

void func_020b87a4(UnkStruct_020b87a4 *p);
void func_020b873c(UnkStruct_020b873c *p);
void func_020b86d0(void *arg0);

void func_020b8a5c(void *p)
{
    struct UnkStruct_020b8a5c *src;
    int *ptr;
    int data[3];
    int buffer2[3];
    int buffer3[3];
    int tmp1, tmp2;

    src = func_0203ab20();
    data_021fbe48 = *src;

    ptr = func_02095794(4);
    if (ptr != 0) {
        data[0] = ptr[0];
        data[1] = ptr[1];
        data[2] = ptr[2];
        data[1] += 0x3c00;

        func_0203f844(buffer2, data);
        MTX_MultVec43(buffer2, &data_021fbe48, buffer3);

        tmp1 = FX_Div(0x60000, func_0203c53c(data_021c67a4));
        tmp2 = FX_Div(-tmp1, buffer3[2]);
        func_020eabc8(buffer3, tmp2);

        func_0208aa60((char *) p + 8, buffer3[0] >> 12, -buffer3[1] >> 12);
    }
}

void func_020b8a4c(void *arg)
{
    func_0208aa60((char *) arg + 8, 0, ~0x2f);
}

void func_020b8a3c(int p0)
{
    func_0208aa60((void *) (p0 + 8), 0x12, ~0x2f);
}

void func_020b8a10(UnkStruct_020b8a10 *param)
{
    unsigned char buffer[40];
    func_02062f90(buffer, param->unk_F4);
    func_0208aa48(param->data, buffer);
    func_02062f4c(buffer);
}

void func_020b89cc(struct SelfData *self)
{
    unsigned char ch;
    UnkStruct_020b89cc local;
    char *p;

    ch = data_020d226c[self->unk_100];
    func_020a8228(&local);
    func_020b4980(&local, &ch, 0);
    p = (char *) self + 8;
    func_0208aa48((void *) p, (void *) (&local));
    func_020a8210(&local);
}

void func_020b88f0(UnkStruct_020b88f0 *self, int flag)
{
    Locals local;
    int r2, r3, r4, cond;
    unsigned char old_byte;

    func_020a8228((UnkStruct_020b89cc *) local.buf);

    local.byte_var = data_020d2270[self->unk_FC];
    r2 = (self->unk_FC == 1) ? 1 : 0;
    r3 = (self->unk_FC == 2) ? 1 : 0;
    r4 = 1;
    if (r2 == 0 && r3 == 0) {
        r4 = 0;
    }

    old_byte = self->unk_10C;
    self->unk_10C = 0;

    if (flag != 0) {
        self->unk_104 = 0;
        cond = 1;
    } else {
        cond = old_byte;
        if (r4 != 0) {
            cond = 1;
        }
    }

    if (cond != 0) {
        if (self->unk_104 == 1) {
            if (r2 != 0) {
                local.byte_var = 0x93;
            } else if (r3 != 0) {
                local.byte_var = 0x94;
            }
        }
        func_020b4980((UnkStruct_020b89cc *) local.buf, &local.byte_var, 0);
        func_0208aa48(&self->sub, (void *) local.buf);
        if (flag == 0) {
            func_0208a9e4(&self->sub, 1);
            func_020b8fe0(&self->sub);
        }
    }

    if (r4 != 0) {
        self->unk_104++;
        if (self->unk_104 >= 2) {
            self->unk_104 = 0;
        }
    }

    func_020a8210((UnkStruct_020b89cc *) local.buf);
}

void func_020b88d8(void *self)
{
    func_020b9068((char *) self + 8, data_020d227c[*(unsigned int *) ((char *) self + 0xfc)]);
}

void func_020b88c0(void *r0)
{
    *(unsigned int *) ((char *) r0 + 0x108) = 0x3c;
    *(unsigned char *) ((char *) r0 + 0x10d) = 1;
}

void func_020b889c(UnkStruct_020b889c *ptr)
{
    ptr->value = data_020d2298[ptr->index];
    ptr->flag = 1;
}

int func_020b8878(void *ptr)
{
    int result;
    int val1;
    int val2;

    val1 = *(int *) ((char *) ptr + 0x100);
    if (val1 != 0) {
        result = 1;
    } else {
        result = 0;
    }

    val2 = *(int *) ((char *) ptr + 0x108);
    if (val2 == 0) {
        result = 0;
    }

    return result;
}

int func_020b8854(UnkStruct_020b8854 *arg0)
{
    int val;
    if (arg0->unk_FC != 0) {
        val = 1;
    } else {
        val = 0;
    }
    if (arg0->unk_108 == 0) {
        val = 0;
    }
    return val;
}

void func_020b884c(UnkStruct_020b884c *p)
{
    p->unk_04 = 0;
}

void func_020b87ac(void *self)
{
    if (func_020b8854((UnkStruct_020b8854 *) self)) {
        func_020b8a3c((int) self);
        func_020b88f0((UnkStruct_020b88f0 *) self, 1);
        func_020b88d8(self);
        if (func_0208a9c8((char *) self + 8)) {
            func_020b86d0(self);
        }
    } else {
        if (func_020b8878(self)) {
            func_020b8a4c(self);
            func_020b89cc((struct SelfData *) self);
            func_020b9068((char *) self + 8, 0);
            if (func_0208a9c8((char *) self + 8)) {
                func_020b873c((UnkStruct_020b873c *) self);
            }
        } else {
            if (*(int *) ((char *) self + 0xf4) != 0) {
                func_020b8a5c(self);
                func_020b8a10((UnkStruct_020b8a10 *) self);
                func_020b9068((char *) self + 8, 0);
                if (func_0208a9c8((char *) self + 8)) {
                    func_020b87a4((UnkStruct_020b87a4 *) self);
                }
            }
        }
    }
}

void func_020b87a4(UnkStruct_020b87a4 *p)
{
    p->unk_04 = 1;
}

void func_020b8744(void *p)
{
    UnkStruct_020b8744 *s = (UnkStruct_020b8744 *) p;

    if (func_0208a844((char *) p + 8) == 0) {
        func_020b884c((UnkStruct_020b884c *) p);
        return;
    }

    if (s->sub == 0) {
        goto skip;
    }
    if (s->id == 0xfff1) {
        goto call8854;
    }
    if (s->id != *s->sub) {
        goto skip;
    }

call8854:
    if (func_020b8854((UnkStruct_020b8854 *) p) != 0) {
        goto skip;
    }
    if (func_020b8878(p) == 0) {
        goto a5c;
    }

skip:
    func_0208a9ac((char *) p + 8);
    return;

a5c:
    func_020b8a5c(p);
}

void func_020b873c(UnkStruct_020b873c *p)
{
    p->unk_04 = 2;
}

void func_020b86e4(void *p)
{
    UnkStruct_020b86e4 *s = (UnkStruct_020b86e4 *) p;

    if (s->unk_108 > 0) {
        s->unk_108--;
    }

    if (func_0208a844((char *) p + 8) == 0) {
        func_020b884c((UnkStruct_020b884c *) p);
        return;
    }

    if (func_020b8854((UnkStruct_020b8854 *) p) != 0) {
        goto final;
    }

    if (func_020b8878(p) != 0) {
        if (s->flag == 0) {
            return;
        }
    }

final:
    p = (char *) p + 8;
    func_0208a9ac(p);
}

void func_020b86d0(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020b90a4((void *) ((unsigned int) arg0 + 8));
    *(unsigned int *) ((unsigned int) r4 + 4) = 3;
}

void func_020b866c(struct UnkStruct_020b866c_2 *self)
{
    if (self->counter > 0) {
        self->counter--;
    }
    if (func_0208a844((void *) (&self->sub)) == 0) {
        func_020b884c((UnkStruct_020b884c *) self);
    } else {
        if (func_020b8854((UnkStruct_020b8854 *) self) == 0) {
            if (func_020b9030(&self->sub) == 0) {
                func_0208a9ac((void *) (&self->sub));
            }
        } else {
            if (func_020b904c(&self->sub) != 0) {
                func_020b88f0((UnkStruct_020b88f0 *) self, 0);
            }
        }
    }
}
