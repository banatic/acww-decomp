/* func_ov003_022189d8 @ 0x022189d8, 0x1f0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_022189d8;
typedef struct {
    int a, b;
} UnkStruct_022189d8_2;

struct UnkStruct_022189d8_3 {
    u8 pad_00[0x8e];
    short unk_8E;
    u8 pad_90[0x7d4 - 0x90];
    UnkStruct_022189d8 unk_7D4;
    u8 pad_7E0[0x820 - 0x7e0];
    u16 unk_820;
};

extern void func_0204f818(int *a, int *b, UnkStruct_022189d8 *c);
extern void func_020912d4(int a, UnkStruct_022189d8 *b, short *c, int d);
extern void func_02091230(int a, UnkStruct_022189d8 *b, int c, int d);
extern void VEC_Add(UnkStruct_022189d8 *a, UnkStruct_022189d8 *b, UnkStruct_022189d8 *dst);
extern void func_02044a14(short *a, UnkStruct_022189d8_2 *b, int c, int d);
extern void func_02045f08(UnkStruct_022189d8_2 *a, int b);
extern void func_0200f328(struct UnkStruct_022189d8_3 *self, int a);
extern void func_0200f268(struct UnkStruct_022189d8_3 *self, int a);

void func_ov003_022189d8(struct UnkStruct_022189d8_3 *self)
{
    short aa[2];
    int o1;
    int o2;
    UnkStruct_022189d8_2 p1;
    UnkStruct_022189d8_2 p2;
    UnkStruct_022189d8 v;
    UnkStruct_022189d8 t1;
    UnkStruct_022189d8 t2;
    UnkStruct_022189d8 t3;
    UnkStruct_022189d8 t4;
    UnkStruct_022189d8 *q;

    q = &self->unk_7D4;
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    o1 = 0;
    o2 = 0;
    func_0204f818(&o1, &o2, &v);
    aa[0] = self->unk_8E;

    switch (self->unk_820) {
        case 0x1f:
            func_020912d4(0x2e, &v, aa, 0);
            break;
        case 0x20:
            func_020912d4(0x2f, &v, aa, 0);
            break;
        case 0x21:
            t1.x = 0;
            t1.y = 0;
            t1.z = -0x800;
            VEC_Add(&v, &t1, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x22:
            t2.x = -0x800;
            t2.y = 0;
            t2.z = 0;
            VEC_Add(&v, &t2, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x23:
            t3.x = 0x800;
            t3.y = 0;
            t3.z = 0xc00;
            VEC_Add(&v, &t3, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        case 0x24:
            t4.x = -0x800;
            t4.y = 0;
            t4.z = 0;
            VEC_Add(&v, &t4, &v);
            func_020912d4(0x2d, &v, aa, 0);
            break;
        default: {
            u16 k = self->unk_820;
            if ((k >= 0x6e && k <= 0x73) || (k >= 0x74 && k <= 0x79) || (k >= 0x7a && k <= 0x7f) || (k >= 0x80 && k <= 0x87) ||
                k == 0x88 || k == 0x89 || (k >= 0x8a && k <= 0x8f) || (k >= 0x90 && k <= 0x95) || (k >= 0x96 && k <= 0x9b) ||
                (k >= 0x9c && k <= 0xa3) || k == 0xa5) {
                goto match;
            }
            if (k != 0xa4) {
                break;
            }
        match:
            func_02091230(0x54, &v, 0, 0);
            aa[1] = self->unk_820;
            p1.a = o1;
            p1.b = o2;
            func_02044a14(&aa[1], &p1, self->unk_8E, 2);
            func_0200f328(self, 0x7d8);
            break;
        }
    }

    switch (self->unk_820) {
        case 0x1f:
        case 0x20:
            func_0200f328(self, 0x7d8);
            break;
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
            func_0200f328(self, 0x7ec);
            break;
    }

    p2.a = o1;
    p2.b = o2;
    func_02045f08(&p2, 0);
    func_0200f268(self, 0x1c);
}
