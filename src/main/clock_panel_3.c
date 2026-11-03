/* clock_panel_3: 26 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208dd68 @ 0x0208dd68, 0x10 bytes, Thumb
 * func_0208dd60 @ 0x0208dd60, 0x8 bytes, Thumb
 * func_0208dd50 @ 0x0208dd50, 0x10 bytes, Thumb
 * func_0208dd40 @ 0x0208dd40, 0x10 bytes, Thumb
 * func_0208dd18 @ 0x0208dd18, 0x28 bytes, Thumb
 * func_0208dd10 @ 0x0208dd10, 0x8 bytes, Thumb
 * func_0208dd00 @ 0x0208dd00, 0xe bytes, Thumb
 * func_0208dcf8 @ 0x0208dcf8, 0x6 bytes, Thumb
 * func_0208dcd4 @ 0x0208dcd4, 0x24 bytes, Thumb
 * func_0208dc88 @ 0x0208dc88, 0x4c bytes, Thumb
 * func_0208dc64 @ 0x0208dc64, 0x22 bytes, Thumb
 * func_0208dc5c @ 0x0208dc5c, 0x6 bytes, Thumb
 * func_0208dc44 @ 0x0208dc44, 0x18 bytes, Thumb
 * func_0208dc00 @ 0x0208dc00, 0x44 bytes, Thumb
 * func_0208dbd8 @ 0x0208dbd8, 0x28 bytes, Thumb
 * func_0208db3c @ 0x0208db3c, 0x9c bytes, Thumb
 * func_0208db08 @ 0x0208db08, 0x32 bytes, Thumb
 * func_0208daa0 @ 0x0208daa0, 0x68 bytes, Thumb
 * func_0208da38 @ 0x0208da38, 0x68 bytes, Thumb
 * func_0208d9d0 @ 0x0208d9d0, 0x68 bytes, Thumb
 * func_0208d968 @ 0x0208d968, 0x68 bytes, Thumb
 * func_0208d900 @ 0x0208d900, 0x68 bytes, Thumb
 * func_0208d898 @ 0x0208d898, 0x68 bytes, Thumb
 * func_0208d824 @ 0x0208d824, 0x74 bytes, Thumb
 * func_0208d7b8 @ 0x0208d7b8, 0x6c bytes, Thumb
 * func_0208d784 @ 0x0208d784, 0x32 bytes, Thumb
 */

typedef struct {
    void *pad_00;
    void *pad_04;
    void *pad_08;
    void *(*func)(void *);
} VTable;

typedef struct {
    VTable *vtable;
} Object;

typedef struct Vtbl Vtbl;

typedef struct UnkStruct_0208dd40 UnkStruct_0208dd40;

struct Vtbl {
    int unk_00;
    int unk_04;
    void (*func)(UnkStruct_0208dd40 *obj);
};

struct UnkStruct_0208dd40 {
    Vtbl *vtbl;
};

typedef struct {
    unsigned char pad_00[0x4E];
    unsigned char unk_4E;
    unsigned char unk_4F;
} UnkStruct_0208dd18;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208dcf8;

typedef struct {
    char pad_00[0x24];
    volatile int unk_24;
} UnkStruct_0208dcd4;

typedef struct UnkStruct_0208dc88 {
    char data[0x14];
} UnkStruct_0208dc88;

typedef struct SomeElement {
    int a;
    int b;
} SomeElement;

typedef struct UnkStruct_0208dc88_2 {
    char pad_00[0x0c];
    UnkStruct_0208dc88 sub;
    int unk_20;
    char pad_24[0x2b];
    unsigned char unk_4F;
} UnkStruct_0208dc88_2;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208dc5c;

typedef struct {
    char data[8];
} Entry8;

typedef struct {
    unsigned char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    unsigned char pad_to_4f[0x2b];
    unsigned char unk_4F;
} UnkStruct_0208dc00;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x4e - 0x28];
    unsigned char unk_4E;
} UnkStruct_0208db3c;

typedef struct Result Result;

struct Result {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54[0x1];
    unsigned char unk_55;
};

