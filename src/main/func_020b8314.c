/* func_020b8314 @ 0x020b8314, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx;
typedef struct {
    Vec3 a, b, c;
} UnkStruct_020b8314;
typedef struct {
    Vec3 a;
    Vec3 b;
} Pair;

extern int data_021c67a4;
extern int data_020ca0e8;
extern Mtx data_0213fee4;
extern int func_0203c53c(int v);
extern int FX_Div(int a, int b);
extern int func_020ea838(Vec3 *v);
extern void func_020eabc8(Vec3 *v, int s);
extern void func_01ffd070(Vec3 *dst, Vec3 *a, Vec3 *b);
extern void MTX_Inverse43(Mtx *a, Mtx *b);
extern void MTX_MultVec43(Vec3 *v, Mtx *m, Vec3 *dst);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);

void func_020b8314(UnkStruct_020b8314 *out, int px, int pz)
{
    Vec3 zero;
    Pair pr;
    Vec3 v2;
    Vec3 ra;
    Vec3 rb;
    Mtx m;
    Vec3 d;
    int s;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    s = -FX_Div(0x60000, func_0203c53c(data_021c67a4));
    pr.a.x = (px << 12) - 0x80000;
    pr.a.y = -((pz << 12) - 0x60000);
    pr.a.z = s;
    pr.b.x = (px << 12) - 0x80000;
    pr.b.y = -((pz << 12) - 0x60000);
    pr.b.z = s;
    func_020ea838(&pr.b);
    func_020eabc8(&pr.b, data_020ca0e8);
    func_01ffd070(&v2, &zero, &pr.b);
    m = data_0213fee4;
    MTX_Inverse43(&m, &m);
    MTX_MultVec43(&zero, &m, &ra);
    MTX_MultVec43(&v2, &m, &rb);
    out->a.x = ra.x;
    out->a.y = ra.y;
    out->a.z = ra.z;
    out->b.x = rb.x;
    out->b.y = rb.y;
    out->b.z = rb.z;
    func_020eaca0(&d, &out->b, &out->a);
    out->c.x = d.x;
    out->c.y = d.y;
    out->c.z = d.z;
    func_020ea838(&out->c);
}
