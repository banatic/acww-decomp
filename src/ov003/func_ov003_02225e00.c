/* func_ov003_02225e00 @ 0x02225e00, 0x98 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} UnkStruct_02225e00;

extern UnkStruct_02225e00 data_021fbe48;
extern int func_0203f8d0(Vec3 *v, void *a);
extern void func_020e96c8(UnkStruct_02225e00 *m, int x, int y, int z);
extern void func_020e9774(UnkStruct_02225e00 *m, int t);
extern void func_020e97a4(UnkStruct_02225e00 *m, int a, int b, int c);
extern void func_020e9838(UnkStruct_02225e00 *m, int x, int y, int z);
extern void func_0210744c(void *h, int a);
extern void func_ov003_022251a4(char *a0, void *r, UnkStruct_02225e00 m);

void *func_ov003_02225e00(char *a0, int i, void *a2, int a3, Vec3 *p, short s1, short s2, short s3)
{
    Vec3 v;
    void *r;
    int t;
    r = *(void **) (a0 + i * 4 + 0x50);
    t = func_0203f8d0(&v, a2);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, t);
    func_020e97a4(&data_021fbe48, s1, s2, s3);
    func_020e9838(&data_021fbe48, p->x, p->y, p->z);
    func_0210744c(*(void **) ((char *) r + 0x5c), a3);
    func_ov003_022251a4(a0, r, data_021fbe48);
    return r;
}
