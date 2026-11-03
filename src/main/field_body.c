/* field_body: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02089cc0 @ 0x02089cc0, 0x1e bytes, Thumb
 * func_02089ca4 @ 0x02089ca4, 0x1c bytes, Thumb
 * func_02089c88 @ 0x02089c88, 0x1c bytes, Thumb
 * func_02089c70 @ 0x02089c70, 0x18 bytes, Thumb
 * func_02089c58 @ 0x02089c58, 0x18 bytes, Thumb
 * func_02089c50 @ 0x02089c50, 0x6 bytes, Thumb
 * func_02089c48 @ 0x02089c48, 0x6 bytes, Thumb
 * func_02089c20 @ 0x02089c20, 0x28 bytes, Thumb
 * func_02089bec @ 0x02089bec, 0x34 bytes, Thumb
 * func_02089bd4 @ 0x02089bd4, 0x18 bytes, Thumb
 * func_02089bbc @ 0x02089bbc, 0x18 bytes, Thumb
 * func_02089b80 @ 0x02089b80, 0x3a bytes, Thumb
 * func_02089b68 @ 0x02089b68, 0x18 bytes, Thumb
 * func_02089b50 @ 0x02089b50, 0x18 bytes, Thumb
 * func_02089b38 @ 0x02089b38, 0x18 bytes, Thumb
 * func_02089b20 @ 0x02089b20, 0x18 bytes, Thumb
 */

typedef struct UnkStruct_02089cc0 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
    unsigned char pad_2C[0x10];
    unsigned char unk_3C;
} UnkStruct_02089cc0;

struct UnkStruct_02089c88 {
    void *unk_00;
    char pad_04[0x3C];
    int unk_40;
};

struct UnkStruct_02089c70 {
    void *unk_00;
};

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char sub;
} UnkStruct_02089c50;

typedef struct {
    unsigned char pad_00[0x40];
    UnkStruct_02089c50 *ptr;
} UnkStruct_02089c50_2;

typedef struct {
    unsigned char pad_00[4];
    void *unk_04;
} UnkStruct_02089c48;

typedef struct {
    unsigned char pad_00[0x40];
    UnkStruct_02089c48 *ptr;
} UnkStruct_02089c48_2;

struct UnkStruct_02089c20 {
    char pad_00[0x40];
    int unk_40;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
} Dst;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Src;

typedef struct {
    char pad_00[0x44];
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
} DestStruct;

typedef struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
} SrcStruct;

typedef struct {
    void *unk_00;
} UnkStruct_02089b68;

typedef struct {
    void *vtable;
} UnkStruct_02089b50;

typedef struct {
    unsigned char *unk_00;
} UnkStruct_02089b38;

struct UnkStruct_02089b20 {
    void *unk_00;
};

extern void *func_0208a088(void *obj);
extern unsigned char data_020e2008[];
extern void func_0208a07c(void *self);
extern void func_0208a000(struct UnkStruct_02089c20 *p, int b, int c, int d, int e, int f, unsigned char g, int h);
extern int data_020e2044;
extern char data_020e2030[];

int func_02089cc0(UnkStruct_02089cc0 *p, unsigned int mask)
{
    if (p->unk_3C != 0) {
        if ((p->unk_28 & mask) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void *func_02089ca4(void *obj)
{
    func_0208a088(obj);
    *(void **) obj = (void *) data_020e2008;
    *(int *) ((char *) obj + 0x40) = 0;
    return obj;
}

struct UnkStruct_02089c88 *func_02089c88(struct UnkStruct_02089c88 *obj)
{
    func_0208a088(obj);
    obj->unk_00 = ((char *) data_020e2008);
    obj->unk_40 = 0;
    return obj;
}

struct UnkStruct_02089c70 *func_02089c70(struct UnkStruct_02089c70 *self)
{
    self->unk_00 = ((int *) data_020e2008);
    func_0208a07c(self);
    return self;
}

void *func_02089c58(void *self)
{
    *(void **) self = ((char *) data_020e2008);
    func_0208a07c(self);
    return self;
}

void *func_02089c50(UnkStruct_02089c50_2 *p)
{
    return &p->ptr->sub;
}

void *func_02089c48(UnkStruct_02089c48_2 *p)
{
    return p->ptr->unk_04;
}

void func_02089c20(struct UnkStruct_02089c20 *p, int a, int b, int c, int d, int e, int f, unsigned char g, int h)
{
    p->unk_40 = a;
    func_0208a000(p, b, c, d, e, f, g, h);
}

void func_02089bec(Dst *dest, const Src *src, int a, int b, int c, int d, int e, unsigned char f, int g)
{
    dest->unk_40 = src->unk_00;
    dest->unk_44 = src->unk_04;
    dest->unk_48 = src->unk_08;
    func_0208a000((struct UnkStruct_02089c20 *) dest, a, b, c, d, e, f, g);
}

void *func_02089bd4(void *arg)
{
    func_02089ca4(arg);
    *(int *) arg = (int) &data_020e2044;
    return arg;
}

void *func_02089bbc(void *obj)
{
    *(void **) obj = (void *) ((char *) &data_020e2044);
    func_02089c58(obj);
    return obj;
}

void func_02089b80(DestStruct *dest, int param1, SrcStruct *src, int param3, int param4, int param5, int param6, int param7,
                   unsigned char param8, int param9)
{
    func_02089c20((struct UnkStruct_02089c20 *) dest, param1, param3, param4, param5, param6, param7, param8, param9);
    dest->f0 = src->f0;
    dest->f1 = src->f1;
    dest->f2 = src->f2;
}

UnkStruct_02089b68 *func_02089b68(UnkStruct_02089b68 *obj)
{
    func_0208a088(obj);
    obj->unk_00 = ((char *) data_020e2030);
    return obj;
}

UnkStruct_02089b50 *func_02089b50(UnkStruct_02089b50 *self)
{
    func_0208a088((void *) self);
    self->vtable = (void *) &data_020e2030;
    return self;
}

UnkStruct_02089b38 *func_02089b38(UnkStruct_02089b38 *arg)
{
    arg->unk_00 = ((unsigned char *) data_020e2030);
    func_0208a07c((void *) arg);
    return arg;
}

struct UnkStruct_02089b20 *func_02089b20(struct UnkStruct_02089b20 *arg)
{
    arg->unk_00 = ((int *) data_020e2030);
    func_0208a07c(arg);
    return arg;
}
