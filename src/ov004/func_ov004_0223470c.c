/* func_ov004_0223470c @ 0x0223470c, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223470c {
    int x, y, z;
};

struct UnkStruct_0223470c_2 {
    u8 pad_00[0x15c];
    int unk_15C;
    int unk_160;
};

struct UnkStruct_0223470c_3 {
    u8 pad_00[0x258];
    struct UnkStruct_0223470c unk_258;
};

struct UnkStruct_0223470c_4 {
    struct UnkStruct_0223470c_2 *p;
};

struct UnkStruct_0223470c_5 {
    u8 pad_00[4];
};

extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern struct UnkStruct_0223470c_4 data_ov004_022594d4[];
extern struct UnkStruct_0223470c_3 *data_ov004_022593b4;

extern void func_ov004_022347b8(struct UnkStruct_0223470c_5 *self, struct UnkStruct_0223470c_4 *e);
extern void func_0205510c(void *p, struct UnkStruct_0223470c *v);

int func_ov004_0223470c(struct UnkStruct_0223470c_5 *self)
{
    int i;
    struct UnkStruct_0223470c_4 *e;
    struct UnkStruct_0223470c_2 *o;
    struct UnkStruct_0223470c_3 *q;
    struct UnkStruct_0223470c *w;
    struct UnkStruct_0223470c v;

    i = data_ov004_022593a4;
    e = &data_ov004_022594d4[i];
    while (i < data_ov004_02255c30) {
        o = e->p;
        if (o != 0 && o->unk_160 == 2) {
            switch (o->unk_15C) {
                case 0xb:
                    v.x = 0x1000;
                    v.y = 0x1000;
                    v.z = 0x1000;
                    func_ov004_022347b8(self, e);
                    break;
                case 0x24:
                    q = data_ov004_022593b4;
                    if (q != 0) {
                        w = &q->unk_258;
                        v.x = q->unk_258.x;
                        v.y = w->y;
                        v.z = w->z;
                    } else {
                        v.x = 0x1000;
                        v.y = 0x1000;
                        v.z = 0x1000;
                    }
                    break;
                default:
                    v.x = 0x1000;
                    v.y = 0x1000;
                    v.z = 0x1000;
                    break;
            }
            func_0205510c((u8 *) e->p + 0x64, &v);
        }
        e++;
        i++;
    }
    return 1;
}
