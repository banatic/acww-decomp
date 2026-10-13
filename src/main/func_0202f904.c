/* func_0202f904 @ 0x0202f904, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0202f904;

extern int func_0202fb28(UnkStruct_0202f904 *s, Vec3 *p);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_0202fb8c(UnkStruct_0202f904 *s, Vec3 *v);
extern int func_0202fa10(UnkStruct_0202f904 *s, Vec3 *v);
extern int func_0202fa9c(UnkStruct_0202f904 *s, Vec3 *v);

int func_0202f904(UnkStruct_0202f904 *s, Vec3 *out, Vec3 *p2, Vec3 *p3)
{
    Vec3 v;
    int t1;
    int diff;
    int ad;
    int k;
    int yy, zz;
    int t;

    t1 = func_0202fb28(s, p2);
    diff = t1 - func_0202fb28(s, p3);
    ad = diff < 0 ? -diff : diff;
    if (ad >= 4) {
        func_020eaca0(&v, p3, p2);
        k = FX_Div(t1, diff);
        zz = p2->z + FX_MulFunc(k, v.z);
        yy = p2->y + FX_MulFunc(k, v.y);
        out->x = p2->x + FX_MulFunc(k, v.x);
        out->y = yy;
        out->z = zz;
        t = s->unk_2C;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fb8c(s, out) != 0) {
                return 1;
            }
        }
        t = s->unk_28;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fa10(s, out) != 0) {
                return 1;
            }
        }
        t = s->unk_30;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fa9c(s, out) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
