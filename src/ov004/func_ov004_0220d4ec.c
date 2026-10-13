/* func_ov004_0220d4ec @ 0x0220d4ec, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern void *func_ov004_0220d7f0(void *p, unsigned int i);
extern int func_ov004_0220d94c(void *o);
extern Vec3 *func_ov004_0220d934(void *o);
extern void *func_ov004_0220d930(void *o);
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern void func_0204f818(int *a, int *b, Vec3 *out);
extern int func_020b65c4(void);
extern void func_02052118(int t, int a, int b, void *p, int k);
extern void func_ov004_0220d800(void *p);

void func_ov004_0220d4ec(void *p0, char *p1)
{
    unsigned int i;
    int zero;
    int a;
    int b;
    Vec3 v;
    Vec3 out;
    void *o;
    int px, py, pz;
    int t;

    zero = 0;
    for (i = 0; i < 4; i++) {
        o = func_ov004_0220d7f0(p0, i);
        if (func_ov004_0220d94c(o) != 0) {
            v.x = zero;
            v.y = zero;
            v.z = zero;
            data_021fbe48 = *(Mtx43 *) (p1 + 0x59c);
            pz = func_ov004_0220d934(o)->z;
            py = func_ov004_0220d934(o)->y;
            px = func_ov004_0220d934(o)->x;
            func_020e9868(&data_021fbe48, px, py, pz);
            MTX_MultVec43(&v, &data_021fbe48, &out);
            func_0204f818(&a, &b, &out);
            t = func_020b65c4();
            func_02052118(t, a, b, func_ov004_0220d930(o), 1);
        }
    }
    func_ov004_0220d800(p0);
}
