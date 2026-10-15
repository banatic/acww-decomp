/* func_020bee9c @ 0x020bee9c, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Tile {
    u8 b[32];
};
struct UnkStruct_020bee9c {
    int unk_00;
    int n0;
    int s1;
    int n1;
};
struct Ref {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

extern int data_021f75b0;
extern struct UnkStruct_020bee9c data_020d26a0[];
extern struct Ref data_020d2bac[];

extern int func_020bef88(void *);
extern void GX_LoadOBJ(const void *src, u32 off, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 off, u32 size);

void func_020bee9c(int *a, u8 *b)
{
    unsigned int sub;
    struct UnkStruct_020bee9c *e;
    struct Ref *r;
    struct Tile *base;
    int t;
    int v;
    int i;
    const void *src1;
    int j;
    const void *src2;
    u32 size1;
    u32 off1;
    u32 size2;
    u32 off2;

    sub = (data_021f75b0 == 0) ? 1 : 0;
    func_020bef88(b);
    r = &data_020d2bac[*a];
    e = &data_020d26a0[r->unk_08];
    base = (struct Tile *) (b + 0x448);
    t = 0;
    v = 0x94;
    for (i = 0; i < 4; i++) {
        if (e->n0 != 0) {
            src1 = base + t + e->unk_00;
            size1 = e->n0 * 32;
            off1 = (v + e->unk_00) * 32;
            GX_LoadOBJ(src1, off1, size1);
            if (sub != 0) {
                GXS_LoadOBJ(src1, off1, size1);
            }
        }
        t += 0xc;
        v += 0x20;
    }
    for (j = 4; j < 8; j++) {
        if (e->n1 != 0) {
            src2 = base + t + e->s1;
            size2 = e->n1 * 32;
            off2 = (v + e->s1) * 32;
            GX_LoadOBJ(src2, off2, size2);
            if (sub != 0) {
                GXS_LoadOBJ(src2, off2, size2);
            }
        }
        t += 0xc;
        v += 0x20;
    }
}
