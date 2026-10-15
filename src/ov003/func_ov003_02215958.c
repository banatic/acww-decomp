/* func_ov003_02215958 @ 0x02215958, 0x118 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c8];
    char unk_5C8;
    char pad_5C9[3];
    int unk_5CC;
    Vec3 unk_5D0;
    char pad_5DC[0x800 - 0x5dc];
    int unk_800;
    char pad_804[0x8c4 - 0x804];
    int unk_8C4;
    int unk_8C8;
    int unk_8CC;
    char pad_8D0[0x8f0 - 0x8d0];
    char unk_8F0;
} UnkStruct_02215958;

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_ov003_02215ba8(void *e, Vec3 *p, int k);
extern void func_ov003_02215b90(void *e, Vec3 *p, u8 *mode);
extern void func_0206026c(void *p, int a);
extern void func_02060428(void *p, Vec3 *v);
extern int func_0200f328(UnkStruct_02215958 *self, int a);

void func_ov003_02215958(UnkStruct_02215958 *self)
{
    u8 mode;
    volatile Vec3 p;
    struct {
        Vec3 q, r, s;
    } W;
    void *e;
    int m;
    int k;
    int dx, dz;
    Vec3 *pv;

    e = &self->unk_8F0;
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02215ba8(e, &self->unk_5D0, (u8) self->unk_5CC);
        return;
    }
    func_ov003_02215b90(e, (Vec3 *) &p, &mode);
    m = mode;
    k = self->unk_5CC;
    if (k != 4) {
        if (k != 3) {
            if (m == 4) {
                func_0206026c(&self->unk_5C8, m);
                W.r.x = p.x;
                W.r.y = p.y;
                W.r.z = p.z;
                func_02060428(&self->unk_5C8, &W.r);
            } else if (k >= 6) {
                func_0206026c(&self->unk_5C8, 0);
            }
        }
    } else {
        pv = &self->unk_5D0;
        W.q.x = pv->x;
        W.q.y = pv->y;
        W.q.z = pv->z;
        dx = W.q.x - p.x;
        dz = W.q.z - p.z;
        if (dx * dx + dz * dz >= 0x400000) {
            W.s.x = p.x;
            W.s.y = p.y;
            W.s.z = p.z;
            func_02060428(&self->unk_5C8, &W.s);
        }
        if (m == 5) {
            func_0206026c(&self->unk_5C8, m);
            func_0200f328(self, 0x84f);
            self->unk_8C4 = p.x;
            self->unk_8C8 = p.y;
            self->unk_8CC = p.z;
        }
    }
}
