/* func_ov003_02214200 @ 0x02214200, 0x184 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int m[4][3];
} Mtx43;

typedef struct UnkStruct_02214200 UnkStruct_02214200;
struct UnkStruct_02214200 {
    char pad_00[0x5c];
    Vec unk_5C;
    char pad_68[0x8e - 0x68];
    u16 unk_8E;
    char pad_90[0x2d8 - 0x90];
    unsigned int unk_2D8;
    char pad_2DC[0x608 - 0x2dc];
    Mtx43 unk_608;
};

extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern int func_0200f328(UnkStruct_02214200 *self, int id);
extern int func_0203f7d0(Vec *a, Vec *b);

void func_ov003_02214200(UnkStruct_02214200 *self, Vec *p1, Vec *p2, Vec *p3)
{
    Vec *v;
    int t, s, c;
    unsigned int kind;
    Mtx43 m;
    Vec w;

    v = &self->unk_5C;
    p2->x = v->x;
    p2->y = v->y;
    p2->z = v->z;

    t = (self->unk_8E >> 4) << 1;
    s = FX_SinCosTable_[t];
    c = FX_SinCosTable_[t + 1];

    kind = (self->unk_2D8 << 4) >> 16;
    switch (kind) {
        case 3:
            func_0200f328(self, 0x845);
            p1->y = p1->y + 0x1dd3;
            p2->x = p2->x + FX_MulFunc(s, 0x1e66);
            p2->y = p2->y + 0x24cd;
            p2->z = p2->z + FX_MulFunc(c, 0x1e66);
            break;
        case 4:
            p1->x = v->x;
            p1->y = v->y;
            p1->z = v->z;
            p1->x = p1->x + FX_MulFunc(s, 0x1e66);
            p1->y = p1->y + 0x24cd;
            p1->z = p1->z + FX_MulFunc(c, 0x1e66);
            p2->x = p2->x + FX_MulFunc(s, 0x2a66);
            p2->z = p2->z + FX_MulFunc(c, 0x2a66);
            break;
        case 5:
            p1->x = v->x;
            p1->y = v->y;
            p1->z = v->z;
            p1->x = p1->x + FX_MulFunc(s, 0x2a66);
            p1->z = p1->z + FX_MulFunc(c, 0x2a66);
            p2->x = p2->x + FX_MulFunc(s, 0x2800);
            p2->y = p2->y - 0x666;
            p2->z = p2->z + FX_MulFunc(c, 0x2800);
            break;
    }
    m = self->unk_608;
    w.x = m.m[3][0];
    w.y = m.m[3][1];
    w.z = m.m[3][2];
    func_0203f7d0(&w, &w);
    p3->x = w.x;
    p3->y = w.y;
    p3->z = w.z;
}
