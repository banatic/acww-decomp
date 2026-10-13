/* func_020b8550 @ 0x020b8550, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;
extern int FX_MulFunc(int a, int b);
extern void func_02030678(void *w, Vec *v, int a, int b);
extern int func_0203006c(void *w, Vec *a, Vec *b);
extern void func_02030668(void *w);
extern short data_0213a59c[];
extern short data_0213c59c[];
int func_020b8550(Vec *out, Vec *p, Vec *q, int a4, int a5)
{
    Vec v0;
    Vec a;
    int val;
    Vec b;
    unsigned char w[0x20];
    int sn;
    int cs;
    int x;
    int y;
    int z;
    v0.x = 0;
    v0.y = 0;
    v0.z = 0;
    func_02030678(w, &v0, a4, a5);
    z = p->z;
    y = p->y;
    x = p->x;
    a.x = x;
    a.y = y;
    a.z = z;
    z = q->z;
    y = q->y;
    x = q->x;
    b.x = x;
    b.y = y;
    b.z = z;
    sn = data_0213a59c[0];
    cs = data_0213a59c[1];
    x = a.x;
    y = (val = a.y);
    a.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
    a.y = FX_MulFunc(sn, x) + FX_MulFunc(cs, y);
    y = b.y;
    x = b.x;
    b.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
    b.y = FX_MulFunc(sn, x) + FX_MulFunc(((((((cs)))))), y);
    if (func_0203006c(w, &b, &a) != 0) {
        y = b.y;
        sn = data_0213c59c[0];
        x = b.x;
        cs = data_0213c59c[1];
        b.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
        b.y = FX_MulFunc(sn, x) + FX_MulFunc(cs, y);
        if (1) {
            out->x = b.x;
            out->y = b.y;
        }
        out->z = b.z;
        func_02030668(w);
        return 1;
    }
    func_02030668(w);
    return 0;
}
