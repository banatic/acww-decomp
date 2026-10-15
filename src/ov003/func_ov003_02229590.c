/* func_ov003_02229590 @ 0x02229590, 0x260 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    u8 a;
    u8 pad_01;
    s16 b;
} UnkStruct_02229590;
typedef struct {
    UnkStruct_02229590 *p;
    int pad_04;
} UnkStruct_02229590_2;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    char pad_60[0x24];
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    u8 unk_94;
    char pad_95[7];
    int unk_9C;
} UnkStruct_02229590_3;

extern u8 data_020cb784[];
extern u8 data_020cb785[];
extern u8 data_ov003_0223c022[];
extern u8 data_ov003_0223c023[];
extern int data_020c904c;
extern void *data_020ccf94;
extern UnkStruct_02229590_2 data_ov003_0223bf00[];

extern int func_020912d4(int a, Vec3 *v, int c, int d);
extern int func_020044c0(UnkStruct_02229590_3 *self, int a, int b, int c);
extern int func_02073d90(void *a);
extern int func_02073918(void *a, int b);
extern int func_ov003_02228400(Vec3 *v, int lim);

void func_ov003_02229590(UnkStruct_02229590_3 *self, int p1)
{
    Vec3 v;
    void *g;
    int t, kind, j, k, q;
    int *pf9c;

    self->unk_40 = 1;
    self->unk_94 = 0;
    t = self->unk_90 * 6;
    kind = data_020cb784[t];
    j = kind * 0x14;
    self->unk_84 = ((int) data_ov003_0223c022[j] << 12) / 100;
    self->unk_88 = 0x1000;
    self->unk_8C = ((int) data_ov003_0223c023[j] << 12) / 100;
    self->unk_58 = data_020c904c;
    self->unk_90 = 0x3b;
    v.x = self->unk_54;
    v.y = self->unk_58;
    v.z = self->unk_5C;
    pf9c = &self->unk_9C;

    switch (kind) {
        case 0:
            func_020912d4(0x12, &v, 0, 0);
            *pf9c = func_020912d4(0x1a, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 1:
            func_020912d4(0x13, &v, 0, 0);
            *pf9c = func_020912d4(0x1b, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 2:
            func_020912d4(0x14, &v, 0, 0);
            *pf9c = func_020912d4(0x1c, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 3:
            func_020912d4(0x15, &v, 0, 0);
            *pf9c = func_020912d4(0x1d, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
        case 4:
            func_020912d4(0x16, &v, 0, 0);
            *pf9c = func_020912d4(0x1e, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
        case 5:
            func_020912d4(0x17, &v, 0, 0);
            *pf9c = func_020912d4(0x1f, &v, 0, 0);
            func_020044c0(self, 0x7e4, 0x7f, 0);
            break;
        case 6:
            func_020912d4(0x19, &v, 0, 0);
            *pf9c = func_020912d4(0x21, &v, 0, 0);
            func_020044c0(self, 0x7e4, 0x7f, 0);
            break;
        case 7:
            func_020912d4(0x18, &v, 0, 0);
            *pf9c = func_020912d4(0x20, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
    }

    self->unk_48 = 5;
    g = data_020ccf94;
    if (func_02073d90(g) != 0) {
        if (func_02073918(g, p1) != 0) {
            k = data_020cb785[t];
            q = ((int) data_ov003_0223bf00[0].p[k].a << 12) / 10;
            func_ov003_02228400(&v, q);
        }
    } else {
        k = data_020cb785[t];
        q = ((int) data_ov003_0223bf00[0].p[k].a << 12) / 10;
        func_ov003_02228400(&v, q);
    }
}
