/* func_ov004_02242228 @ 0x02242228, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242228 {
    char unk_00[0x168];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02242228;

extern UnkStruct_02242228 *func_ov004_0223ee38(void);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern void func_ov004_02244fb8(Vec3 *d, int a);
extern void func_ov004_02242a9c(UnkStruct_02242228 *o, int a, int b);
extern void func_020eac34(Vec3 *d, Vec3 *s, int k);
extern void VEC_Subtract(Vec3 *d, Vec3 *a, Vec3 *b);
extern int func_ov004_02244c20(UnkStruct_02242228 *self);

void func_ov004_02242228(UnkStruct_02242228 *self)
{
    UnkStruct_02242228 *o;
    int t1, t2;
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 *p, *q;
    short *n;

    o = func_ov004_0223ee38();
    p = &self->pos;
    q = &o->pos;
    n = &self->unk_168;
    if (func_020ea990(p, q) < 0x2000) {
        t1 = func_0200322c(q, p);
        o->unk_192 = (short) t1;
        func_ov004_02244fb8(&a, t1);
        func_ov004_02242a9c(o, t1, *n);
        t2 = func_0200322c(p, q);
        self->unk_192 = (short) t2;
        func_ov004_02244fb8(&b, t2);
        func_ov004_02242a9c(self, t2, *n);
        func_020eac34(&c, &b, 0x4000);
        VEC_Subtract(p, &c, p);
        func_020eac34(&d, &a, 0x4000);
        VEC_Subtract(q, &d, q);
        *n = (short) (*n + 1);
    } else if (func_ov004_02244c20(self) != 0) {
        self->unk_172 = 0x19;
        *n = 0;
    }
}
