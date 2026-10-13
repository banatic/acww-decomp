/* func_02056c20 @ 0x02056c20, 0xec bytes, ARM, module main
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    VecFx32 unk_00, v1;
} Pair;
typedef struct {
    VecFx32 a, b, c;
} Mtx;

extern void func_02056d0c(VecFx32 *v);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);

void func_02056c20(const Pair *p0, const Pair *p1, Mtx *dest, fx32 t)
{
    fx32 w = 0x1000 - t;

    dest->a.x = (fx32) (((s64) t * p0->unk_00.x + (s64) w * p1->unk_00.x) >> 12);
    dest->a.y = (fx32) (((s64) t * p0->unk_00.y + (s64) w * p1->unk_00.y) >> 12);
    dest->a.z = (fx32) (((s64) t * p0->unk_00.z + (s64) w * p1->unk_00.z) >> 12);
    dest->b.x = (fx32) (((s64) t * p0->v1.x + (s64) w * p1->v1.x) >> 12);
    dest->b.y = (fx32) (((s64) t * p0->v1.y + (s64) w * p1->v1.y) >> 12);
    dest->b.z = (fx32) (((s64) t * p0->v1.z + (s64) w * p1->v1.z) >> 12);

    func_02056d0c(&dest->a);
    func_02056d0c(&dest->b);
    VEC_CrossProduct(&dest->a, &dest->b, &dest->c);
    VEC_CrossProduct(&dest->c, &dest->a, &dest->b);
}
