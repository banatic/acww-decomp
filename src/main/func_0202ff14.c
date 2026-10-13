/* func_0202ff14 @ 0x0202ff14, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int VEC_DotProduct(void *p, void *q);
extern int FX_MulFunc(int x, int y);

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char pad_0D[0xb];
    unsigned char unk_18;
} UnkStruct_0202ff14;

int func_0202ff14(UnkStruct_0202ff14 *a, UnkStruct_0202ff14 *b)
{
    int v1 = VEC_DotProduct(&a->unk_18, a);
    int v2 = VEC_DotProduct(&a->unk_18, b);
    int v3 = VEC_DotProduct(&a->unk_18, &a->unk_0C);
    int v4 = VEC_DotProduct(&a->unk_18, b);
    int d1 = v2 - v1;
    int d2 = v4 - v3;
    return (FX_MulFunc(d1, d2) > 0) ? 0 : 1;
}
