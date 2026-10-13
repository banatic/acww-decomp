/* func_ov003_0222ad80 @ 0x0222ad80, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int data_020c904c;
extern void func_ov003_022277fc(char *self, int k);
extern void func_ov003_0222be78(void *p, int d, int ang);
extern void func_02091278(void *h, Vec3 *v, int a, int b);

int func_ov003_0222ad80(char *self)
{
    Vec3 v;
    int n;
    int d;
    func_ov003_022277fc(self, 0x1c);
    n = *(int *) (self + 0x13c);
    d = 0x19 * (n + 0xa);
    if (d >= 0x180) {
        d = 0x180;
    }
    if (*(u8 *) (self + 0x7f)) {
        if (n >= 0x14) {
            func_ov003_022277fc(self, 3);
        } else if (n >= 0xf) {
            func_ov003_022277fc(self, 0x10);
        } else {
            func_ov003_022277fc(self, 0x20);
        }
    }
    func_ov003_0222be78(self + 0x120, d, *(short *) (self + 0x138));
    v.x = *(int *) (self + 0x120);
    v.y = *(int *) (self + 0x124);
    v.z = *(int *) (self + 0x128);
    v.y = data_020c904c;
    func_02091278(*(void **) (self + 0x204), &v, 0, 0);
    return 1;
}