typedef struct UnkStruct_0208daa0 {
    char pad_00[0x28];
    Result *unk_28;
    char pad1[0x1c];
    unsigned char unk_48;
    char pad2[0x6];
    unsigned char unk_4F;
} UnkStruct_0208daa0;

typedef struct UnkStruct_0208da38 UnkStruct_0208da38;

typedef struct UnkStruct_0208da38_2 UnkStruct_0208da38_2;

struct UnkStruct_0208da38 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad_30[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[22];
    int unk_50;
    char pad_54[1];
    unsigned char unk_55;
};

struct UnkStruct_0208da38_2 {
    char pad_00[0x2c];
    UnkStruct_0208da38 *unk_2C;
    char pad_30[25];
    unsigned char unk_49;
    char pad2[5];
    unsigned char unk_4F;
};

struct UnkStruct_0208d9d0 {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54[0x1];
    unsigned char unk_55;
};

struct UnkStruct_0208d9d0_2 {
    char pad_00[0x30];
    struct UnkStruct_0208d9d0 *unk_30;
    char pad1[0x16];
    unsigned char unk_4A;
    char pad2[0x4];
    unsigned char unk_4F;
};

struct InnerStruct {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    char pad1[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x50 - 0x3a];
    unsigned int unk_50;
    char pad_54[0x55 - 0x54];
    unsigned char unk_55;
};

struct OuterStruct {
    char pad_00[0x34];
    struct InnerStruct *unk_34;
    char pad1[0x13];
    unsigned char unk_4B;
    char pad2[3];
    unsigned char unk_4F;
};

struct UnkStruct_0208d900 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54;
    unsigned char unk_55;
};

struct UnkStruct_0208d900_2 {
    char pad_00[0x38];
    struct UnkStruct_0208d900 *unk_38;
    char pad1[0x10];
    unsigned char unk_4C;
    char pad2[0x2];
    unsigned char unk_4F;
};

struct OuterStruct_0208d898 {
    char pad_00[0x3c];
    struct InnerStruct *unk_3C;
    char pad1[0x4d - 0x40];
    unsigned char unk_4D;
    char pad2[0x4f - 0x4e];
    unsigned char unk_4F;
};

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x4f - 0x44];
    unsigned char unk_4F;
} SELF;

typedef struct {
    unsigned char pad_00[0x10];
    int *unk_10;
    unsigned char pad_14[0x28 - 0x14];
    int *unk_28;
    int unk_2C;
    unsigned char pad_30[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x50 - 0x3a];
    int unk_50;
    unsigned char pad_54[0x55 - 0x54];
    unsigned char unk_55;
} OBJ;

extern unsigned char data_020e54a8;
extern void func_0208d400(UnkStruct_0208dc88_2 *self);
extern void func_0208a1f0(UnkStruct_0208dc88 *sub, const SomeElement *elem);
extern void func_0208a1ec(UnkStruct_0208dc88 *sub, int val);
extern void *func_0208a144(UnkStruct_0208dc88 *sub);
extern SomeElement data_020d5b3c[];
extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern int func_0203ec98(void);
extern int func_020960f8(int, int);
extern int func_02070070(void);
extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern void *func_020a9034(int, int, int);
extern unsigned char data_021c82e8[];
extern void func_02051694(struct InnerStruct *p);
extern unsigned char data_021c81d4[];
extern void func_02051648(OBJ *obj);
extern void func_0205166c(OBJ *obj, int a);
extern int data_020d0a54;
extern void func_020a8fb8(void *);
extern void func_0208d72c(void *);
extern void func_0208d6dc(void *);
extern void func_0208d69c(void *);
extern void func_0208d650(void *);
extern void func_0208d5ec(void *);
extern void func_0208d594(void *);
extern void func_0208d560(void *);

