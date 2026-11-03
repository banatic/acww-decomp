/* name_texts: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02062fbc @ 0x02062fbc, 0x20 bytes, Thumb
 * func_02062f90 @ 0x02062f90, 0x2c bytes, Thumb
 * func_02062f64 @ 0x02062f64, 0x2c bytes, Thumb
 * func_02062f4c @ 0x02062f4c, 0x18 bytes, Thumb
 * func_02062f2c @ 0x02062f2c, 0x20 bytes, Thumb
 * func_02062ea4 @ 0x02062ea4, 0x88 bytes, Thumb
 * func_02062e80 @ 0x02062e80, 0x22 bytes, Thumb
 * func_02062e78 @ 0x02062e78, 0x8 bytes, Thumb
 * func_02062e74 @ 0x02062e74, 0x4 bytes, Thumb
 * func_02062e70 @ 0x02062e70, 0x4 bytes, Thumb
 * func_02062e50 @ 0x02062e50, 0x20 bytes, Thumb
 * func_02062e18 @ 0x02062e18, 0x38 bytes, Thumb
 * func_02062e00 @ 0x02062e00, 0x18 bytes, Thumb
 * func_02062de0 @ 0x02062de0, 0x20 bytes, Thumb
 * func_02062ddc @ 0x02062ddc, 0x4 bytes, Thumb
 * func_02062dd8 @ 0x02062dd8, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
} UnkStruct_02062f90;

typedef struct {
    int *vtable;
} UnkStruct_02062f64;

struct UnkStruct_02062f2c {
    int *unk_00;
};

typedef struct {
    u32 unk_00;
    u32 val;
    u8 a;
    u8 b;
} UnkStruct_02062ea4;

typedef struct {
    u8 pad[8];
    UnkStruct_02062ea4 sub;
} UnkStruct_02062ea4_2;

struct UnkStruct_02062e18 {
    void *vptr;
    u8 pad_04[10];
    u16 data[10];
};

struct Blk {
    u16 v[10];
};

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020de62c;
extern void *func_020a8c38(void *);
extern void func_020edb3c(struct UnkStruct_02062f2c *self);
void func_02061e2c(void *p, unsigned short *);
int func_0204bd08(void *p);
int func_02062a28(void *p);
int func_020629e4(void *p);
int func_020629dc(void *p);
int func_020629d4(void *p);
int func_0204bcdc(void *p);
int func_0204bc64(void *p);
int func_020537e8(int value);
int func_02053da4(int value);
int func_02053d9c(int value);
int func_02053d94(int value);
extern int func_02062280(int param1);
extern int func_020a8be4(int, int);
extern void *func_020a88ec(void *);
extern void func_0205195c(void *);
extern char data_020de614;
void *func_020a887c(void *arg);

int func_02062ea4(UnkStruct_02062ea4_2 *self, unsigned short *argument1);
int func_02062e80(int param1, int param2);
int func_02062e78(int argument0, int argument1);

void *func_02062fbc(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = &data_020de62c;
    func_020a8c1c(arg);
    return arg;
}

void *func_02062f90(UnkStruct_02062f90 *self, void *arg)
{
    func_020a8cac(self);
    self->unk_00 = &data_020de62c;
    func_020a8c1c(self);
    func_02062ea4((UnkStruct_02062ea4_2 *) self, (unsigned short *) arg);
    return self;
}

UnkStruct_02062f64 *func_02062f64(UnkStruct_02062f64 *self, int arg)
{
    func_020a8cac((void *) self);
    self->vtable = ((int *) &data_020de62c);
    func_020a8c1c((void *) self);
    func_02062e80((int) self, arg);
    return self;
}

void *func_02062f4c(void *self)
{
    *(void **) self = (void *) ((unsigned char *) &data_020de62c);
    func_020a8c38(self);
    return self;
}

struct UnkStruct_02062f2c *func_02062f2c(struct UnkStruct_02062f2c *self)
{
    self->unk_00 = ((int *) &data_020de62c);
    func_020a8c38((void *) self);
    func_020edb3c(self);
    return self;
}

int func_02062ea4(UnkStruct_02062ea4_2 *self, unsigned short *argument1)
{
    struct {
        u32 pad;
        int local;
    } s;
    UnkStruct_02062ea4 *sub;

    func_02061e2c(&s.local, (unsigned short *) argument1);
    sub = &self->sub;

    if (func_0204bd08(&s.local) != 0) {
        func_02062e78((int) self, func_02062a28(&s.local));
        sub->val = func_020629e4(&s.local);
        sub->b = func_020629dc(&s.local);
        sub->a = func_020629d4(&s.local);
        return 1;
    }

    if (func_0204bcdc(&s.local) != 0) {
        int v = func_0204bc64(&s.local);

        func_02062e78((int) self, func_020537e8(v));
        sub->val = func_02053da4(v);
        sub->b = func_02053d9c(v);
        sub->a = func_02053d94(v);
        return 1;
    }

    return 0;
}

int func_02062e80(int param1, int param2)
{
    int result;
    int temp;

    if (param2 < 0x4a) {
        temp = func_02062280(param2);
        result = func_02062e78(param1, temp);
        return 1;
    }
    return 0;
}

int func_02062e78(int argument0, int argument1)
{
    return func_020a8be4((int) argument0, (int) argument1);
}

int func_02062e74(void)
{
    return 22;
}

int func_02062e70(int p0)
{
    return ((int) (p0) + (18));
}

void *func_02062e50(void *self)
{
    func_020a88ec(self);
    *(void **) self = (void *) &data_020de614;
    func_0205195c(self);
    return self;
}

struct UnkStruct_02062e18 *func_02062e18(struct UnkStruct_02062e18 *self, const u16 *src)
{
    u16 *dst;
    int i;

    func_020a88ec((void *) self);
    self->vptr = ((int *) &data_020de614);
    func_0205195c((void *) self);

    *(struct Blk *) ((u8 *) self + 0xe) = *(struct Blk *) src;

    return self;
}

void *func_02062e00(void *arg)
{
    *(void **) arg = (void *) &data_020de614;
    func_020a887c(arg);
    return arg;
}

void *func_02062de0(void *self)
{
    *(void **) self = &data_020de614;
    func_020a887c(self);
    func_020edb3c((struct UnkStruct_02062f2c *) self);
    return self;
}

int func_02062ddc(void)
{
    return 10;
}

int func_02062dd8(int p0)
{
    return ((int) (p0) + (14));
}
