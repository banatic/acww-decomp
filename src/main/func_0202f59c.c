/* func_0202f59c @ 0x0202f59c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00[5];
    int a, b, c;
} UnkStruct_0202f59c;
typedef struct {
    int x, y;
} UnkStruct_0202f59c_2;

extern void func_0202f740(UnkStruct_0202f59c *o, int p, int q);
extern int FX_MulFunc(int x, int y);
extern int FX_Div(int x, int y);
extern void func_0202f6e8(UnkStruct_0202f59c *o);

int func_0202f59c(UnkStruct_0202f59c *s, UnkStruct_0202f59c_2 *out, int p, int q)
{
    UnkStruct_0202f59c b;
    int det;
    int t;
    int u;
    int c1, c2, c3;
    int c0;
    int m;

    func_0202f740(&b, p, q);
    det = FX_MulFunc(s->a, b.b) - FX_MulFunc(b.a, s->b);
    if ((det < 0 ? -det : det) < 4) {
        goto plain;
    }
    c1 = b.c;
    c0 = s->c;
    out->y = FX_Div(FX_MulFunc(b.a, c0) - FX_MulFunc(s->a, c1), det);
    t = s->a;
    if ((t < 0 ? -t : t) >= 4) {
        c2 = s->c;
        m = FX_MulFunc(s->b, out->y);
        out->x = FX_Div(-(m + c2), t);
        func_0202f6e8(&b);
        return 1;
    }
    u = b.a;
    if ((u < 0 ? -u : u) < 4) {
        goto plain;
    }
    c3 = b.c;
    m = FX_MulFunc(b.b, out->y);
    out->x = FX_Div(-(m + c3), u);
    func_0202f6e8(&b);
    return 1;
plain:
    func_0202f6e8(&b);
    return 0;
}