void func_0208dcf8(UnkStruct_0208dcf8 *p);
void func_0208dc88(UnkStruct_0208dc88_2 *self);
void func_0208dc5c(UnkStruct_0208dc5c *p);
void func_0208dc00(UnkStruct_0208dc00 *obj);
int func_0208db3c(UnkStruct_0208db3c *param);
void func_0208db08(void *arg);
void func_0208daa0(UnkStruct_0208daa0 *self);
void func_0208da38(UnkStruct_0208da38_2 *this);
void func_0208d9d0(struct UnkStruct_0208d9d0_2 *p);
void func_0208d968(struct OuterStruct *arg);
void func_0208d900(struct UnkStruct_0208d900_2 *self);
void func_0208d898(struct OuterStruct_0208d898 *arg);
void func_0208d824(SELF *self);
void func_0208d7b8(void *arg);

void func_0208dd68(char *arg)
{
    char *p = arg;
    p += 0x4e;
    *p = 0;
    func_0208dcf8((UnkStruct_0208dcf8 *) arg);
}

void func_0208dd60(void *argument0)
{
    func_0208d7b8((void *) argument0);
}

void *func_0208dd50(Object *self)
{
    return self->vtable->func(self);
}

void func_0208dd40(UnkStruct_0208dd40 *obj)
{
    obj->vtbl->func(obj);
}

void func_0208dd18(UnkStruct_0208dd18 *p)
{
    int flag;
    int val;
    flag = 1;
    p->unk_4E = 1;
    if (data_020e54a8 != 1) {
        flag = 0;
    }
    if (flag) {
        val = 1;
    } else {
        val = 0;
    }
    p->unk_4F = val;
}

void func_0208dd10(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (78))) + (0)) = 0;
}

int func_0208dd00(void *ptr)
{
    if (*(int *) ((char *) ptr + 0x20) == 0) {
        return 1;
    }
    return 0;
}

void func_0208dcf8(UnkStruct_0208dcf8 *p)
{
    p->unk_20 = 0;
}

void func_0208dcd4(UnkStruct_0208dcd4 *param)
{
    if (func_0208db3c((UnkStruct_0208db3c *) param)) {
        param->unk_24--;
        if (param->unk_24 > 0) {
            return;
        }
        func_0208dc88((UnkStruct_0208dc88_2 *) param);
    }
}

void func_0208dc88(UnkStruct_0208dc88_2 *self)
{
    int idx;

    self->unk_20 = 1;
    func_0208d400(self);

    if (self->unk_4F != 0) {
        idx = 0x29;
    } else {
        idx = 4;
    }

    func_0208a1f0(&self->sub, &data_020d5b3c[idx]);
    func_0208a1ec(&self->sub, 1);
    func_0208a144(&self->sub);
    func_0208db08((void *) self);
}

void func_0208dc64(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208dc5c((UnkStruct_0208dc5c *) param);
    }
}

void func_0208dc5c(UnkStruct_0208dc5c *p)
{
    p->unk_20 = 2;
}

void func_0208dc44(int r0)
{
    int r4 = r0;
    if (func_0208db3c((UnkStruct_0208db3c *) ((void *) r0)) == 0) {
        func_0208dc00((UnkStruct_0208dc00 *) r4);
    }
}

void func_0208dc00(UnkStruct_0208dc00 *obj)
{
    int idx;

    obj->unk_20 = 3;
    if (obj->unk_4F) {
        idx = 42;
    } else {
        idx = 5;
    }
    func_0208a1f0((UnkStruct_0208dc88 *) obj->sub, (const SomeElement *) (&((Entry8 *) data_020d5b3c)[idx]));
    func_0208a1ec((UnkStruct_0208dc88 *) obj->sub, 1);
    func_0208a144((UnkStruct_0208dc88 *) obj->sub);
}

void func_0208dbd8(void *arg0)
{
    void *ptr = arg0;
    func_0208a0c8((char *) ptr + 0xc);
    if (func_0208a160((char *) ptr + 0xc) != 0) {
        func_0208d7b8(ptr);
        func_0208dcf8((UnkStruct_0208dcf8 *) ptr);
    }
}

