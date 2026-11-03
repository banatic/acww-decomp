/* obj_020dd33c_modes_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02058528 @ 0x02058528, 0x10c bytes, Thumb
 * func_020584c4 @ 0x020584c4, 0x62 bytes, Thumb
 * func_02058414 @ 0x02058414, 0xb0 bytes, Thumb
 * func_020583b0 @ 0x020583b0, 0x62 bytes, Thumb
 * func_02058398 @ 0x02058398, 0x16 bytes, Thumb
 * func_0205831c @ 0x0205831c, 0x7c bytes, Thumb
 * func_02058280 @ 0x02058280, 0x9c bytes, Thumb
 * func_0205817c @ 0x0205817c, 0x104 bytes, Thumb
 * func_02058164 @ 0x02058164, 0x16 bytes, Thumb
 * func_0205815c @ 0x0205815c, 0x8 bytes, Thumb
 * func_02058140 @ 0x02058140, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad1[0x8e - 0x60];
    s16 unk_8E;
} UnkStruct_02058528;

typedef struct {
    u8 pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    Vec pos;
    u8 pad1[0x90 - 0x78];
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xcc - 0x9c];
    UnkStruct_02058528 *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
} UnkStruct_02058528_2;

struct UnkStruct_020584c4;

struct UnkStruct_020584c4 {
    unsigned char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    unsigned char pad_78[0x90 - 0x78];
    int unk_90;
    int unk_94;
    int unk_98;
    unsigned char pad_9C[0xd6 - 0x9c];
    unsigned short state;
};

typedef struct {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78[3];
    char pad_84[0x90 - 0x84];
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0xcc - 0x9c];
    void *unk_CC;
    char pad_D0[0xd6 - 0xd0];
    short unk_D6;
} UnkStruct_02058414;

typedef struct {
    char pad_00[0x60];
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
    unsigned int unk_6C;
    unsigned int unk_70;
    unsigned int unk_74;
    char pad_78[0x90 - 0x78];
    unsigned int unk_90;
    unsigned int unk_94;
    unsigned int unk_98;
    char pad_9C[0xd6 - 0x9c];
    unsigned short unk_D6;
} Context;

typedef struct Vec_0205831c {
    int x;
    int y;
    int z;
} Vec_0205831c;

typedef struct UnkStruct_0205831c {
    unsigned char pad_00[0x8e];
    short angle;
} UnkStruct_0205831c;

typedef struct UnkStruct_0205831c_2 {
    unsigned char pad_00[0x60];
    unsigned char mtx[0x78 - 0x60];
    Vec_0205831c vec; // 0x78
    unsigned char pad_84[0xcc - 0x84];
    UnkStruct_0205831c *ent; // 0xcc
    unsigned char pad_D0[0xd6 - 0xd0];
    unsigned short count; // 0xd6
} UnkStruct_0205831c_2;

typedef struct {
    char pad_00[0x6C];
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0x38];
    char unk_D4;
    short unk_D6;
} UnkStruct_02058280;

struct UnkStruct_0205817c {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

typedef struct UnkStruct_0205817c_2 {
    u8 pad_00[0x60];
    u8 unk_60[0x18];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xa8 - 0x9c];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    u8 pad_B4[0xcc - 0xb4];
    struct UnkStruct_0205817c *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
} UnkStruct_0205817c_2;

typedef struct {
    unsigned char pad_00[0xD4];
    unsigned char unk_D4;
    unsigned char unk_D5;
    unsigned short hword_D6;
} Func02058140;

extern int data_021c9358;
extern Vec data_021c93b4;
extern int data_021c93a8;
extern void func_020012dc(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_020b65c4(void);
extern void func_0204f7e0(Vec *, Vec *);
extern int func_020e895c(void *out, int a, int b);
extern int data_021c9390[3];
extern void func_0205967c(void *a, void *b);
extern void func_02059674(void *a, int b);
extern void func_020ea6e0(void *a, int b);
extern void VEC_Add(void *a, void *b, void *c);
extern int data_021c9364;
extern unsigned int data_021c9360;
extern void func_02058f54(void *);

void func_02058528(UnkStruct_02058528_2 *p)
{
    Vec v;
    int a, b, c;

    if (!(data_021c9358 & 1)) {
        data_021c93b4.x = 0x10000;
        data_021c93b4.y = 0;
        data_021c93b4.z = 0x17000;
        __register_global_object((void *) (&data_021c93b4), (((void *) func_020012dc)), (void *) (&data_021c93a8));
        data_021c9358 |= 1;
    }
    v.x = 0;
    v.y = 0;
    v.z = 0x2000;
    if (func_020b65c4() == 0x10) {
        p->pos.x = data_021c93b4.x;
        p->pos.y = data_021c93b4.y;
        p->pos.z = data_021c93b4.z;
    } else {
        func_020ea6e0((void *) (&v), p->unk_CC->unk_8E);
        VEC_Add((void *) (&v), &p->unk_CC->unk_5C, (void *) (&v));
        func_0204f7e0(&p->pos, &v);
    }
    p->pos.y += 0x1000;
    c = (p->pos.z - p->unk_68) / 4;
    if (c < 0) {
        c = -c;
    }
    b = (p->pos.y - p->unk_64) / 4;
    if (b < 0) {
        b = -b;
    }
    a = (p->pos.x - p->unk_60) / 4;
    if (a < 0) {
        a = -a;
    }
    p->unk_90 = a;
    p->unk_94 = b;
    p->unk_98 = c;
    p->unk_D6 = 0;
    func_02059674((void *) p, 1);
}

void func_020584c4(struct UnkStruct_020584c4 *this)
{
    if ((int) this->state >= 4) {
        return;
    }
    func_020e895c(&this->unk_60, this->unk_6C, this->unk_90);
    func_020e895c(&this->unk_64, this->unk_70, this->unk_94);
    func_020e895c(&this->unk_68, this->unk_74, this->unk_98);
    this->state++;
    if ((int) this->state < 4) {
        return;
    }
    func_02059674((void *) this, 0);
}

void func_02058414(UnkStruct_02058414 *self)
{
    int d1;
    int d0;
    int d2;
    func_0205967c(self, ((char *) self) + 0x6c);
    if (self->unk_CC) {
        self->unk_78[0] = data_021c9390[0];
        self->unk_78[1] = data_021c9390[1];
        self->unk_78[2] = data_021c9390[2];
        func_020ea6e0(self->unk_78, *((short *) (((char *) self->unk_CC) + 0x8e)));
    }
    VEC_Add(((char *) self) + 0x6c, ((char *) self) + 0x78, ((char *) self) + 0x6c);
    d0 = (self->unk_74 - self->unk_68) / 2;
    if (d0 < 0) {
        d0 = -d0;
    }
    d1 = (self->unk_70 - self->unk_64) / 2;
    if (d1 < 0) {
        d1 = -d1;
    }
    d2 = (self->unk_6C - self->unk_60) / 2;
    if (d2 < 0) {
        d2 = -d2;
    }
    self->unk_90 = d2;
    self->unk_94 = d1;
    self->unk_98 = d0;
    self->unk_D6 = 0;
    func_02059674(self, 1);
}

void func_020583b0(Context *this)
{
    if ((int) this->unk_D6 < 2) {
        func_020e895c(&this->unk_60, (int) ((void *) this->unk_6C), (int) ((void *) this->unk_90));
        func_020e895c(&this->unk_64, (int) ((void *) this->unk_70), (int) ((void *) this->unk_94));
        func_020e895c(&this->unk_68, (int) ((void *) this->unk_74), (int) ((void *) this->unk_98));
        this->unk_D6++;
        if ((int) this->unk_D6 >= 2) {
            func_02059674(this, 0);
        }
    }
}

void func_02058398(void *param1)
{
    void *r4;
    r4 = param1;
    func_02059674(r4, 1);
    r4 = (void *) ((unsigned int) r4 + 0xd6);
    *(unsigned short *) r4 = 0;
}

void func_0205831c(UnkStruct_0205831c_2 *self)
{
    if ((int) self->count >= 10) {
        return;
    }
    func_0205967c((void *) self, (void *) self->mtx);
    if (self->ent != 0) {
        self->vec.x = (*(Vec_0205831c *) data_021c9390).x;
        self->vec.y = (*(Vec_0205831c *) data_021c9390).y;
        self->vec.z = (*(Vec_0205831c *) data_021c9390).z;
        func_020ea6e0((void *) (&self->vec), self->ent->angle);
    }
    VEC_Add((void *) self->mtx, (void *) (&self->vec), (void *) self->mtx);
    self->count = self->count + 1;
    if ((int) self->count >= 10) {
        func_02059674((void *) self, 0);
    }
}

void func_02058280(UnkStruct_02058280 *obj)
{
    int b, a, c;

    obj->unk_6C = 0;
    obj->unk_70 = 0;
    obj->unk_74 = 0;

    obj->unk_84 = data_021c9390[0];
    obj->unk_88 = data_021c9390[1];
    obj->unk_8C = data_021c9390[2];

    obj->unk_78 = 0;
    obj->unk_7C = 0;
    obj->unk_80 = 0;

    a = obj->unk_8C / 8;
    if (a < 0) {
        a = -a;
    }

    b = obj->unk_88 / 8;
    if (b < 0) {
        b = -b;
    }

    c = obj->unk_84 / 8;
    if (c < 0) {
        c = -c;
    }

    obj->unk_90 = c;
    obj->unk_94 = b;
    obj->unk_98 = a;

    func_02059674((void *) obj, 1);

    obj->unk_D6 = 0;
    obj->unk_D4 = 0;
}

void func_0205817c(UnkStruct_0205817c_2 *p)
{
    int tmp;
    int v;

    if (!(data_021c9364 & 1)) {
        data_021c9360 = 0x200;
        data_021c9364 |= 1;
    }
    tmp = p->unk_A8;
    if ((int) p->unk_D6 >= 8) {
        return;
    }

    func_0205967c((void *) p, &p->unk_60[0]);
    func_020e895c(&tmp, 0, data_021c9360);
    v = tmp;
    p->unk_A8 = v;
    p->unk_AC = v;
    p->unk_B0 = v;
    func_020e895c(&p->unk_84, 0, p->unk_90);
    func_020e895c(&p->unk_88, 0, p->unk_94);
    func_020e895c(&p->unk_8C, 0, p->unk_98);
    if (p->unk_CC) {
        p->unk_78 = p->unk_84;
        p->unk_7C = p->unk_88;
        p->unk_80 = p->unk_8C;
        func_020ea6e0(&p->unk_78, p->unk_CC->unk_8E);
    }
    VEC_Add(&p->unk_60[0], &p->unk_78, &p->unk_60[0]);
    p->unk_D6++;
    if ((int) p->unk_D6 >= 8) {
        func_02059674((void *) p, 0);
    }
}

void func_02058164(void *param1)
{
    void *r4;
    r4 = param1;
    func_02059674(r4, 1);
    r4 = (char *) r4 + 0xd6;
    *(unsigned short *) r4 = 0;
}

void func_0205815c(void *argument0)
{
    func_02058f54((void *) argument0);
}

void func_02058140(Func02058140 *ptr)
{
    func_02059674(ptr, 1);
    ptr->hword_D6 = 0;
    ptr->unk_D4 = 0;
}
