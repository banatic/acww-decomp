/* thrown_bottle_2: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222c1f4 @ 0x0222c1f4, 0x20 bytes, Thumb
 * func_ov003_0222c1bc @ 0x0222c1bc, 0x38 bytes, Thumb
 * func_ov003_0222c16c @ 0x0222c16c, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x34];
    char unk_34;
    char pad_35[0x2b];
} UnkStruct_0222c1f4;

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_0222c1bc;

typedef struct {
    int x, y, z;
} Vec3;

extern UnkStruct_0222c1f4 data_ov003_0225f35c[];
extern char data_ov003_0225f390[];
extern void *data_021c67a4;
extern Vec3 data_021c67d0;
int func_ov003_0222799c(void *a, Vec3 *b, int dx, int dz, int dz2);

void *func_ov003_0222c1f4(int i)
{
    if (i < 0 || i >= 4) {
        return data_ov003_0225f390;
    }
    return &data_ov003_0225f35c[i].unk_34;
}

int func_ov003_0222c1bc(int i)
{
    int r = 0;
    UnkStruct_0222c1bc *e;
    int s;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &((UnkStruct_0222c1bc *) data_ov003_0225f35c)[i];
    if (e->unk_30 == 1) {
        s = e->unk_58;
        if (s == 0) {
            r = 1;
        } else if (s == 0xf) {
            r = 2;
        }
    }
    return r;
}

int func_ov003_0222c16c(char *e)
{
    int r = 0;
    Vec3 t;
    if (data_021c67a4 == 0) {
        return 1;
    }
    t.x = data_021c67d0.x;
    t.y = data_021c67d0.y;
    t.z = data_021c67d0.z;
    if (func_ov003_0222799c(e + 0x34, &t, 0x8000, 0x6000, 0x6000) == 0) {
        r = 1;
    }
    return r;
}
