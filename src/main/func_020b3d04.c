/* func_020b3d04 @ 0x020b3d04, 0x8a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00[3];
} Vec3;
typedef struct {
    u32 unk_00[9];
} Rec;

extern u32 func_020b3d90(void *);
extern u32 func_020b3f08(void *);
extern u32 func_020b3f2c(void *);
extern u32 func_020b3ed4(void *);

int func_020b3d04(void *base, Vec3 *out1, Vec3 *out2, Vec3 *out3, u32 idx)
{
    u32 cnt = func_020b3d90(base);
    out1->unk_00[0] = 0;
    out1->unk_00[1] = 0;
    out1->unk_00[2] = 0;
    out2->unk_00[0] = 0;
    out2->unk_00[1] = 0;
    out2->unk_00[2] = 0;
    out3->unk_00[0] = 0;
    out3->unk_00[1] = 0;
    out3->unk_00[2] = 0;
    if (idx < cnt) {
        u32 v0 = func_020b3f08(base);
        u32 v1 = func_020b3f2c(base);
        u32 v2 = func_020b3ed4(base);
        u32 off = 4 * (v0 + (v1 + v2) + 1) + 4;
        Rec *rec = (Rec *) ((char *) base + off);
        Rec *p = rec + idx;
        out1->unk_00[0] = rec[idx].unk_00[0];
        out1->unk_00[1] = p->unk_00[1];
        out1->unk_00[2] = p->unk_00[2];
        out2->unk_00[0] = p->unk_00[3];
        out2->unk_00[1] = p->unk_00[4];
        out2->unk_00[2] = p->unk_00[5];
        out3->unk_00[0] = p->unk_00[6];
        out3->unk_00[1] = p->unk_00[7];
        out3->unk_00[2] = p->unk_00[8];
        return 1;
    }
    return 0;
}
