/* talk_page_7: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206d5e4 @ 0x0206d5e4, 0x4c bytes, Thumb
 * func_0206d5c0 @ 0x0206d5c0, 0x24 bytes, Thumb
 * func_0206d594 @ 0x0206d594, 0x2c bytes, Thumb
 * func_0206d56c @ 0x0206d56c, 0x26 bytes, Thumb
 * func_0206d54c @ 0x0206d54c, 0x1e bytes, Thumb
 * func_0206d538 @ 0x0206d538, 0x14 bytes, Thumb
 * func_0206d500 @ 0x0206d500, 0x38 bytes, Thumb
 * func_0206d4e8 @ 0x0206d4e8, 0x16 bytes, Thumb
 * func_0206d4e0 @ 0x0206d4e0, 0x6 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[0x28];
    int unk_2C;
    void *unk_30;
    char sub_34[0x14];
    int unk_48;
    int unk_4C;
    int unk_50;
} UnkStruct_0206d5e4;

struct UnkStruct_0206d5c0 {
    void *unk_00;
    char pad_04[0x2C];
    void *unk_30;
};

typedef struct {
    void *unk_00;
    char pad_04[44];
    void *unk_30;
} UnkStruct_0206d594;

struct UnkStruct_0206d56c;

struct UnkStruct_0206d56c_2;

struct UnkStruct_0206d56c {
    unsigned char pad_00[0x30];
    struct UnkStruct_0206d56c_2 *b;
};

struct UnkStruct_0206d56c_2 {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad_14[0x1C];
    int unk_30;
};

struct UnkStruct_0206d500 {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned char pad_08[0x28];
    unsigned int unk_30;
    unsigned char pad_34[0x14];
    unsigned int unk_48;
    unsigned int unk_4C;
};

typedef struct {
    unsigned char pad_00[80];
    unsigned long unk_50;
} UnkStruct_0206d4e0;

void *func_020a92b0(void *self, int flag);
void func_020a8754(void *sub);
void *func_020a9034(int a, int b, int c);
void func_020a8eec(void *ptr, void *self);
extern char data_020def7c;
extern void func_020a8fb8(void *ptr);
extern void *func_020a9260(struct UnkStruct_0206d5c0 *self);
extern void func_020edb3c(UnkStruct_0206d594 *);
extern void func_02051648(void *p);
extern void func_020a8ecc(void *);
extern void func_020a8eac(void *);
extern void func_020a8e8c(unsigned int, int);
extern void func_020a9318(struct UnkStruct_0206d500 *);
extern void func_020a8764(void *, int);
extern void func_0206d330(void *);

void *func_0206d5e4(UnkStruct_0206d5e4 *self, int value)
{
    func_020a92b0(self, 1);
    self->unk_00 = ((int *) &data_020def7c);
    self->unk_2C = value;
    self->unk_30 = 0;
    func_020a8754(self->sub_34);
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;
    self->unk_30 = func_020a9034(0, 20, 2);
    if (self->unk_30 != 0) {
        func_020a8eec(self->unk_30, self);
    }
    return self;
}

struct UnkStruct_0206d5c0 *func_0206d5c0(struct UnkStruct_0206d5c0 *self)
{
    self->unk_00 = &data_020def7c;
    if (self->unk_30 != 0) {
        func_020a8fb8(self->unk_30);
    }
    func_020a9260(self);
    return self;
}

UnkStruct_0206d594 *func_0206d594(UnkStruct_0206d594 *self)
{
    self->unk_00 = &data_020def7c;
    if (self->unk_30) {
        func_020a8fb8(self->unk_30);
    }
    func_020a9260((struct UnkStruct_0206d5c0 *) self);
    func_020edb3c(self);
    return self;
}

int func_0206d56c(struct UnkStruct_0206d56c *a, int value, int flag)
{
    int result = 0;
    if (flag && a->b != 0) {
        a->b->unk_10 = value;
        func_02051648(a->b);
        result = a->b->unk_30;
        a->b->unk_10 = 0;
    }
    return result;
}

void func_0206d54c(void *param)
{
    if (*(int *) ((char *) param + 0x30) != 0) {
        *(int *) ((char *) param + 0x50) = 0;
        *(int *) ((char *) param + 0x48) = 0;
        *(int *) ((char *) param + 0x4c) = 0;
        func_020a8ecc(*(void **) ((char *) param + 0x30));
    }
}

void func_0206d538(void *arg)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg + 0x30))) != 0) {
        func_020a8eac(condition_value0);
    }
}

void func_0206d500(struct UnkStruct_0206d500 *param, int argument1)
{
    if (param->unk_30) {
        func_020a8e8c(param->unk_30, (int) argument1);
    }
    if (param->unk_04 == param->unk_48) {
        param->unk_48 = 0;
        func_020a9318(param);
    }
    if (param->unk_04 == param->unk_4C) {
        param->unk_4C = 0;
        func_020a9318(param);
    }
}

void func_0206d4e8(void *arg0, int argument1)
{
    void *r4;
    r4 = arg0;
    func_020a8764((void *) ((char *) r4 + 0x34), (int) argument1);
    func_0206d330(r4);
}

void func_0206d4e0(UnkStruct_0206d4e0 *p)
{
    p->unk_50 = 0;
}
