/* func_0201b790 @ 0x0201b790, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
extern void func_02055d0c(void *a, void *b, unsigned int c);
extern void func_0203f7d0(void *a, void *b);
extern void func_020acc0c(void *a, unsigned int b, unsigned int c, unsigned int d);

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
