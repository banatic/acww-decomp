/* func_ov004_02227bf4 @ 0x02227bf4, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void func_02032c64(void *);
extern void func_02032c50(void *);
extern int func_020082a0(void *, int);
extern void func_02031288(void *, void *, void *, int, int, void *, int);
extern int func_020310c8(int);
extern int func_020ea990(Vec3 *, void *);
extern int FX_Div(int);

void func_ov004_02227bf4(char *self)
{
    char buf[0x30];
    Vec3 v;
    char *o;
    short a;
    void *p;
    int st;
    o = self + 0x5c;
    func_02032c64(buf);
    a = *(short *) (self + 0x8e);
    if (func_020082a0(self, *(int *) (self + 0x7f0)) == 0) {
        p = buf;
    } else {
        p = self + 0x7a4;
    }
    func_02031288(p, o, self + 0x68, a, 0xfd7, self, 0xf);
    func_02032c50(buf);
    *(int *) (o + 4) = func_020310c8(0);
    {
        char *b = self + 0x7d4;
        st = *(int *) b;
        if ((unsigned) (st - 1) <= 1) {
            int z = *(int *) (b + 0xc);
            int y = *(int *) (o + 4);
            int x = *(int *) (b + 8);
            v.x = x;
            v.y = y;
            v.z = z;
            if (func_020ea990(&v, o) < 0x1000) {
                int t = 6 * FX_Div(0x1000 - func_020ea990(&v, o));
                if (st == 1) {
                    *(int *) (o + 4) = *(int *) (o + 4) + (t >> 5);
                } else {
                    *(int *) (o + 4) = *(int *) (o + 4) - (t >> 5);
                }
            }
        }
    }
}
