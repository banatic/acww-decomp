/* func_0203aa48 @ 0x0203aa48, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;
extern Mtx43 data_021fbe48;
extern void *data_021c67a4;
extern Mtx43 *func_0203ab20(void);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *dst);
extern int func_0203c53c(void *p);
extern int FX_Div(int a, int b);
extern void func_020eabc8(Vec3 *v, int s);

int func_0203aa48(int *outX, int *outY, Vec3 *v)
{
    Vec3 t;
    Mtx43 m;
    int k;
    if (data_021c67a4 != 0) {
        m = *func_0203ab20();
        data_021fbe48 = m;
        MTX_MultVec43(v, &data_021fbe48, &t);
        k = -FX_Div(0x60000, func_0203c53c(data_021c67a4));
        k = FX_Div(k, t.z);
        func_020eabc8(&t, k);
        *outX = t.x >> 12;
        *outY = -(t.y >> 12);
        return 1;
    }
    return 0;
}
