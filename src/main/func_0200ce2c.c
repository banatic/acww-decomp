/* func_0200ce2c @ 0x0200ce2c, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200ce2c {
    int x, y, z;
} UnkStruct_0200ce2c;

typedef struct UnkStruct_0200ce2c_2 {
    int unk_00;
    int unk_04;
    char pad_08[0x10 - 8];
    int unk_10;
} UnkStruct_0200ce2c_2;

typedef struct Other {
    char pad_00[0x9c];
    UnkStruct_0200ce2c_2 sub;
} Other;

typedef struct UnkStruct_0200ce2c_3 {
    char pad_00[0x5c];
    UnkStruct_0200ce2c v;
    char pad_68[0x98 - 0x68];
    int unk_98;
    char pad_9C[0x134 - 0x9c];
    int unk_134;
    short unk_138;
    char pad_13A[0x234 - 0x13a];
    char unk_234;
    char pad_235[0x2d4 - 0x235];
    int unk_2D4;
    char pad_2D8[0x2e0 - 0x2d8];
    int unk_2E0;
    char pad_2E4[0x5a0 - 0x2e4];
    char unk_5A0;
    char pad_5A1[0x704 - 0x5a1];
    int unk_704;
} UnkStruct_0200ce2c_3;

extern int func_020b03c0(UnkStruct_0200ce2c *out, int *b, int *c, int d, int e);
extern void func_020110a0(UnkStruct_0200ce2c_3 *s, int *p);
extern int func_020ea990(UnkStruct_0200ce2c *a, UnkStruct_0200ce2c *b);
extern void func_0201107c(UnkStruct_0200ce2c_3 *s, int *p);
extern int FX_MulFunc(int a, int b);
extern Other *func_0205e8e4(void *p);
extern void func_020109c8(UnkStruct_0200ce2c_3 *s, int a, int b, int c);
extern void func_02054860(void *p);
extern void func_0200f95c(UnkStruct_0200ce2c_3 *s);

void func_0200ce2c(UnkStruct_0200ce2c_3 *self)
{
    int b;
    int v;
    int c;
    UnkStruct_0200ce2c nv;
    UnkStruct_0200ce2c old;
    int ok;
    int r;
    UnkStruct_0200ce2c *p;
    UnkStruct_0200ce2c_2 *q;

    v = self->unk_98;
    p = &self->v;
    old.x = p->x;
    old.y = p->y;
    old.z = p->z;
    ok = func_020b03c0(&nv, &b, &c, self->unk_134, self->unk_138);
    if (ok) {
        p = &self->v;
        p->x = nv.x;
        p->y = nv.y;
        p->z = nv.z;
        func_020110a0(self, &b);
        v = func_020ea990(&self->v, &old);
        func_0201107c(self, &v);
        v = c;
        v = v << 2;
    }
    r = FX_MulFunc(v, 0x3ae1);
    if (r <= self->unk_2D4) {
        self->unk_2E0 = r;
        q = &func_0205e8e4(&self->unk_5A0)->sub;
        if (r <= q->unk_04) {
            q = &func_0205e8e4(&self->unk_5A0)->sub;
            q->unk_10 = r;
        }
    }
    if (ok) {
        if (self->unk_704 != 3) {
            func_020109c8(self, 3, 3, 3);
        }
    } else {
        if (v > 0x53f) {
            if (self->unk_704 != 2) {
                func_020109c8(self, 2, 3, 3);
            }
        } else {
            if (self->unk_704 != 1) {
                func_020109c8(self, 1, 3, 3);
            }
        }
    }
    func_02054860(&self->unk_234);
    func_0200f95c(self);
}
