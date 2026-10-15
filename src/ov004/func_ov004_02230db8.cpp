/* func_ov004_02230db8 @ 0x02230db8, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02230db8 {
    int a;
    ~UnkStruct_02230db8() {}
};
struct B {
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
};
extern "C" {
extern void *func_020682e0(int);
extern void func_020a8164(void *, void *);
extern void func_02068340(void *, void *);
}

extern "C" void func_ov004_02230db8(char *self, void *p1, u8 p2)
{
    UnkStruct_02230db8 t;
    void *h = func_020682e0(0);
    ((B *) (self + 0x290))->vfunc_08();
    func_020a8164(self + 0x290, p1);
    *(u8 *) (self + 0x2ae) = p2;
    {
        char *q = self;
        if (self != 0) {
            q = self + 0x290;
        }
        func_02068340(h, q);
    }
    *(int *) ((char *) h + 8) = 1;
}
