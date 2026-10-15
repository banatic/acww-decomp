/* func_ov003_022286ac @ 0x022286ac, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} Mtx;
extern Mtx data_021fbe48;
extern int func_0203f844(Vec3 *v, void *argument1);
extern void func_020e96c8(Mtx *m, int x, int y, int z);
extern void func_020e9774(Mtx *m, int t);
extern void func_020e9744(Mtx *m, int t);

void func_ov003_022286ac(void *a0, int a1, char *self, int a3)
{
    Vec3 v;
    int t;
    t = func_0203f844(&v, (void *) a1);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, t);
    func_020e9744(&data_021fbe48, a3);
    *(Mtx *) (self + 0x64) = data_021fbe48;
}
