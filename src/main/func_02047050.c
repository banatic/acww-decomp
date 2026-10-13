/* func_02047050 @ 0x02047050, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

union Date {
    u16 h;
    u8 b;
    int pad_00;
};
typedef struct {
    int x;
    int y;
    int z;
} Vec;
struct UnkStruct_02047050 {
    char pad_00[0x5c];
    Vec v;
};

extern void func_0209def4(union Date *d);
extern struct UnkStruct_02047050 *func_020961a8(int n);
extern int func_0204e414(void);
extern void func_020470c0(void *a, int b, int c);
extern int func_020644cc(int);
extern u16 data_021c779c;

void func_02047050(void *a)
{
    union Date d;
    struct UnkStruct_02047050 *obj;
    Vec *q;
    u16 *gp;
    int v0;
    int v1;
    int x;
    int r;

    func_0209def4(&d);
    if (d.h == data_021c779c) {
        return;
    }
    if (d.b % 10 != 3) {
        return;
    }
    obj = func_020961a8(4);
    if (obj != 0) {
        x = func_0204e414();
        q = &obj->v;
        r = func_020644cc(4);
        v0 = obj->v.x >> 17;
        v1 = q->z >> 17;
        if (v1 != 4 || v0 != r + 1) {
            func_020470c0(a, x, r);
        }
    }
    gp = &data_021c779c;
    *gp = d.h;
}
