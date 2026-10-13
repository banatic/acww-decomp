/* func_02033678 @ 0x02033678, 0x200 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02033678 {
    int x, z;
} UnkStruct_02033678;
typedef struct UnkStruct_02033678_2 {
    int x, y, z;
} UnkStruct_02033678_2;
typedef struct VV3 {
    int x, y, z;
} VV3;
typedef struct UnkStruct_02033678_3 {
    char unk_00[0x14];
    int unk_14;
    int unk_18;
    char unk_1C[4];
    u8 unk_20;
    char unk_21[3];
    struct Handler *unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02033678_3;
struct Handler {
    virtual void contact(UnkStruct_02033678_3 *, void *, int);
};
typedef struct UnkStruct_02033678_4 {
    UnkStruct_02033678_3 ents[24];
    int cnt;
} UnkStruct_02033678_4;

extern "C" UnkStruct_02033678 data_021c30b8;

extern "C" void func_0202f8fc(UnkStruct_02033678 *, int, int);
extern "C" s64 func_0202f838(UnkStruct_02033678 *, UnkStruct_02033678 *);
extern "C" int FX_MulFunc(int, int);
extern "C" int func_0202f288(UnkStruct_02033678_3 *, UnkStruct_02033678 *, UnkStruct_02033678 *, int);
extern "C" int func_0202f3e4(UnkStruct_02033678_3 *, UnkStruct_02033678 *, UnkStruct_02033678 *, int);
extern "C" int func_0202f2f4(UnkStruct_02033678_3 *, UnkStruct_02033678 *, UnkStruct_02033678 *, int);
extern "C" short func_020e8ed8(int, int);
extern "C" int func_02032cac(char *, short, int, int);

extern "C" int func_02033678(UnkStruct_02033678_4 *self, UnkStruct_02033678_2 *m, UnkStruct_02033678_2 *n, int p3, char *p4,
                             void *p5)
{
    int ret;
    int k1, k2, k3;
    s64 ll;
    UnkStruct_02033678 v24;
    UnkStruct_02033678 v2c;
    UnkStruct_02033678 v34;
    struct {
        VV3 p;
        VV3 q;
    } volatile w1, w2, w3;
    UnkStruct_02033678_3 *e;

    ret = 0;
    func_0202f8fc(&v24, m->x, m->z);
    func_0202f8fc(&v2c, n->x, n->z);
    func_0202f8fc(&v34, m->x - n->x, m->z - n->z);
    ll = func_0202f838(&v34, &data_021c30b8);
    if (ll >= (s64) FX_MulFunc(p3, p3)) {
        for (e = self->ents; e < &self->ents[self->cnt]; e++) {
            w1.p.x = m->x;
            w1.p.y = m->y;
            w1.p.z = m->z;
            if (e->unk_2C - 0x700 > m->y) {
                if (func_0202f288(e, &v24, &v2c, p3) != 0) {
                    int height = *(volatile int *) &m->y;
                    w1.q.x = v24.x;
                    w1.q.y = height;
                    w1.q.z = v24.z;
                    k1 = e->unk_28;
                    if (k1 != 3) {
                        func_02032cac(p4 + 0xc, func_020e8ed8(e->unk_14, e->unk_18), k1, e->unk_20);
                        if (e->unk_24 != 0) {
                            e->unk_24->contact(e, p5, p3);
                        }
                    }
                    ret = 1;
                }
            }
        }
    }
    for (e = self->ents; e < &self->ents[self->cnt]; e++) {
        w2.p.x = m->x;
        w2.p.y = m->y;
        w2.p.z = m->z;
        if (e->unk_2C - 0x700 > m->y) {
            if (func_0202f3e4(e, &v24, &v2c, p3) != 0) {
                int height = *(volatile int *) &m->y;
                w2.q.x = v24.x;
                w2.q.y = height;
                w2.q.z = v24.z;
                k2 = e->unk_28;
                if (k2 != 3) {
                    func_02032cac(p4 + 0xc, func_020e8ed8(e->unk_14, e->unk_18), k2, e->unk_20);
                    if (e->unk_24 != 0) {
                        e->unk_24->contact(e, p5, p3);
                    }
                }
                ret = 1;
            }
        }
    }
    for (e = self->ents; e < &self->ents[self->cnt]; e++) {
        w3.p.x = m->x;
        w3.p.y = m->y;
        w3.p.z = m->z;
        if (e->unk_2C - 0x700 > m->y) {
            if (func_0202f2f4(e, &v24, &v2c, p3) != 0) {
                int height = *(volatile int *) &m->y;
                w3.q.x = v24.x;
                w3.q.y = height;
                w3.q.z = v24.z;
                k3 = e->unk_28;
                if (k3 != 3) {
                    func_02032cac(p4 + 0xc, func_020e8ed8(e->unk_14, e->unk_18), k3, e->unk_20);
                    if (e->unk_24 != 0) {
                        e->unk_24->contact(e, p5, p3);
                    }
                }
                ret = 1;
            }
        }
    }
    m->x = v24.x;
    m->z = v24.z;
    return ret;
}
