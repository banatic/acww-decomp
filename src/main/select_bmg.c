/* select_bmg: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ab960 @ 0x020ab960, 0x28 bytes, Thumb
 * func_020ab948 @ 0x020ab948, 0x18 bytes, Thumb
 * func_020ab928 @ 0x020ab928, 0x20 bytes, Thumb
 * func_020ab91c @ 0x020ab91c, 0xc bytes, Thumb
 * func_020ab90c @ 0x020ab90c, 0xe bytes, Thumb
 * func_020ab904 @ 0x020ab904, 0x6 bytes, Thumb
 * func_020ab8fc @ 0x020ab8fc, 0x6 bytes, Thumb
 * func_020ab8dc @ 0x020ab8dc, 0x20 bytes, Thumb
 * func_020ab8c4 @ 0x020ab8c4, 0x18 bytes, Thumb
 * func_020ab8a4 @ 0x020ab8a4, 0x20 bytes, Thumb
 * func_020ab8a0 @ 0x020ab8a0, 0x4 bytes, Thumb
 * func_020ab89c @ 0x020ab89c, 0x4 bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xA0];
    int unk_A4;
    int unk_A8;
} UnkStruct_020ab960;

struct UnkStruct_020ab928 {
    void *vtable;
};

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} UnkStruct_020ab91c;

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} UnkStruct_020ab90c;

typedef struct {
    unsigned char pad_00[164];
    unsigned long unk_A4;
} UnkStruct_020ab904;

typedef struct {
    unsigned char pad_00[168];
    unsigned long unk_A8;
} UnkStruct_020ab8fc;

extern void *func_020a9a90(void *obj, int param);
extern void *func_020a9a40(void *self);
extern void func_020edb3c(void *);
extern unsigned char data_020e3fcc[];
extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020e3f9c;
extern void *func_020a8c38(void *);

UnkStruct_020ab960 *func_020ab960(UnkStruct_020ab960 *obj)
{
    func_020a9a90(obj, 1);
    obj->unk_00 = ((int *) data_020e3fcc);
    obj->unk_A4 = 0;
    obj->unk_A8 = 0;
    return obj;
}

void *func_020ab948(void *self)
{
    *(unsigned int *) self = (unsigned int) ((char *) data_020e3fcc);
    func_020a9a40(self);
    return self;
}

struct UnkStruct_020ab928 *func_020ab928(struct UnkStruct_020ab928 *obj)
{
    obj->vtable = (void *) data_020e3fcc;
    func_020a9a40(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020ab91c(UnkStruct_020ab91c *arg0, int arg1, int arg2)
{
    arg0->unk_A4 = arg1;
    arg0->unk_A8 = arg2;
}

void func_020ab90c(UnkStruct_020ab90c *arg)
{
    arg->unk_A4 = 0;
    arg->unk_A8 = 0;
}

unsigned long func_020ab904(UnkStruct_020ab904 *p)
{
    return p->unk_A4;
}

unsigned long func_020ab8fc(UnkStruct_020ab8fc *p)
{
    return p->unk_A8;
}

void *func_020ab8dc(void *self)
{
    func_020a8cac(self);
    *(void **) self = &data_020e3f9c;
    func_020a8c1c(self);
    return self;
}

void *func_020ab8c4(void *self)
{
    *(void **) self = &data_020e3f9c;
    func_020a8c38(self);
    return self;
}

void *func_020ab8a4(void *this)
{
    *(void **) this = &data_020e3f9c;
    func_020a8c38(this);
    func_020edb3c(this);
    return this;
}

int func_020ab8a0(void)
{
    return 72;
}

int func_020ab89c(int p0)
{
    return ((int) (p0) + (18));
}