int func_0208db3c(UnkStruct_0208db3c *param)
{
    int ret;
    int flag1, flag2, flag3, a1, c1, a2, b1, b2;
    ret = param->unk_4E;
    if (ret != 0) {
        a1 = func_0203ec98();
        c1 = func_020960f8(2, 4);
        a2 = func_02070070();
        flag1 = 0;
        if (a1 != 0 && a2 == 0) {
            flag1 = 1;
        }
        flag2 = 0;
        if (a2 == 0 && c1 == 0) {
            flag2 = 1;
        }
        flag3 = 0;
        if (a1 != 0 && a2 != 0) {
            b1 = func_0206fd04();
            b2 = func_0206fd10();
            if (b1 != 0) {
                if (b2 < 0x1000) {
                    flag3 = 1;
                }
            } else {
                flag3 = 1;
            }
        }
        if (flag1 || flag2 || flag3) {
            ret = 0;
            if (flag1 || flag2) {
                param->unk_24 = 0x1e;
            } else {
                param->unk_24 = 1;
            }
        }
    } else {
        param->unk_24 = 0xa;
    }
    return ret;
}

void func_0208db08(void *arg)
{
    func_0208daa0((UnkStruct_0208daa0 *) arg);
    func_0208da38((UnkStruct_0208da38_2 *) arg);
    func_0208d9d0((struct UnkStruct_0208d9d0_2 *) arg);
    func_0208d968((struct OuterStruct *) arg);
    func_0208d900((struct UnkStruct_0208d900_2 *) arg);
    func_0208d898((struct OuterStruct_0208d898 *) arg);
    func_0208d824((SELF *) arg);
}

void func_0208daa0(UnkStruct_0208daa0 *self)
{
    int value;

    if (self->unk_28 != 0) {
        return;
    }

    if (self->unk_4F != 0) {
        value = 0x94;
    } else {
        value = 0x80;
    }

    self->unk_28 = func_020a9034(value, 3, 2);
    if (self->unk_28 != 0) {
        self->unk_28->unk_2C = 4;
        self->unk_28->unk_50 = 2;
        self->unk_28->unk_55 = 1;
        self->unk_28->unk_39 = 0;
        self->unk_28->unk_38 = 0xC;
        self->unk_28->unk_28 = (void *) data_021c82e8;
        func_02051694((struct InnerStruct *) self->unk_28);
        self->unk_48 = 1;
    }
}

void func_0208da38(UnkStruct_0208da38_2 *this)
{
    if (this->unk_2C) {
        return;
    }
    this->unk_2C = (UnkStruct_0208da38 *) func_020a9034((this->unk_4F != 0) ? 0x97 : 0x83, 3, 2);
    if (this->unk_2C == 0) {
        return;
    }
    this->unk_2C->unk_2C = 4;
    this->unk_2C->unk_50 = 2;
    this->unk_2C->unk_55 = 1;
    this->unk_2C->unk_39 = 0;
    this->unk_2C->unk_38 = 0xc;
    this->unk_2C->unk_28 = (int) ((int *) data_021c82e8);
    func_02051694((struct InnerStruct *) this->unk_2C);
    this->unk_49 = 1;
}

void func_0208d9d0(struct UnkStruct_0208d9d0_2 *p)
{
    int val;

    if (p->unk_30) {
        return;
    }

    if (p->unk_4F != 0) {
        val = 0x9a;
    } else {
        val = 0x86;
    }

    p->unk_30 = (struct UnkStruct_0208d9d0 *) func_020a9034(val, 2, 2);
    if (!p->unk_30) {
        return;
    }

    p->unk_30->unk_2C = 4;
    p->unk_30->unk_50 = 2;
    p->unk_30->unk_55 = 1;
    p->unk_30->unk_39 = 0;
    p->unk_30->unk_38 = 0xa;
    p->unk_30->unk_28 = (void *) data_021c82e8;

    func_02051694((struct InnerStruct *) p->unk_30);

    p->unk_4A = 1;
}

