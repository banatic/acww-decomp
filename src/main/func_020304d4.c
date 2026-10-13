/* func_020304d4 @ 0x020304d4, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
} ObjA;

typedef struct {
    int x, y, z;
} Vec3;

extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int func_020ea838(Vec3 *v);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020306a4(void *a, Vec3 *b);

static __inline void VEC_Set(Vec3 *p, int x, int y, int z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

int func_020304d4(ObjA *a, Vec3 *b, Vec3 *c)
{
    int sum = a->unk_04 + a->unk_10;
    Vec3 c2;
    Vec3 b2;
    Vec3 result;
    Vec3 out;
    int t, yy, zz;

    VEC_Set(&c2, c->x, c->y, c->z);
    if (c2.y > sum) {
        VEC_Set(&b2, b->x, b->y, b->z);
        if (b2.y < sum) {
            func_020eaca0(&result, &b2, &c2);
            if (func_020ea838(&result) != 0) {
                int ry = result.y;
                int ay = ry < 0 ? -ry : ry;
                if (ay >= 4) {
                    t = FX_Div(sum - c2.y, ry);
                    zz = c2.z + FX_MulFunc(result.z, t);
                    yy = c2.y + FX_MulFunc(result.y, t);
                    out.x = c2.x + FX_MulFunc(result.x, t);
                    out.y = yy;
                    out.z = zz;
                    if (func_020306a4(a, &out) != 0) {
                        b->x = out.x;
                        b->y = out.y;
                        b->z = out.z;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
