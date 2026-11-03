/* town_nook: 6 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226e3a4 @ 0x0226e3a4, 0xe bytes, Thumb
 * func_ov068_0226e210 @ 0x0226e210, 0x194 bytes, Thumb
 * func_ov068_0226e1fc @ 0x0226e1fc, 0x14 bytes, Thumb
 * func_ov068_0226e1d8 @ 0x0226e1d8, 0x22 bytes, Thumb
 * func_ov068_0226e1ac @ 0x0226e1ac, 0x2c bytes, Thumb
 * func_ov068_0226e184 @ 0x0226e184, 0x28 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_0226e210 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0226e210;

typedef struct UnkStruct_0226e210_2 {
    unsigned char pad_00[0x5c];
    Vec v;
    unsigned char pad1[0x564 - 0x68];
    unsigned char obj[0x718 - 0x564];
    Vec d;
} UnkStruct_0226e210_2;

typedef struct UnkStruct_0226e210_3 {
    unsigned char pad_00[0x40];
    UnkStruct_0226e210 *t;
    unsigned char pad1[0xb4 - 0x44];
    unsigned char state;
    unsigned char pad_B5[3];
    UnkStruct_0226e210_2 *sub;
} UnkStruct_0226e210_3;

struct UnkStruct_0226e1fc {
    char pad_00[0x654];
    int unk_654;
};

typedef struct {
    void *vtable;
    char pad_04[0x658 - 4];
    int unk_658;
} UnkStruct_0226e1ac;

extern unsigned short data_020c80f8;
extern unsigned char data_021f43ec;
extern void *data_ov068_0227733c;
extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);
extern void func_02095eec(int, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_02019de8(void *);
extern int func_02019e00(void *);
extern int func_020a12d4(void);
extern void func_0206844c(UnkStruct_0226e210 *, unsigned char *, void *);
extern int func_0203af80(Vec *);
extern void func_ov068_0226e878(int a, int b);
extern void *func_ov068_0226e5d4(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov068_02277574[];

void func_ov068_0226e3a4(void *r0, int r1)
{
    *(int *) ((char *) r0 + 0xb0) = r1;
    *(char *) ((char *) r0 + 0xb4) = 0;
}

void func_ov068_0226e210(UnkStruct_0226e210_3 *self)
{
    unsigned char c;
    Vec lv;
    Vec *src;
    Vec *dst;
    UnkStruct_0226e210 *t;

    switch (self->state) {
        case 0:
            if (self->t->unk_04 == 5) {
                func_02035624(0x13);
                func_020356c4(0x15, 0x47, 0x7f, 1);
                func_02095eec(0, 4);
                src = &self->sub->v;
                dst = &self->sub->d;
                dst->x = self->sub->v.x;
                dst->y = src->y;
                dst->z = src->z;
                self->sub->d.x = self->sub->d.x + 0x6000;
                func_02019d0c(self->sub->obj, 2, 2, self->sub->d.x, self->sub->d.z, 0, 0, 0, 0, data_020c80f8, 0);
                self->state = 1;
            }
            break;
        case 1:
            if (func_02019de8(self->sub->obj) != 0) {
                if (func_02019e00(self->sub->obj) == 2) {
                    func_02019d0c(self->sub->obj, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                    self->state = 2;
                }
            }
            break;
        case 2:
            if (func_02019de8(self->sub->obj) != 0) {
                if (func_02019e00(self->sub->obj) == 0) {
                    t = self->t;
                    c = data_021f43ec;
                    if (func_020a12d4() != 0) {
                        c = 0xd;
                    } else {
                        c = 0xa;
                    }
                    func_0206844c(t, &c, data_ov068_0227733c);
                    t->unk_08 = 1;
                    src = &self->sub->v;
                    lv.x = self->sub->v.x;
                    lv.y = src->y;
                    lv.z = src->z;
                    lv.y = lv.y + 0x2000;
                    func_0203af80(&lv);
                    func_ov068_0226e3a4((void *) self, 0);
                }
            }
            break;
    }
}

int func_ov068_0226e1fc(struct UnkStruct_0226e1fc *self)
{
    int ret = 0;
    if (self->unk_654 == 0) {
        ret = 1;
    }
    return ret;
}

void func_ov068_0226e1d8(int a, int b)
{
    switch (b) {
        case 1:
            func_ov068_0226e878(a, 2);
            break;
        case 8:
            func_ov068_0226e878(a, 5);
            break;
    }
}

UnkStruct_0226e1ac *func_ov068_0226e1ac(UnkStruct_0226e1ac *self)
{
    self->vtable = (void *) data_ov068_02277574;
    func_ov068_0226e5d4(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_ov068_0226e184(void *self)
{
    *(void **) self = (void *) ((char *) data_ov068_02277574);
    func_ov068_0226e5d4((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
