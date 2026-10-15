/* func_ov003_0220f6dc @ 0x0220f6dc, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;
extern int func_020e8ed8(fx32, fx32);
extern void func_0204f818(fx32 *, fx32 *, Vec *);
extern void func_ov003_0220f744(void *, int, fx32, fx32, unsigned char, unsigned char);
extern void func_020109a0(void *, int b, int c, unsigned short d);
typedef struct {
    char pad_00[0x5c];
    Vec pos;
} UnkStruct_0220f6dc;
typedef struct {
    fx32 x;
    fx32 z;
    unsigned char c0, c1;
} UnkStruct_0220f6dc_2;

typedef volatile struct {
    fx32 x, y, z;
} DT;
void func_ov003_0220f6dc(UnkStruct_0220f6dc *self, void *data, int previous)
{
    fx32 a, b;
    DT d;
    Vec v;
    UnkStruct_0220f6dc_2 *p = (UnkStruct_0220f6dc_2 *) ((char *) data + 0xc);
    unsigned char c0 = p->c0;
    unsigned char c1 = p->c1;
    fx32 zz = p->z;
    fx32 yy = self->pos.y;
    fx32 xx = p->x;
    fx32 e0, e2;
    int r;
    v.x = xx;
    v.y = yy;
    v.z = zz;
    e0 = xx - self->pos.x;
    d.x = e0;
    e2 = zz - self->pos.z;
    d.z = e2;
    r = func_020e8ed8(e0, e2);
    a = 0;
    b = 0;
    func_0204f818(&a, &b, &v);
    func_ov003_0220f744((char *) self + 0x7d4, r, a, b, c0, c1);
    func_020109a0(self, 0x67, 3, 0);
}
