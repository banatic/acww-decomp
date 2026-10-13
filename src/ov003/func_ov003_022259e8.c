/* func_ov003_022259e8 @ 0x022259e8, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} UnkStruct_022259e8;

extern UnkStruct_022259e8 data_021fbe48;
extern int func_020466e0(int a, int b);
extern int func_0203f8d0(Vec3 *v, void *a);
extern void func_020e96c8(UnkStruct_022259e8 *m, int x, int y, int z);
extern void func_020e9774(UnkStruct_022259e8 *m, int t);
extern void func_ov003_022251a4(char *a0, void *r, UnkStruct_022259e8 m);

void func_ov003_022259e8(char *a0, void *a1, int a2, int a3)
{
    void *p;
    Vec3 v;
    int k;
    int t;
    p = 0;
    k = func_020466e0(a2, a3);
    if (k != -1) {
        k = (k + (*(int *) (a0 + 0x6a6c) + k * 0xf) / 0x14) % 3;
        p = a0 + 0x1014 + k * 0x9c;
    }
    t = func_0203f8d0(&v, a1);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, t);
    func_ov003_022251a4(a0, p, data_021fbe48);
}
