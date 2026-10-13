/* func_0202ff68 @ 0x0202ff68, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
extern int VEC_DotProduct(int *a, void *b);
extern int FX_MulFunc(int a, int b);
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
