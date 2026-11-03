/* collision_line: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203005c @ 0x0203005c, 0x10 bytes, Thumb
 * func_02030058 @ 0x02030058, 0x2 bytes, Thumb
 * func_0203002c @ 0x0203002c, 0x2c bytes, Thumb
 * func_0203000c @ 0x0203000c, 0x1e bytes, Thumb
 * func_0202ffe8 @ 0x0202ffe8, 0x24 bytes, Thumb
 * func_0202ffbc @ 0x0202ffbc, 0x2a bytes, Thumb
 * func_0202ff68 @ 0x0202ff68, 0x54 bytes, Thumb
 * func_0202ff14 @ 0x0202ff14, 0x54 bytes, Thumb
 */

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0203002c;

typedef struct {
    unsigned char pad_00[0xc];
    UnkStruct_0203002c unk_0C;
} UnkStruct_0203002c_2;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char pad_0C[0xc];
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_0202ff68;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0202ff68_2;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char pad_0D[0xb];
    unsigned char unk_18;
} UnkStruct_0202ff14;

extern void func_020eaca0(UnkStruct_0203002c *out, UnkStruct_0203002c *in, UnkStruct_0203002c_2 *a);
extern int func_020ea838(UnkStruct_0203002c *v);
extern int func_020ea9e4(void *, void *);
extern int VEC_DotProduct(int *a, void *b);
extern int FX_MulFunc(int a, int b);

void func_0202ffe8(unsigned int *dest, const unsigned int *src1, const unsigned int *src2);
void func_0202ff68(UnkStruct_0202ff68 *p, UnkStruct_0202ff68_2 *out, void *q);

int func_0203005c(int arg, const unsigned int *argument1, const unsigned int *argument2)
{
    func_0202ffe8((unsigned int *) arg, (const unsigned int *) argument1, (const unsigned int *) argument2);
    return arg;
}

void func_02030058(void *self) {}

void func_0203002c(UnkStruct_0203002c_2 *a, UnkStruct_0203002c *out)
{
    UnkStruct_0203002c t;
    func_020eaca0(&t, &a->unk_0C, a);
    out->x = t.x;
    out->y = t.y;
    out->z = t.z;
    func_020ea838(out);
}

int func_0203000c(int a, void *b)
{
    char buffer[16];
    func_0202ff68((UnkStruct_0202ff68 *) a, (UnkStruct_0202ff68_2 *) buffer, b);
    return func_020ea9e4(buffer, b);
}

void func_0202ffe8(unsigned int *dest, const unsigned int *src1, const unsigned int *src2)
{
    dest[0] = src1[0];
    dest[1] = src1[1];
    dest[2] = src1[2];
    dest[3] = src2[0];
    dest[4] = src2[1];
    dest[5] = src2[2];
    func_0203002c((UnkStruct_0203002c_2 *) dest, (UnkStruct_0203002c *) (dest + 6));
}

int func_0202ffbc(int a, Vec3 *out, int b)
{
    Vec3 local;
    func_0202ff68((UnkStruct_0202ff68 *) a, (UnkStruct_0202ff68_2 *) (&local), (void *) b);
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
    return func_020ea9e4((void *) (&local), (void *) b);
}

void func_0202ff68(UnkStruct_0202ff68 *p, UnkStruct_0202ff68_2 *out, void *q)
{
    int t;
    int a;
    int b;
    int x;
    int y;
    int z;
    a = VEC_DotProduct(&p->unk_18, q);
    b = VEC_DotProduct(&p->unk_18, p);
    t = -(b - a);
    {
        int m = FX_MulFunc(p->unk_20, t);
        z = m + p->unk_08;
    }
    {
        int m = FX_MulFunc(p->unk_1C, t);
        y = m + p->unk_04;
    }
    {
        int m = FX_MulFunc(p->unk_18, t);
        x = m + p->unk_00;
    }
    out->x = x;
    out->y = y;
    out->z = z;
}

int func_0202ff14(UnkStruct_0202ff14 *a, UnkStruct_0202ff14 *b)
{
    int v1 = VEC_DotProduct((int *) (&a->unk_18), a);
    int v2 = VEC_DotProduct((int *) (&a->unk_18), b);
    int v3 = VEC_DotProduct((int *) (&a->unk_18), &a->unk_0C);
    int v4 = VEC_DotProduct((int *) (&a->unk_18), b);
    int d1 = v2 - v1;
    int d2 = v4 - v3;
    return (FX_MulFunc(d1, d2) > 0) ? 0 : 1;
}
