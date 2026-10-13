/* func_ov004_02233e18 @ 0x02233e18, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} Mtx;
typedef struct {
    int x, y, z;
} Vec3;

extern int func_0203f8d0(Vec3 *out, void *pos);
extern void func_020e96c8(void *m, int x, int y, int z);
extern void func_020e9774(void *m, int r);
extern void func_020e97a4(void *m, int a, int b, int c);
extern void func_020e9838(void *m, int x, int y, int z);
extern Mtx data_021fbe48;
extern void func_ov004_02233eb8(void *self, int field, Mtx byval);

#pragma opt_propagation off
int func_ov004_02233e18(char *self, int idx, void *pos, int *d, short s5, short s6, short s7)
{
    int field = *(int *) (self + 0x50 + idx * 4);
    Mtx m;
    Vec3 v;
    int r = func_0203f8d0(&v, pos);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, r);
    func_020e97a4(&data_021fbe48, s5, s6, s7);
    func_020e9838(&data_021fbe48, d[0], d[1], d[2]);
    m = data_021fbe48;
    func_ov004_02233eb8(self, field, m);
    return field;
}
