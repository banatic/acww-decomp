/* func_ov003_02229ae0 @ 0x02229ae0, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The empty destructor keeps the eight bytes the ROM reserves for this local.
class Scope {
  public:
    Scope() {}
    ~Scope() {}
    int a, b;
};

extern "C" void *func_02096190(void *x);

extern "C" int func_ov003_02229ae0(char *self, void *x)
{
    Scope scope;
    int r = 0;
    unsigned int c1;
    unsigned int c2;
    int f;
    int *q;
    int v0, v1, v2;
    void *p = func_02096190(x);
    if (p == 0) {
        *(int *) (self + 0x40) = 4;
        return r;
    }
    f = *(int *) ((char *) p + 0xb0);
    if ((f & 4) != 0) {
        c1 = 1;
    } else {
        c1 = 0;
    }
    if (c1 != 0) {
        if ((f & 2) != 0) {
            c2 = 1;
        } else {
            c2 = 0;
        }
        if (c2 != 0) {
            q = (int *) ((char *) p + 0x5c);
            v0 = q[0];
            v1 = q[1];
            v2 = q[2];
            *(int *) (self + 0x54) = v0;
            *(int *) (self + 0x58) = v1;
            *(int *) (self + 0x5c) = v2;
            *(int *) (self + 0x6c) = v0;
            *(int *) (self + 0x70) = v1;
            *(int *) (self + 0x74) = v2;
            goto done;
        }
    }
    r = 1;
    *(u8 *) (self + 0x80) = 1;
    *(int *) (self + 0x40) = 3;
done:
    return r;
}
