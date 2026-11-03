/* menu_scene_2: 16 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220830c @ 0x0220830c, 0x38 bytes, Thumb
 * func_ov002_022082d8 @ 0x022082d8, 0x34 bytes, Thumb
 * func_ov002_022082a0 @ 0x022082a0, 0x38 bytes, Thumb
 * func_ov002_0220826c @ 0x0220826c, 0x34 bytes, Thumb
 * func_ov002_0220823c @ 0x0220823c, 0x30 bytes, Thumb
 * func_ov002_022081f4 @ 0x022081f4, 0x48 bytes, Thumb
 * func_ov002_022081dc @ 0x022081dc, 0x18 bytes, Thumb
 * func_ov002_022081b8 @ 0x022081b8, 0x22 bytes, Thumb
 * func_ov002_022081a0 @ 0x022081a0, 0x18 bytes, Thumb
 * func_ov002_02208198 @ 0x02208198, 0x8 bytes, Thumb
 * func_ov002_02208168 @ 0x02208168, 0x30 bytes, Thumb
 * func_ov002_02208164 @ 0x02208164, 0x4 bytes, Thumb
 * func_ov002_02208160 @ 0x02208160, 0x4 bytes, Thumb
 * func_ov002_0220815c @ 0x0220815c, 0x4 bytes, Thumb
 * func_ov002_02208158 @ 0x02208158, 0x4 bytes, Thumb
 * func_ov002_02208154 @ 0x02208154, 0x4 bytes, Thumb
 */

struct UnkStruct_0220830c {
    int *vptr;
    char pad_04[0x4c];
    char sub1[0x14];
    int unk_64;
    int unk_68;
    char pad_6C[4];
    char sub2[1];
};

typedef struct {
    char data[0x10];
} Sub50;

typedef struct {
    char data[0x10];
} Sub70;

typedef struct {
    void *vtbl;
    char pad_04[0x50 - 4];
    Sub50 unk_50;
    char pad2[0x70 - 0x50 - sizeof(Sub50)];
    Sub70 unk_70;
} UnkStruct_022082d8;

typedef struct UnkStruct_0220823c {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x6C - 0x0C];
    struct UnkStruct_0220823c *unk_6C;
    char pad_70[0x90 - 0x70];
    unsigned char unk_90;
} UnkStruct_0220823c;

struct UnkStruct_022081f4 {
    char pad_00[0x64];
    char unk_64;
};

struct UnkStruct_022081f4_2 {
    char pad_00[0x34];
    unsigned short unk_34;
    char pad_36[0xe];
    unsigned short unk_44;
};

extern int data_020da13c;
extern int data_ov002_0220bb24;
extern void *func_020ee660(void *p);
extern void func_ov002_022089e0(void *sub);
extern void *func_ov002_022087d4(void *sub);
extern void *func_ov002_022087bc(void *);
extern void func_ov002_022089d4(void *);
extern void func_020ee62c(void *);
extern void func_ov002_02207f6c(void *ptr);
extern int func_020ee61c(void);
extern void func_ov002_02208880(void *, int, int, int);
extern void func_02070204(char *arg);
extern struct UnkStruct_022081f4_2 *func_020ee45c(struct UnkStruct_022081f4 *p);
extern void func_020ee3c0(struct UnkStruct_022081f4 *p, unsigned short x);
extern void func_020ee324(struct UnkStruct_022081f4 *p, unsigned short x);
extern void func_0202f144(struct UnkStruct_022081f4 *p, int x);
extern int func_020ee550(void *object);
extern void func_020701e4(void *);
extern void func_020ee4d8(void *, int);
extern int func_01ffd41c(unsigned char *arg0);
extern void func_01ffd418(void *object);
extern int func_0206f258(void);
extern int func_0206f244(void);
extern void func_0206ef70(void);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);

struct UnkStruct_0220830c *func_ov002_0220830c(struct UnkStruct_0220830c *obj)
{
    func_020ee660(obj);
    obj->vptr = &data_020da13c;
    obj->vptr = &data_ov002_0220bb24;
    func_ov002_022089e0(obj->sub1);
    obj->unk_64 = 0;
    obj->unk_68 = 0;
    func_ov002_022087d4(obj->sub2);
    return obj;
}

UnkStruct_022082d8 *func_ov002_022082d8(UnkStruct_022082d8 *p)
{
    p->vtbl = ((char *) &data_ov002_0220bb24);
    func_ov002_022087bc(&p->unk_70);
    func_ov002_022089d4(&p->unk_50);
    p->vtbl = ((char *) &data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_ov002_022082a0(void *obj)
{
    *(void **) obj = ((char *) &data_ov002_0220bb24);
    func_ov002_022087bc((void *) ((char *) obj + 0x70));
    func_ov002_022089d4((void *) ((char *) obj + 0x50));
    *(void **) obj = ((char *) &data_020da13c);
    func_020ee62c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}

void *func_ov002_0220826c(void *self)
{
    *(int *) self = (int) &data_ov002_0220bb24;
    func_ov002_022087bc((void *) ((char *) self + 0x70));
    func_ov002_022089d4((void *) ((char *) self + 0x50));
    *(int *) self = (int) &data_020da13c;
    func_020ee62c(self);
    return self;
}

int func_ov002_0220823c(UnkStruct_0220823c *self)
{
    if (!func_020ee61c()) {
        return 0;
    }
    self->unk_90 = self->unk_08;
    self->unk_6C = self;
    self = (UnkStruct_0220823c *) ((char *) self + 0x50);
    func_ov002_02208880(self, 8, 1, 7);
    return 1;
}

void func_ov002_022081f4(struct UnkStruct_022081f4 *p, int param2)
{
    func_02070204(&p->unk_64);
    if (param2 == 2) {
        struct UnkStruct_022081f4_2 *q = func_020ee45c(p);
        if (q != 0) {
            func_020ee3c0(p, q->unk_34 + 1);
            func_020ee324(p, q->unk_44 + 1);
        }
    }
    func_0202f144(p, param2);
}

int func_ov002_022081dc(void *object)
{
    if (func_020ee550(object) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov002_022081b8(void *r0, int r1)
{
    void *r5 = r0;
    int r4 = r1;
    if (r4 == 2) {
        func_020701e4((char *) r5 + 0x64);
    }
    func_020ee4d8(r5, r4);
}

int func_ov002_022081a0(int result)
{
    if (func_01ffd41c((unsigned char *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_ov002_02208198(void *object)
{
    func_01ffd418(object);
}

int func_ov002_02208168(int param)
{
    int r4 = param;
    if (func_0206f258() != 0) {
        func_ov002_022080a0(r4, 1);
    }
    if (func_0206f244() != 0) {
        func_0206ef70();
        func_ov002_022080a0(r4, 5);
    }
    return 1;
}

int func_ov002_02208164(void)
{
    return 1;
}

int func_ov002_02208160(void)
{
    return 1;
}

int func_ov002_0220815c(void)
{
    return 1;
}

int func_ov002_02208158(void)
{
    return 1;
}

int func_ov002_02208154(void)
{
    return 1;
}
