/* func_ov004_02234a98 @ 0x02234a98, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
class Actor {
  public:
    virtual void f0();
    virtual void update();
};
extern "C" {
extern unsigned char data_ov004_022593a0;
extern int FX_MulFunc(int, int);
extern void func_ov004_02235698(void *);
extern void func_ov004_0223405c(void *, void *, void *);
extern void func_ov004_022347b8(void *, void *);
extern void func_02054cdc(void *);
void func_ov004_02234a98(void *self, unsigned char **slot, void *arg)
{
    Vec *position = (Vec *) (*slot + 0x1a8);
    if (data_ov004_022593a0 == 0) {
        int x = FX_MulFunc(*(int *) (*slot + 0x14), 0x99a);
        int z = FX_MulFunc(*(int *) (*slot + 0x1c), 0x99a);
        if ((*slot)[0x40]) {
            if ((int) (*slot)[0x13] >= 0x38) {
                if ((x < 0 ? -x : x) > 143) {
                    x = (x > 0 ? 1 : -1) * 143;
                }
                if ((z < 0 ? -z : z) > 143) {
                    z = (z > 0 ? 1 : -1) * 143;
                }
            }
            position->x += x;
            position->z += z;
        }
    } else if (data_ov004_022593a0 == 1) {
        int x = FX_MulFunc(*(int *) (*slot + 0x14), 0x866);
        int z = FX_MulFunc(*(int *) (*slot + 0x1c), 0x866);
        if ((*slot)[0x40]) {
            position->x += x;
            position->z += z;
        }
    }
    ((Actor *) *slot)->update();
    func_ov004_02235698(*slot);
    func_ov004_0223405c(self, slot, arg);
    func_ov004_022347b8(self, slot);
    func_02054cdc(*slot + 0x64);
}
}
