/* cell_pair_sprite_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a448 @ 0x0208a448, 0x48 bytes, Thumb
 * func_0208a41c @ 0x0208a41c, 0x2c bytes, Thumb
 * func_0208a3ec @ 0x0208a3ec, 0x30 bytes, Thumb
 * func_0208a2d8 @ 0x0208a2d8, 0x114 bytes, Thumb
 * func_0208a2b8 @ 0x0208a2b8, 0x20 bytes, Thumb
 * func_0208a2b0 @ 0x0208a2b0, 0x8 bytes, Thumb
 * func_0208a2a8 @ 0x0208a2a8, 0x6 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[20];
} UnkStruct_0208a448;

typedef struct {
    unsigned int vtable;
    char pad_04[8];
    UnkStruct_0208a448 sub1;
    UnkStruct_0208a448 sub2;
    int unk_34;
    int unk_38;
    int unk_3C;
    unsigned char unk_40;
    unsigned char unk_41;
} Obj_t;

typedef struct UnkStruct_0208a2d8 {
    u8 pad_00[0xc];
    u8 unk_0C[0x14];
    u8 unk_20[0x14];
    int unk_34;
    int unk_38;
    int unk_3C;
    u8 unk_40;
    u8 unk_41;
} UnkStruct_0208a2d8;

typedef struct {
    unsigned char pad_00[0x38];
    unsigned long a;
    unsigned long b;
} UnkStruct_0208a2a8;

extern void func_0208af30(Obj_t *obj);
extern void func_0208a1f8(void *ptr);
extern void func_0208a238(void *, int);
extern unsigned char data_020e2058[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *p);
extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(UnkStruct_0208a2d8 *);
extern int func_0208aeec(UnkStruct_0208a2d8 *);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern void func_0208a0c8(void *);

Obj_t *func_0208a448(Obj_t *obj, int b)
{
    func_0208af30(obj);
    obj->vtable = (unsigned int) ((char *) data_020e2058);
    func_0208a1f8(&obj->sub1);
    func_0208a1f8(&obj->sub2);
    obj->unk_34 = 0;
    obj->unk_38 = 0;
    obj->unk_3C = 0;
    obj->unk_40 = 0;
    obj->unk_41 = (char) b;
    func_0208a238(obj, 0);
    return obj;
}

void *func_0208a41c(void *param)
{
    *(void **) param = (void *) data_020e2058;
    func_0208a1f4((char *) param + 0x20);
    func_0208a1f4((char *) param + 0xc);
    func_0208af00(param);
    return param;
}

void *func_0208a3ec(void *arg)
{
    struct UnkStruct_0208a3ec {
        void *field0;
        char pad1[8];
        char fieldC[20];
        char field20[4];
    } *self;

    self = (struct UnkStruct_0208a3ec *) arg;
    self->field0 = (void *) &data_020e2058;
    func_0208a1f4(self->field20);
    func_0208a1f4(self->fieldC);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0208a2d8(UnkStruct_0208a2d8 *p)
{
    int v20;
    int v24;
    int t;
    int v28;
    int v2c;
    int v30;
    int x;
    int y;

    if (!p->unk_34) {
        return;
    }
    v20 = func_0208a1d0(&p->unk_0C[0]);
    v24 = func_0208a1d0(&p->unk_20[0]);
    t = func_0208a1b0(&p->unk_0C[0], -1);
    v28 = func_0208a198(&p->unk_0C[0], -1);
    v2c = func_0208a1b0(&p->unk_20[0], -1);
    v30 = func_0208a198(&p->unk_20[0], -1);
    x = p->unk_38 + func_0208aef0(p);
    y = p->unk_3C + func_0208aeec(p);
    if (p->unk_41) {
        func_02088df8(0, v20, x + t, y + v28, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(0, v24, x + v2c, y + v30, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    } else {
        func_02088df8(1, v20, x + t, y + v28, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(1, v24, x + v2c, y + v30, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void func_0208a2b8(void *param)
{
    if (*(int *) ((char *) param + 0x34) != 0) {
        func_0208a0c8((char *) param + 0xc);
        func_0208a0c8((char *) param + 0x20);
    }
}

void func_0208a2b0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (64))) + (0)) = 1;
}

void func_0208a2a8(UnkStruct_0208a2a8 *p, unsigned long a, unsigned long b)
{
    p->a = a;
    p->b = b;
}
