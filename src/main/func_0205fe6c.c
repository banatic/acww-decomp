/* func_0205fe6c @ 0x0205fe6c, 0x188 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0205fe6c;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_0205fe6c vec;
} UnkStruct_0205fe6c_2;

typedef struct {
    u8 pad_00[8];
    UnkStruct_0205fe6c pos;
    u8 pad_14[0x14];
    UnkStruct_0205fe6c_2 *unk_28;
    u8 pad_2C[8];
    int unk_34;
} UnkStruct_0205fe6c_3;

extern int func_02034270(void *buf, UnkStruct_0205fe6c *p, int a, int b);
extern void func_020eaad0(int *dst, void *src, int n);
extern int func_020e8ed8(int a, int b);
extern void VEC_Add(UnkStruct_0205fe6c *a, int *b, UnkStruct_0205fe6c *c);
extern int func_020912d4(int a, UnkStruct_0205fe6c *v, u16 *h, int d);
extern int func_020ea990(UnkStruct_0205fe6c *v, UnkStruct_0205fe6c *p);
extern int FX_MulFunc(int a, int b);
extern void func_02091278(int a, UnkStruct_0205fe6c *v, u16 *h, int d);
extern void func_0209129c(int a);
extern void func_0203423c(void *buf);

extern short FX_SinCosTable_[];

void func_0205fe6c(UnkStruct_0205fe6c_3 *self)
{
    u16 h;
    UnkStruct_0205fe6c v0;
    char buf[0x40];
    UnkStruct_0205fe6c v1;
    int m[4];
    UnkStruct_0205fe6c_2 *o;
    UnkStruct_0205fe6c *q;
    int t;
    int d;
    int r;
    int idx;

    o = self->unk_28;
    q = &o->vec;
    v0.a = o->vec.a;
    v0.b = q->b;
    v0.c = q->c;
    func_02034270(buf, &self->pos, 0, 1);
    h = 0;
    if (*(int *) (buf + 0x30) != 0) {
        func_020eaad0(m, buf + 0x24, 5);
        h = (u16) func_020e8ed8(m[0], m[2]);
        VEC_Add(&self->pos, m, &self->pos);
        t = *(int *) (buf + 0x3c);
        d = self->pos.b;
        if (d < t + 0x333) {
            if (d < t + 0x19a) {
                self->pos.b = d + 0x66;
                if (self->pos.b >= t + 0x19a) {
                    v1.a = self->pos.a;
                    v1.b = self->pos.b;
                    v1.c = self->pos.c;
                    v1.b = t;
                    func_020912d4(0xf, &v1, 0, 0);
                }
            } else {
                self->pos.b = d + 0x66;
            }
        } else {
            self->pos.b = t + 0x30a;
        }
    }
    r = func_020ea990(&v0, &self->pos);
    if (r >= 0x8000) {
        idx = ((int) (u16) func_020e8ed8(self->pos.a - v0.a, self->pos.c - v0.c) >> 4) * 2;
        self->pos.a = v0.a + FX_MulFunc(0x7f33, FX_SinCosTable_[idx]);
        self->pos.c = v0.c + FX_MulFunc(0x7f33, FX_SinCosTable_[idx + 1]);
        if (*(int *) (buf + 0x30) != 0) {
            v1.a = self->pos.a;
            v1.b = self->pos.b;
            v1.c = self->pos.c;
            v1.b = *(int *) (buf + 0x3c);
            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0xe, &v1, &h, 0);
            } else {
                func_02091278(self->unk_34, &v1, &h, 0);
            }
        }
    } else if (self->unk_34 != -1) {
        if (r < 0x7e66) {
            func_0209129c(self->unk_34);
            self->unk_34 = -1;
        } else if (*(int *) (buf + 0x30) != 0) {
            v1.a = self->pos.a;
            v1.b = self->pos.b;
            v1.c = self->pos.c;
            v1.b = *(int *) (buf + 0x3c);
            func_02091278(self->unk_34, &v1, &h, 0);
        }
    }
    func_0203423c(buf);
}
