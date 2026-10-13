/* func_02032fc0 @ 0x02032fc0, 0xfa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8fc(void *dst, int x, int y);
extern void func_0202f898(void *dst, void *src1, void *src2);
extern void func_0202f7f4(void *v);
extern void func_0202f7a0(void *dst, void *a, void *b);
extern int func_02033614(void *a, void *b, void *c, void *d, int e, int f, int g, int h);
extern int FX_MulFunc(int x, int y);

typedef struct {
    int x;
    int y;
} Vec2;

typedef struct UnkStruct_02032fc0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[12];
    short unk_20;
    short unk_22;
} UnkStruct_02032fc0;

int func_02032fc0(UnkStruct_02032fc0 *a, void *b, UnkStruct_02032fc0 *c)
{
    int dx, dy;
    Vec2 v1, v2, v3, v4, v5, v6, v7;
    int ty, tx;
    int ty2, tx2;
    int min;

    dx = c->unk_20 - a->unk_20;
    dy = c->unk_22 - a->unk_22;

    if ((dx == 0 && dy == 1) || (dx == 1 && (unsigned) (dy + 1) <= 2)) {
        func_0202f8fc(&v1, a->unk_00, a->unk_08);
        func_0202f8fc(&v2, c->unk_00, c->unk_08);
        func_0202f898(&v3, &v2, &v1);
        func_0202f7f4(&v3);

        ty = v1.y - FX_MulFunc(v3.y, a->unk_0C);
        tx = v1.x - FX_MulFunc(v3.x, a->unk_0C);
        func_0202f8fc(&v4, tx, ty);

        ty2 = v2.y + FX_MulFunc(v3.y, c->unk_0C);
        tx2 = v2.x + FX_MulFunc(v3.x, c->unk_0C);
        func_0202f8fc(&v5, tx2, ty2);

        func_0202f8fc(&v6, 0, 0);
        func_0202f7a0(&v6, &v1, &v2);
        func_0202f8fc(&v7, -v6.x, -v6.y);

        min = c->unk_10;
        if (c->unk_10 > a->unk_10) {
            min = a->unk_10;
        }

        func_02033614(b, &v4, &v5, &v6, min, 3, 0, 0);
        func_02033614(b, &v4, &v5, &v7, min, 3, 0, 0);

        return 1;
    }

    return 0;
}