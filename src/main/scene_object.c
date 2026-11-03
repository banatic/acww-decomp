/* scene_object: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201b790 @ 0x0201b790, 0x180 bytes, Thumb
 * func_0201b78c @ 0x0201b78c, 0x2 bytes, Thumb
 * func_0201b744 @ 0x0201b744, 0x48 bytes, Thumb
 * func_0201b6fc @ 0x0201b6fc, 0x48 bytes, Thumb
 * func_0201b6e4 @ 0x0201b6e4, 0x16 bytes, Thumb
 * func_0201b6e0 @ 0x0201b6e0, 0x4 bytes, Thumb
 * func_0201b6dc @ 0x0201b6dc, 0x4 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    unsigned char data[0x24];
    Vec vec;
    Vec copy1;
    Vec copy2;
    Vec copy3;
} Buf;

typedef struct UnkStruct_0201b790 {
    unsigned char pad_00[0x5c];
    Vec vec;
    unsigned char pad_68[0xec - 0x68];
    unsigned char ec[0x3b0 - 0xec];
    unsigned char unk_3B0[0x448 - 0x3b0];
    unsigned char unk_448[0x478 - 0x448];
    Vec v1;
    Vec v2;
    Vec v3;
    unsigned char pad_49C[0x511 - 0x49c];
    unsigned char unk_511;
    unsigned char pad_512[0x561 - 0x512];
    unsigned char unk_561;
    unsigned char unk_562;
} UnkStruct_0201b790;

extern void func_02054848(void *a, int b);
extern void func_0201adbc(void *a, void *b);
extern int func_02055d0c(void *a, void *b, unsigned int c);
extern int func_0203f7d0(void *a, void *b);
extern void func_020acc0c(void *a, unsigned int b, unsigned int c, unsigned int d);
extern int func_0201c450(void *p);
extern void func_02019ff0(void *p);
extern void func_0201637c(void *p);
extern int func_0200441c(void *p);
extern void func_0201bf24(void *p, int n);
extern void func_02095eec(int a, int b);

int func_0201b790(UnkStruct_0201b790 *self)
{
    if (self->unk_561 == 0) {
        Vec *p = &self->vec;
        self->v1.x = self->vec.x;
        self->v1.y = p->y;
        self->v1.z = p->z;
        self->v2.x = self->vec.x;
        self->v2.y = p->y;
        self->v2.z = p->z;
        self->v3.x = self->vec.x;
        self->v3.y = p->y;
        self->v3.z = p->z;
        return 1;
    }
    if (self->unk_562 == 0) {
        Vec *p = &self->vec;
        self->v1.x = self->vec.x;
        self->v1.y = p->y;
        self->v1.z = p->z;
        self->v2.x = self->vec.x;
        self->v2.y = p->y;
        self->v2.z = p->z;
        self->v3.x = self->vec.x;
        self->v3.y = p->y;
        self->v3.z = p->z;
        return 1;
    }
    func_02054848(&self->ec[0], 0);
    func_0201adbc(&self->unk_3B0[0], (void *) self);
    func_02055d0c(&self->ec[0], &self->unk_448[0], 0xb);
    {
        Buf buf;
        func_02055d0c(&self->ec[0], &buf, 0x10);
        buf.copy1.x = buf.vec.x;
        buf.copy1.y = buf.vec.y;
        buf.copy1.z = buf.vec.z;
        func_0203f7d0(&self->v1, &buf.copy1);
        func_02055d0c(&self->ec[0], &buf, 7);
        buf.copy2.x = buf.vec.x;
        buf.copy2.y = buf.vec.y;
        buf.copy2.z = buf.vec.z;
        func_0203f7d0(&self->v2, &buf.copy2);
        func_02055d0c(&self->ec[0], &buf, 4);
        buf.copy3.x = buf.vec.x;
        buf.copy3.y = buf.vec.y;
        buf.copy3.z = buf.vec.z;
        func_0203f7d0(&self->v3, &buf.copy3);
    }
    if (self->unk_511 != 0) {
        self = (UnkStruct_0201b790 *) ((char *) self + 0x5c);
        func_020acc0c(self, 0xb00, 0x4000, 0x1000);
    }
    return 1;
}

void func_0201b78c(void) {}

int func_0201b744(unsigned char *base)
{
    func_0201c450(base);
    func_02019ff0(base + 0x2ac);
    func_0201637c(base + 0x334);
    func_0200441c(base + 0x514);
    if (base[0x563] == 0) {
        func_0201bf24(base, 1);
    }
    return 1;
}

int func_0201b6fc(void *r0, void *r1)
{
    int r3;
    int r2;
    int r0_2;

    r3 = *(int *) ((char *) r0 + 0x46c);
    if (r3 == 0) {
        r2 = *(int *) ((char *) r0 + 0x470);
        if (r2 == 0) {
            r2 = *(int *) ((char *) r0 + 0x474);
            if (r2 == 0) {
                return 0;
            }
        }
    }
    *(int *) r1 = r3;
    r2 = *(int *) ((char *) r0 + 0x470);
    *(int *) ((char *) r1 + 4) = r2;
    r0_2 = *(int *) ((char *) r0 + 0x474);
    *(int *) ((char *) r1 + 8) = r0_2;
    func_0203f7d0(r1, r1);
    return 1;
}

void func_0201b6e4(int a, int b, int participant)
{
    if (b == 8) {
        func_02095eec(0, 4);
    }
}

int func_0201b6e0(void *object)
{
    (void) object;
    return 0;
}

int func_0201b6dc(void *object)
{
    (void) object;
    return 0;
}
