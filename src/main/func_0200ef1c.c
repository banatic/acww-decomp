/* func_0200ef1c @ 0x0200ef1c, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200ef1c {
    int x, y, z;
} UnkStruct_0200ef1c;

typedef struct UnkStruct_0200ef1c_2 {
    u8 pad_00[0x5c];
    UnkStruct_0200ef1c v;
    u8 pad_68[0x182 - 0x68];
    u8 unk_182;
    u8 unk_183;
    u8 pad_184[0x1b0 - 0x184];
    u8 unk_1B0;
    u8 pad_1B1[0x800 - 0x1b1];
    int unk_800;
} UnkStruct_0200ef1c_2;

extern void *data_020ccf94;
extern int data_020d7300;

extern int func_02073908(void *h, int a);
extern int func_020960f8(int a, int b);
extern int func_02096614(short *pair, UnkStruct_0200ef1c *pos, int *z, int m, int e);
extern UnkStruct_0200ef1c *func_02095794(int a);
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, int b);
extern int func_020ea990(UnkStruct_0200ef1c *a, UnkStruct_0200ef1c *b);
extern void func_0200fa1c(UnkStruct_0200ef1c *out, UnkStruct_0200ef1c_2 *s, UnkStruct_0200ef1c *cur, short *ang, void *tbl);
extern void func_02010d64(UnkStruct_0200ef1c_2 *s);

void func_0200ef1c(UnkStruct_0200ef1c_2 *self)
{
    struct {
        short pair[2];
        UnkStruct_0200ef1c old;
    } s;
    UnkStruct_0200ef1c pos;
    UnkStruct_0200ef1c cur;
    UnkStruct_0200ef1c nv;
    UnkStruct_0200ef1c *p;
    UnkStruct_0200ef1c *q;
    UnkStruct_0200ef1c *tgt;
    int h;
    int d1;
    int d2;

    p = &self->v;
    s.old.x = p->x;
    s.old.y = p->y;
    s.old.z = p->z;
    if (self->unk_1B0 == 0) {
        goto end;
    }
    if (self->unk_182 != 0x15) {
        goto end;
    }
    h = self->unk_183;
    if (func_02073908(data_020ccf94, h) == 0) {
        goto end;
    }
    if (func_020960f8(2, 4) == 0) {
        goto end;
    }
    if (func_02096614(s.pair, &pos, &pos.z, -1, self->unk_800) == 0) {
        goto end;
    }
    tgt = func_02095794(h);
    q = &self->v;
    cur.x = q->x;
    cur.y = q->y;
    cur.z = q->z;
    d1 = func_020e8ed8(tgt->x - cur.x, tgt->z - cur.z);
    s.pair[1] = (short) func_020e8ed8(pos.x - cur.x, pos.z - cur.z);
    if (func_020e8b4c(d1, s.pair[1]) >= 0x400) {
        goto end;
    }
    d2 = func_020ea990(&cur, tgt);
    if (d2 > func_020ea990(&cur, &pos)) {
        goto end;
    }
    if (self->unk_800 >= h) {
        s.pair[1] = (short) (s.pair[1] + 0x4000);
    } else {
        s.pair[1] = (short) (s.pair[1] - 0x4000);
    }
    func_0200fa1c(&nv, self, &cur, &s.pair[1], &data_020d7300);
    p = &self->v;
    p->x = nv.x;
    p->y = nv.y;
    p->z = nv.z;
end:
    func_02010d64(self);
    p = &self->v;
    p->x = s.old.x;
    p->y = s.old.y;
    p->z = s.old.z;
}
