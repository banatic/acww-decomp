/* func_ov003_0222e0ec @ 0x0222e0ec, 0x178 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int r[9];
    Vec3 t;
} Mtx43;

extern Mtx43 data_021fbe48;

extern int func_0203f8d0(Vec3 *out, Vec3 *p);
extern void func_020e9774(Mtx43 *m, int ang);
extern void func_020e96c8(Mtx43 *m, int x, int y, int z);
extern void func_020e9744(Mtx43 *m, int a);
extern void func_020e9714(Mtx43 *m, int a);
extern int FX_MulFunc(int a, int b);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern void func_0203f7d0(Vec3 *a, Vec3 *b);
extern int func_020912d4(int id, Vec3 *p, int a, short *h);
extern void func_02091278(int id, Vec3 *p, int a, short *h);

void func_ov003_0222e0ec(int unused, char *self, int mode)
{
    short h[2];
    Vec3 v;
    Mtx43 m;
    Vec3 t;
    Mtx43 m2;
    Vec3 vin;
    Vec3 vout;
    int ang;
    char *p50;

    p50 = self + 0x50;
    ang = func_0203f8d0(&v, (Vec3 *) (self + 0x204));
    if (mode != 0) {
        data_021fbe48 = *(Mtx43 *) (self + 0x180);
        func_020e9774(&data_021fbe48, *(short *) (self + 0x238));
    } else {
        func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
        func_020e9774(&data_021fbe48, (short) (ang + *(short *) (self + 0x238)));
    }
    if (*(short *) (self + 0x23a) != 0) {
        func_020e9744(&data_021fbe48, *(short *) (self + 0x23a));
    }
    if (*(short *) (self + 0x23c) != 0) {
        func_020e9714(&data_021fbe48, *(short *) (self + 0x23c));
    }
    *(Mtx43 *) (p50 + 0x64) = data_021fbe48;
    if (mode != 0) {
        if (*(signed char *) (self + 0x24d) == 0x39) {
            int *q;
            m = data_021fbe48;
            t.x = m.t.x;
            t.y = m.t.y;
            t.z = m.t.z;
            q = (int *) (self + 0x22c);
            m.t.z = 0;
            m.t.y = 0;
            m.t.x = 0;
            m2 = m;
            vin.y = 0;
            vin.x = 0;
            vin.z = FX_MulFunc(*(int *) (self + 0x210), -0x333);
            MTX_MultVec43(&vin, &m2, &vout);
            t.x = t.x + vout.x;
            t.y = t.y + vout.y;
            t.z = t.z + vout.z;
            func_0203f7d0(&t, &t);
            if (*(int *) (self + 0x21c) == 0) {
                h[0] = (short) *(int *) (self + 0x210);
                *q = func_020912d4(0x3a, &t, 0, h);
                *(int *) (self + 0x21c) = 1;
            } else {
                h[1] = (short) *(int *) (self + 0x210);
                if (*q != -1) {
                    func_02091278(*q, &t, 0, &h[1]);
                }
            }
        }
    }
}
