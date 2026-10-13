/* func_ov004_02225de0 @ 0x02225de0, 0x118 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_02225de0;

extern int func_020ea9c8(UnkStruct_02225de0 *d);
extern void func_020114b0(void *dst, int a, int b, int c, int d);
extern int func_020ea990(void *a, void *b);
extern int func_02011398(int a, int b);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int dx, int dz);
extern void func_020113e0(short *a, int b);
extern void func_020110a0(void *self, short *b);
extern int FX_MulFunc(int a, int b);
extern void func_0201107c(void *self, int *a);

extern short FX_SinCosTable_[];

void func_ov004_02225de0(char *self, UnkStruct_02225de0 *p1, int *out, int *p3)
{
    int r;
    int ang;
    UnkStruct_02225de0 d;
    int idx;
    short prevAngle;
    UnkStruct_02225de0 saved;
    short diffS;

    {
        int *p = (int *) (self + 0x5c);
        saved.x = p[0];
        saved.y = p[1];
        saved.z = p[2];
    }

    d.x = p1->x - *(int *) (self + 0x5c);
    d.z = p1->z - *(int *) (self + 0x64);

    if (func_020ea9c8(&d) < 0x1000) {
        if (*out <= *p3) {
            func_020114b0(self + 0x5c, p1->x, 0x800, *p3, 0x31);
            func_020114b0(self + 0x64, p1->z, 0x800, *p3, 0x31);
            if (p1->x == *(int *) (self + 0x5c) && p1->z == *(int *) (self + 0x64)) {
                *out = 0;
            } else {
                *out = func_020ea990(self + 0x5c, &saved);
                {
                    int *p = (int *) (self + 0x5c);
                    p[0] = saved.x;
                    p[1] = saved.y;
                    p[2] = saved.z;
                }
            }
        } else {
            *out = func_02011398(*out, *p3);
        }
    } else {
        *out = func_020113b0(*out, *p3);
    }

    ang = func_020e8ed8(d.x, d.z);
    prevAngle = *(short *) (self + 0x8e);
    if (*out != 0) {
        func_020113e0(&prevAngle, ang);
        func_020110a0(self, &prevAngle);
    }
    diffS = prevAngle - ang;
    idx = (unsigned short) diffS >> 4;
    {
        int t = FX_MulFunc(*out, FX_SinCosTable_[idx * 2 + 1]);
        r = (t < 0) ? -t : t;
    }
    func_0201107c(self, &r);
}
