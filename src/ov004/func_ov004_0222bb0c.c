/* func_ov004_0222bb0c @ 0x0222bb0c, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int, int);
extern void func_ov004_0222bbd4(void *, Vec3 *, int);
extern int func_02073908(void *, int);
extern void func_02051e20(Vec3 *);
extern void *data_020ccf94;

void func_ov004_0222bb0c(char *self, char *e)
{
    char *s;
    int cd[2];
    int t;
    Vec3 a;
    Vec3 b;
    int f;
    int ang;
    int m;
    int r;
    int j;
    f = *(unsigned char *) (e + 0xc);
    ang = *(short *) (self + 0x8e);
    s = self + 0x7d4;
    {
        char *o = self + 0x5c;
        a.x = *(int *) (self + 0x5c);
        a.y = *(int *) (o + 4);
        a.z = *(int *) (o + 8);
    }
    m = 0x2000;
    {
        int neg = 0;
        neg = ~neg;
        if (f == 0) {
            m = neg * m;
        }
    }
    j = ((int) (unsigned short) ang >> 4) * 2;
    cd[0] = FX_SinCosTable_[j];
    cd[1] = FX_SinCosTable_[j + 1];
    r = FX_MulFunc(cd[1], 0x1000);
    r = r - FX_MulFunc(cd[0], m);
    t = FX_MulFunc(cd[0], 0x1000);
    t = t + FX_MulFunc(cd[1], m);
    {
        char *o = self + 0x5c;
        a.x = *(int *) o + t;
        a.z = *(int *) (o + 8) + r;
    }
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    func_ov004_0222bbd4(s, &b, f);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02051e20(&a);
    }
}
