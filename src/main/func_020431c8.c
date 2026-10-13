/* func_020431c8 @ 0x020431c8, 0x1a0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020431c8;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    u16 unk_10;
    u16 unk_12;
    int unk_14;
    int unk_18;
    u8 unk_1C;
    u8 pad_1D[7];
} Entry;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_020431c8 vec;
} UnkStruct_020431c8_2;

extern UnkStruct_020431c8_2 *func_020961a8(int k);
extern int func_ov003_02221118(int a, int w, Pt *p);
extern int func_ov003_02221304(int a, int w, Pt *p, UnkStruct_020431c8 *v);
extern int func_ov004_022335b8(int a, int w, Pt *p, UnkStruct_020431c8 *v, int z);

extern void *data_021c80bc;
extern Entry data_021c7c48[];
extern u8 data_020e54a8;

int func_020431c8(int idx)
{
    UnkStruct_020431c8 *q;
    unsigned int s4;
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int s8;
    unsigned int sc;
    unsigned int s10;
    unsigned int s14;
    volatile u16 w;
    Pt pa;
    Pt pb;
    Pt pc_;
    UnkStruct_020431c8 va;
    UnkStruct_020431c8 vb;
    void *ctx;
    int ret;
    Entry *e;
    int k;
    UnkStruct_020431c8_2 *o;
    unsigned int f;
    unsigned int v;
    unsigned int v2;
    int bb;

    ctx = data_021c80bc;
    ret = 0;
    e = &data_021c7c48[idx];
    if (ctx == 0) {
        return ret;
    }
    switch (e->unk_08) {
        case 2:
            o = func_020961a8(4);
            if (ctx == 0) {
                goto end;
            }
            if (o == 0) {
                goto end;
            }
            q = &o->vec;
            if (data_020e54a8 == 0) {
                f = 1;
            } else {
                f = 0;
            }
            if (f == 0) {
                goto third;
            }
            w = 0xfff1;
            w = e->unk_10;
            s10 = sc = s8 = rc = rb = ra = s4 = 1;
            s14 = 0;
            v = w;
            v2 = w;
            if (v2 <= 5) {
                s14 = 1;
            }
            if (s14 == 0) {
                if (!(v >= 6 && v <= 0xb)) {
                    s10 = 0;
                }
            }
            if (s10 == 0) {
                if (!(v >= 0xc && v <= 0x11)) {
                    sc = 0;
                }
            }
            if (sc == 0) {
                if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
                    s8 = 0;
                }
            }
            if (s8 == 0) {
                if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
                      (v >= 0x9c && v <= 0xa3) || v == 0xa5)) {
                    rc = 0;
                }
            }
            if (rc == 0) {
                if (v != 0x1a) {
                    rb = 0;
                }
            }
            if (rb == 0) {
                if (v != 0xa4) {
                    ra = 0;
                }
            }
            if (ra == 0) {
                if (v != 0x1d) {
                    s4 = 0;
                }
            }
            if (s4 != 0 || (v >= 0xa7 && v <= 0xc6) || v == 0x1e) {
                pa.x = e->unk_14;
                pa.y = e->unk_18;
                if (func_ov003_02221118(e->unk_00, e->unk_10, &pa) == 0) {
                    goto end;
                }
                ret = 1;
                goto end;
            }
            va.a = q->a;
            va.b = q->b;
            va.c = q->c;
            pb.x = e->unk_14;
            pb.y = e->unk_18;
            if (func_ov003_02221304(e->unk_00, e->unk_10, &pb, &va) == 0) {
                goto end;
            }
            ret = 1;
            goto end;
        third:
            vb.a = q->a;
            vb.b = q->b;
            vb.c = q->c;
            bb = e->unk_1C;
            pc_.x = e->unk_14;
            pc_.y = e->unk_18;
            if (func_ov004_022335b8(e->unk_00, e->unk_10, &pc_, &vb, bb) == 0) {
                goto end;
            }
            ret = 1;
            goto end;
        case 3:
            ret = 2;
            break;
    }
end:
    return ret;
}