void func_0208d968(struct OuterStruct *arg)
{
    if (arg->unk_34 != 0) {
        return;
    }
    arg->unk_34 = (struct InnerStruct *) func_020a9034((arg->unk_4F != 0) ? 0xd4 : 0x88, 2, 1);
    if (arg->unk_34 != 0) {
        arg->unk_34->unk_2C = 4;
        arg->unk_34->unk_50 = 2;
        arg->unk_34->unk_55 = 1;
        arg->unk_34->unk_39 = 0;
        arg->unk_34->unk_38 = 9;
        arg->unk_34->unk_28 = (unsigned int) data_021c81d4;
        func_02051694(arg->unk_34);
        arg->unk_4B = 1;
    }
}

void func_0208d900(struct UnkStruct_0208d900_2 *self)
{
    if (self->unk_38 != 0) {
        return;
    }
    self->unk_38 = (struct UnkStruct_0208d900 *) func_020a9034((self->unk_4F != 0) ? 0xf4 : 0xa8, 2, 1);
    if (self->unk_38 == 0) {
        return;
    }
    self->unk_38->unk_2C = 4;
    self->unk_38->unk_50 = 2;
    self->unk_38->unk_55 = 1;
    self->unk_38->unk_39 = 0;
    self->unk_38->unk_38 = 9;
    self->unk_38->unk_28 = (unsigned int) data_021c81d4;
    func_02051694((struct InnerStruct *) self->unk_38);
    self->unk_4C = 1;
}

void func_0208d898(struct OuterStruct_0208d898 *arg)
{
    if (arg->unk_3C != 0) {
        return;
    }
    arg->unk_3C = (struct InnerStruct *) func_020a9034((arg->unk_4F != 0) ? 0xf6 : 0xaa, 2, 1);
    if (arg->unk_3C != 0) {
        arg->unk_3C->unk_2C = 4;
        arg->unk_3C->unk_50 = 2;
        arg->unk_3C->unk_55 = 1;
        arg->unk_3C->unk_39 = 0;
        arg->unk_3C->unk_38 = 9;
        arg->unk_3C->unk_28 = (unsigned int) data_021c81d4;
        func_02051694(arg->unk_3C);
        arg->unk_4D = 1;
    }
}

void func_0208d824(SELF *self)
{
    if (self->unk_40 != 0) {
        return;
    }
    self->unk_40 = func_020a9034(self->unk_4F ? 0xd8 : 0x8c, 1, 2);
    if (self->unk_40 == 0) {
        return;
    }
    ((OBJ *) self->unk_40)->unk_2C = 4;
    ((OBJ *) self->unk_40)->unk_10 = &data_020d0a54;
    ((OBJ *) self->unk_40)->unk_50 = 2;
    ((OBJ *) self->unk_40)->unk_55 = 1;
    ((OBJ *) self->unk_40)->unk_28 = ((int *) data_021c82e8);
    func_02051648((OBJ *) self->unk_40);
    ((OBJ *) self->unk_40)->unk_39 = 0;
    ((OBJ *) self->unk_40)->unk_38 = 9;
    func_0205166c((OBJ *) self->unk_40, 0);
}

void func_0208d7b8(void *arg)
{
    if (*(unsigned int *) ((char *) arg + 0x28) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x28));
        *(unsigned int *) ((char *) arg + 0x28) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x2c) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x2c));
        *(unsigned int *) ((char *) arg + 0x2c) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x30) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x30));
        *(unsigned int *) ((char *) arg + 0x30) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x34) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x34));
        *(unsigned int *) ((char *) arg + 0x34) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x38) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x38));
        *(unsigned int *) ((char *) arg + 0x38) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x3c) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x3c));
        *(unsigned int *) ((char *) arg + 0x3c) = 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x40) != 0) {
        func_020a8fb8(*(void **) ((char *) arg + 0x40));
        *(unsigned int *) ((char *) arg + 0x40) = 0;
    }
}

void func_0208d784(void *obj)
{
    func_0208d72c(obj);
    func_0208d6dc(obj);
    func_0208d69c(obj);
    func_0208d650(obj);
    func_0208d5ec(obj);
    func_0208d594(obj);
    func_0208d560(obj);
}
