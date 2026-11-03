/* field_actor_61: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02210010 @ 0x02210010, 0x84 bytes, Thumb
 * func_ov003_0220ffc0 @ 0x0220ffc0, 0x50 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

struct UnkStruct_02210010 {
    char pad_00[0xc];
    unsigned char c0;
    unsigned char c1;
    unsigned char c2;
};

struct S7d4 {
    unsigned char b[0x10];
};

struct UnkStruct_02210010_3 {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x7d4 - 0x68];
    struct S7d4 unk_7D4;
    char pad_7E4[0x8f0 - 0x7e4];
    char unk_8F0[1];
};

struct UnkStruct_02210010_2 {
    Vec d;
    Vec v;
    Vec v2;
};

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0xfc];
    int unk_8F0;
    char pad_8F4[0x390];
    short unk_C84;
} UnkStruct_0220ffc0;

extern void func_0204f794(void *, int, int);
extern int func_020e8ed8(int, int);
extern void func_ov003_022100ac(void *, int, int, void *);
extern void func_ov003_022100a0(void *, void *);
extern void func_020109fc(void *, int, int, int);
extern unsigned int *func_0200f27c(void *, int);
extern void func_ov003_02210094(int *src, int *dst);
extern int func_ov003_022100c4(void *self, int *out, int a, int b, int c);

void func_ov003_02210010(struct UnkStruct_02210010_3 *o, struct UnkStruct_02210010 *b, int previous)
{
    int k;
    int pair[2];
    struct UnkStruct_02210010_2 t;
    int ang;
    unsigned char *p = &b->c0;
    struct S7d4 *q = &o->unk_7D4;
    int x = *p;
    int z = *(p + 1);
    k = *(p + 2);
    func_0204f794(&t.v, x, z);
    t.d.x = t.v.x - o->unk_5C;
    t.d.z = t.v.z - o->unk_64;
    ang = func_020e8ed8(t.d.x, t.d.z);
    t.v2.x = t.v.x;
    t.v2.y = t.v.y;
    t.v2.z = t.v.z;
    func_ov003_022100ac(q, k, ang, &t.v2);
    pair[0] = x;
    pair[1] = z;
    func_ov003_022100a0(o->unk_8F0, pair);
    func_020109fc(o, 0x64, 3, 0);
    if (q->b[0xf] == 1) {
        func_0200f27c(o, 0x1c);
    }
}

void func_ov003_0220ffc0(UnkStruct_0220ffc0 *self, int param)
{
    if (self->unk_7F0 == 0x66) {
        self->unk_C84 = (short) param;
    } else {
        int tmp[2];
        int out[2];
        tmp[0] = 0;
        tmp[1] = 0;
        func_ov003_02210094(&self->unk_8F0, tmp);
        out[0] = tmp[0];
        out[1] = tmp[1];
        func_ov003_022100c4(self, out, 0, 6, param);
    }
}
