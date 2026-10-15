/* func_ov004_0220d3c8 @ 0x0220d3c8, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *o, int a, int b, int c);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *y, void *x);
extern void func_0204f794(Vec3 *v, int a, int b);
extern void func_ov004_0220fc98(void *x, int a, int b);
extern int MTX_Inverse43(Mtx43 *a, Mtx43 *b);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);

int func_ov004_0220d3c8(int *p0, int *p1, short *p2, int p3, int p4, short p5)
{
    Vec3 v;
    Vec3 out;
    void *x;
    int z;

    x = func_ov004_0223cc10(func_ov004_0223cd50(), p3, p4, 0);
    z = func_ov004_0223cd78(func_ov004_0223ce84(), x);
    if (x != 0 && z != -1) {
        func_0204f794(&v, p3, p4);
        v.y = *(int *) ((char *) x + 0x790);
        func_ov004_0220fc98(x, 0, 0);
        MTX_Inverse43(&data_021fbe48, &data_021fbe48);
        MTX_MultVec43(&v, &data_021fbe48, &out);
        *p0 = z;
        p1[0] = out.x;
        p1[1] = out.y;
        p1[2] = out.z;
        *p2 = (short) (p5 - *(short *) ((char *) x + 0x8e));
        return 1;
    }
    return 0;
}
