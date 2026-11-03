/* text_label_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070c2c @ 0x02070c2c, 0x24 bytes, Thumb
 * func_02070c08 @ 0x02070c08, 0x24 bytes, Thumb
 * func_02070be8 @ 0x02070be8, 0x20 bytes, Thumb
 * func_02070bc4 @ 0x02070bc4, 0x24 bytes, Thumb
 * func_02070ba4 @ 0x02070ba4, 0x20 bytes, Thumb
 * func_02070ba0 @ 0x02070ba0, 0x4 bytes, Thumb
 * func_02070b9c @ 0x02070b9c, 0x4 bytes, Thumb
 * func_02070b84 @ 0x02070b84, 0x18 bytes, Thumb
 * func_02070b24 @ 0x02070b24, 0x60 bytes, Thumb
 */

typedef struct UnkStruct_02070c2c UnkStruct_02070c2c;

struct UnkStruct_02070c2c {
    void *unk_00;
    char pad_04[0x64];
    int unk_68;
};

typedef struct UnkStruct_02070c08 {
    void *unk_00;
    char pad_04[0x64];
    int unk_68;
} UnkStruct_02070c08;

typedef struct {
    void *unk_00;
} UnkStruct_02070ba4;

struct UnkStruct_02070b24 {
    char pad_00[0x2c];
    int unk_2C;
    char pad_30[0x38 - 0x30];
    char unk_38;
    char unk_39;
    char pad_3A[0x50 - 0x3a];
    int unk_50;
    char pad_54[0x55 - 0x54];
    char unk_55;
};

struct UnkStruct_02070b24_2 {
    char pad_00[0x68];
    struct UnkStruct_02070b24 *unk_68;
};

extern void *func_020a8cac(UnkStruct_02070c2c *obj);
extern void func_020a8c1c(UnkStruct_02070c2c *obj);
extern int data_020e179c;
extern void *func_020a8c38(int **param);
extern void func_020edb3c(int **ptr);
extern void func_020a8fb8(void *);
extern int func_02002dc8(int arg);
extern int func_02002e04(int arg);

void func_02070b84(void *arg);

UnkStruct_02070c2c *func_02070c2c(UnkStruct_02070c2c *obj)
{
    func_020a8cac(obj);
    obj->unk_00 = ((char *) &data_020e179c);
    func_020a8c1c(obj);
    obj->unk_68 = 0;
    return obj;
}

UnkStruct_02070c08 *func_02070c08(UnkStruct_02070c08 *self)
{
    func_020a8cac((UnkStruct_02070c2c *) self);
    self->unk_00 = ((char *) &data_020e179c);
    func_020a8c1c((UnkStruct_02070c2c *) self);
    self->unk_68 = 0;
    return self;
}

int **func_02070be8(int **param)
{
    *param = &data_020e179c;
    func_02070b84((void *) param);
    func_020a8c38(param);
    return param;
}

int **func_02070bc4(int **ptr)
{
    *ptr = &data_020e179c;
    func_02070b84((void *) ptr);
    func_020a8c38(ptr);
    func_020edb3c(ptr);
    return ptr;
}

UnkStruct_02070ba4 *func_02070ba4(UnkStruct_02070ba4 *self)
{
    self->unk_00 = &data_020e179c;
    func_02070b84(self);
    func_020a8c38((int **) self);
    return self;
}

int func_02070ba0(void)
{
    return 84;
}

int func_02070b9c(int p0)
{
    return ((int) (p0) + (18));
}

void func_02070b84(void *arg)
{
    void *condition_value0;
    unsigned int *p = (unsigned int *) arg;
    if ((condition_value0 = (void *) (p[0x1A])) != 0) {
        func_020a8fb8(condition_value0);
        p[0x1A] = 0;
    }
}

void func_02070b24(struct UnkStruct_02070b24_2 *a, int b, char c, char d)
{
    int r = func_02002dc8(b);
    if (a->unk_68) {
        a->unk_68->unk_2C = r;
        if (func_02002e04(b)) {
            a->unk_68->unk_50 = 2;
        } else {
            a->unk_68->unk_50 = 1;
        }
        if (r == 4) {
            a->unk_68->unk_55 = 1;
        } else {
            a->unk_68->unk_55 = 0;
        }
        a->unk_68->unk_39 = d;
        a->unk_68->unk_38 = c;
    }
}
