/* func_020597a8 @ 0x020597a8, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_020597a8;
typedef struct {
    char pad_00[0xc4];
    int h;
} UnkStruct_020597a8_2;

extern u8 data_020e54a8;
extern int func_0204fdec(int a, int b, UnkStruct_020597a8 *c, UnkStruct_020597a8 *d, int e, int f, int g, int h, int i, int j);
extern void func_ov003_02224678(int id, UnkStruct_020597a8 *a, UnkStruct_020597a8 *b, int c, int d, int e);
extern void func_ov004_02233b10(int id, UnkStruct_020597a8 *a, UnkStruct_020597a8 *b, int c, int d, int e);

void func_020597a8(UnkStruct_020597a8_2 *self, u16 *pid, UnkStruct_020597a8 *p2, UnkStruct_020597a8 *p3, short *s)
{
    unsigned int ok;
    unsigned int f;
    unsigned int id;
    int idx;
    int hnd;

    ok = 0;
    id = *pid;
    if (id >= 0x12e8 && id <= 0x131f) {
        ok = 1;
    }
    if (ok > 0) {
        hnd = self->h;
        if (hnd != -1) {
            if (id >= 0x12e8 && id <= 0x131f) {
                idx = id - 0x12e8;
            } else {
                idx = -1;
            }
            func_0204fdec(hnd, idx, p2, p3, s[0], s[1], s[2], 0, 0, 0x1f);
            return;
        }
    }
    if (data_020e54a8 == 0) {
        f = 1;
    } else {
        f = 0;
    }
    if (f == 1) {
        UnkStruct_020597a8 a, b;
        a.x = p2->x;
        a.y = p2->y;
        a.z = p2->z;
        b.x = p3->x;
        b.y = p3->y;
        b.z = p3->z;
        func_ov003_02224678(*pid, &a, &b, s[0], s[1], s[2]);
    } else {
        UnkStruct_020597a8 a, b;
        a.x = p2->x;
        a.y = p2->y;
        a.z = p2->z;
        b.x = p3->x;
        b.y = p3->y;
        b.z = p3->z;
        func_ov004_02233b10(*pid, &a, &b, s[0], s[1], s[2]);
    }
}
