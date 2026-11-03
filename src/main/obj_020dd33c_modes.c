/* obj_020dd33c_modes: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057f38 @ 0x02057f38, 0x12c bytes, Thumb
 * func_02057e0c @ 0x02057e0c, 0x12c bytes, Thumb
 */

#include "types.h"

struct Vec {
    int x, y, z;
};

struct UnkStruct_02057f38 {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

struct UnkStruct_02057f38_2 {
    u8 pad_00[0x60];
    struct Vec unk_60;
    struct Vec unk_6C;
    struct Vec unk_78;
    struct Vec unk_84;
    struct Vec unk_90;
    u8 pad_9C[0xcc - 0x9c];
    struct UnkStruct_02057f38 *unk_CC;
    u8 pad_D0[4];
    u8 unk_D4;
    u8 pad_D5;
    u16 unk_D6;
};

typedef struct UnkStruct_02057e0c {
    unsigned char pad_00[0x60];
    unsigned char unk_60[0x18];
    unsigned int vec78[3];
    unsigned char buf84[0xc];
    unsigned int size90;
    unsigned int size94;
    unsigned int size98;
    unsigned char pad_9C[0xc];
    unsigned int vecA8[3];
    unsigned char pad_B4[0x18];
    void *unk_CC;
    unsigned char pad_D0[4];
    unsigned char stateD4;
    unsigned char pad_D5;
    unsigned short countD6;
} UnkStruct_02057e0c;

extern u8 data_020cbaf4[];
extern struct Vec data_021c9390;
extern void func_0205967c(struct UnkStruct_02057f38_2 *, struct Vec *);
extern void func_020ea6e0(struct Vec *, int);
extern void VEC_Add(struct Vec *, struct Vec *, struct Vec *);
extern int func_020e895c(int *, int, int);
extern unsigned int data_021c9374;
extern unsigned int data_021c9368;
extern unsigned char data_021c9340[];
extern void func_02059674(void *, int);

void func_02057f38(struct UnkStruct_02057f38_2 *o)
{
    int lim;
    int tx, ty, tz;

    lim = data_020cbaf4[1];
    if (o->unk_D6 < lim) {
        func_0205967c(o, &o->unk_6C);
        if (o->unk_CC) {
            o->unk_78.x = data_021c9390.x;
            o->unk_78.y = data_021c9390.y;
            o->unk_78.z = data_021c9390.z;
            func_020ea6e0(&o->unk_78, o->unk_CC->unk_8E);
        }
        VEC_Add(&o->unk_6C, &o->unk_78, &o->unk_6C);
        func_020e895c(&o->unk_60.x, o->unk_6C.x, o->unk_90.x);
        func_020e895c(&o->unk_60.y, o->unk_6C.y, o->unk_90.y);
        func_020e895c(&o->unk_60.z, o->unk_6C.z, o->unk_90.z);
        o->unk_D6++;
        if (o->unk_D6 >= lim) {
            o->unk_6C.x = 0;
            o->unk_6C.y = 0;
            o->unk_6C.z = 0;
            o->unk_84.x = data_021c9390.x;
            o->unk_84.y = data_021c9390.y;
            o->unk_84.z = data_021c9390.z;
            o->unk_78.x = 0;
            o->unk_78.y = 0;
            o->unk_78.z = 0;
            tz = o->unk_84.z / 8;
            if (tz < 0) {
                tz = -tz;
            }
            ty = o->unk_84.y / 8;
            if (ty < 0) {
                ty = -ty;
            }
            tx = o->unk_84.x / 8;
            if (tx < 0) {
                tx = -tx;
            }
            o->unk_90.x = tx;
            o->unk_90.y = ty;
            o->unk_90.z = tz;
            o->unk_D4 = 2;
        }
    }
}

void func_02057e0c(UnkStruct_02057e0c *self)
{
    unsigned int local;
    unsigned int tmp;
    unsigned char limit;
    int v;

    if ((data_021c9374 & 1) == 0) {
        v = 0x1000 / data_021c9340[1];
        if (v < 0) {
            v = -v;
        }
        data_021c9368 = v;
        data_021c9374 |= 1;
    }

    local = self->vecA8[0];
    limit = ((unsigned char *) data_020cbaf4)[2];

    if (self->countD6 >= limit) {
        return;
    }

    func_0205967c((struct UnkStruct_02057f38_2 *) self, (struct Vec *) (&self->unk_60));
    func_020e895c((int *) (&local), 0, data_021c9368);
    tmp = local;
    self->vecA8[0] = tmp;
    self->vecA8[1] = tmp;
    self->vecA8[2] = tmp;
    func_020e895c((int *) (&self->buf84[0]), 0, self->size90);
    func_020e895c((int *) (&self->buf84[4]), 0, self->size94);
    func_020e895c((int *) (&self->buf84[8]), 0, self->size98);

    if (self->unk_CC != 0) {
        self->vec78[0] = *(unsigned int *) &self->buf84[0];
        self->vec78[1] = *(unsigned int *) &self->buf84[4];
        self->vec78[2] = *(unsigned int *) &self->buf84[8];
        func_020ea6e0((struct Vec *) self->vec78, (short) (*(short *) ((char *) self->unk_CC + 0x8e)));
    }

    VEC_Add((struct Vec *) (&self->unk_60), (struct Vec *) self->vec78, (struct Vec *) (&self->unk_60));

    self->countD6++;
    if (self->countD6 < limit) {
        return;
    }

    self->stateD4 = 3;
    func_02059674(self, 0);
}
