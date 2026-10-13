/* func_ov003_022241a4 @ 0x022241a4, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[8];
    u16 unk_08;
    u16 unk_0A;
} UnkStruct_022241a4;

extern void *data_020ccf94;
extern int func_02045bb8(u8 i, int k);
extern UnkStruct_022241a4 *func_02045bac(int r);
extern void func_ov003_02220d50(int i, u16 id, int *p);
extern void func_0204f794(Vec3 *v, int x, int y);
extern void func_ov003_02220bb0(int i, u16 id, int *a, Vec3 *w);

void func_ov003_022241a4(int *pos)
{
    volatile u16 t[3];
    int p[2];
    int a[2];
    Vec3 v;
    Vec3 w;
    int i;
    int r;
    UnkStruct_022241a4 *e;
    u16 tmp;
    i = *(int *) ((char *) data_020ccf94 + 0x64);
    r = func_02045bb8((u8) i, 4);
    if (r >= 0) {
        e = func_02045bac(r);
        p[0] = pos[0];
        p[1] = pos[1];
        func_ov003_02220d50(i, e->unk_0A, p);
    }
    r = func_02045bb8((u8) i, 3);
    if (r >= 0) {
        e = func_02045bac(r);
        func_0204f794(&v, pos[0], pos[1]);
        t[2] = e->unk_08;
        tmp = t[2];
        t[1] = tmp;
        t[0] = tmp;
        w.x = v.x;
        w.y = v.y;
        w.z = v.z;
        a[0] = t[0] >> 8;
        a[1] = t[1] & 0xff;
        func_ov003_02220bb0(i, e->unk_0A, a, &w);
    }
}
