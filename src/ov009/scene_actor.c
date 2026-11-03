/* scene_actor: 14 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02262fd8 @ 0x02262fd8, 0x20 bytes, Thumb
 * func_ov009_02262fcc @ 0x02262fcc, 0xc bytes, Thumb
 * func_ov009_02262fc0 @ 0x02262fc0, 0xc bytes, Thumb
 * func_ov009_02262fb4 @ 0x02262fb4, 0xc bytes, Thumb
 * func_ov009_02262fa4 @ 0x02262fa4, 0x10 bytes, Thumb
 * func_ov009_02262f8c @ 0x02262f8c, 0x18 bytes, Thumb
 * func_ov009_02262f74 @ 0x02262f74, 0x18 bytes, Thumb
 * func_ov009_02262f54 @ 0x02262f54, 0x1e bytes, Thumb
 * func_ov009_02262f2c @ 0x02262f2c, 0x26 bytes, Thumb
 * func_ov009_02262f0c @ 0x02262f0c, 0x1e bytes, Thumb
 * func_ov009_02262ef0 @ 0x02262ef0, 0x1c bytes, Thumb
 * func_ov009_02262ed4 @ 0x02262ed4, 0x1c bytes, Thumb
 * func_ov009_02262ec4 @ 0x02262ec4, 0xe bytes, Thumb
 * func_ov009_02262ec0 @ 0x02262ec0, 0x4 bytes, Thumb
 */

struct UnkStruct_02262fd8 {
    unsigned char pad_00[0x27c];
    unsigned int unk_27C;
};

struct UnkStruct_02262f8c {
    char pad_00[0x40];
    char flag;
};

struct UnkStruct_02262f54 {
    unsigned char pad_00[0x40];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[0x40];
    unsigned char flag;
} UnkStruct_02262f2c;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Triple;

typedef struct {
    unsigned char pad_00[0x40];
    unsigned char flag;
} UnkStruct_02262f0c;

struct UnkStruct_02262ef0 {
    unsigned char pad_00[0x40];
    unsigned char flag;
};

extern int func_ov009_02262ff8(struct UnkStruct_02262fd8 *self);
extern int func_020b3310(int a);
extern void *func_020f539c(struct UnkStruct_02262f8c *p);
extern void func_020f5914(void *);
extern unsigned char data_0213f090[];
extern void func_0200451c(void *p);
extern void func_020044d0(UnkStruct_02262f2c *a, Triple *t);
extern int func_020044a0(void *);
extern int func_020044c0(void *self, int arg, int c, int d);
extern int func_020044b0(unsigned char *a, int b, int c, int d);

int func_ov009_02262fd8(struct UnkStruct_02262fd8 *self)
{
    if (self->unk_27C == 0) {
        return func_ov009_02262ff8(self);
    } else {
        return 0;
    }
}

int func_ov009_02262fcc(int a)
{
    return a + 0x136;
}

int func_ov009_02262fc0(void *p)
{
    return *(int *) ((char *) p + 0x22c);
}

unsigned int func_ov009_02262fb4(unsigned int *param0)
{
    return param0[0x8c];
}

int func_ov009_02262fa4(int a)
{
    return func_020b3310(a + 500);
}

void *func_ov009_02262f8c(struct UnkStruct_02262f8c *obj)
{
    func_020f539c(obj);
    obj->flag = 0;
    return obj;
}

void *func_ov009_02262f74(void *obj)
{
    *(void **) obj = (void *) data_0213f090;
    func_020f5914(obj);
    return obj;
}

void func_ov009_02262f54(struct UnkStruct_02262f54 *this)
{
    if (this->flag == 0) {
        func_0200451c(this);
        this->flag = 1;
    }
}

void func_ov009_02262f2c(UnkStruct_02262f2c *a, Triple *b)
{
    if (a->flag != 0) {
        Triple local;
        local.x = b->x;
        local.y = b->y;
        local.z = b->z;
        func_020044d0(a, &local);
    }
}

void func_ov009_02262f0c(UnkStruct_02262f0c *self)
{
    if (self->flag) {
        func_020044a0(self);
        self->flag = 0;
    }
}

void func_ov009_02262ef0(struct UnkStruct_02262ef0 *self, int arg)
{
    if (self->flag != 0) {
        func_020044c0(self, arg, 0x7f, 0);
    }
}

void func_ov009_02262ed4(unsigned char *self, int arg1)
{
    unsigned char *p = self;
    p += 0x40;
    if (*p != 0) {
        func_020044b0(self, arg1, 0x7f, 0);
    }
}

void func_ov009_02262ec4(void *r0, void *r1)
{
    *(unsigned int *) (r0) = *(unsigned int *) ((char *) r1 + 0x5c);
    *(unsigned int *) ((char *) r0 + 4) = *(unsigned int *) ((char *) r1 + 0x60);
    *(unsigned int *) ((char *) r0 + 8) = *(unsigned int *) ((char *) r1 + 0x64);
}

int func_ov009_02262ec0(void *object)
{
    return 0;
}
