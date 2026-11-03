/* popup: 11 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02207e40 @ 0x02207e40, 0x40 bytes, Thumb
 * func_ov002_02207e28 @ 0x02207e28, 0x18 bytes, Thumb
 * func_ov002_02207e08 @ 0x02207e08, 0x20 bytes, Thumb
 * func_ov002_02207d5c @ 0x02207d5c, 0xac bytes, Thumb
 * func_ov002_02207d24 @ 0x02207d24, 0x36 bytes, Thumb
 * func_ov002_02207d00 @ 0x02207d00, 0x22 bytes, Thumb
 * func_ov002_02207cf8 @ 0x02207cf8, 0x8 bytes, Thumb
 * func_ov002_02207cf0 @ 0x02207cf0, 0x8 bytes, Thumb
 * func_ov002_02207cec @ 0x02207cec, 0x4 bytes, Thumb
 * func_ov002_02207ce4 @ 0x02207ce4, 0x6 bytes, Thumb
 * func_ov002_02207cc0 @ 0x02207cc0, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    char pad_04[0xc8];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_02207e40;

typedef struct UnkStruct_02207d5c {
    char pad_00[0xcc];
    u8 unk_CC;
    char pad_CD;
    u8 unk_CE;
} UnkStruct_02207d5c;

typedef struct {
    unsigned char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char pad_CD;
    unsigned char unk_CE;
} UnkStruct_02207d24;

struct UnkStruct_02207d00 {
    char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char unk_CD;
    unsigned char unk_CE;
};

typedef struct {
    unsigned char pad_00[206];
    unsigned char unk_CE;
} UnkStruct_02207ce4;

extern void *func_0208ade8(void *p, int n);
extern void func_0208aa38(void *p, int n);
extern void func_0208aa40(void *p);
extern char data_ov002_0220baa8[];
extern void *func_0208ad24(void *a);
extern void func_020edb3c(void *);
extern int func_0208a844(UnkStruct_02207d5c *self);
extern int func_0208a9ac(UnkStruct_02207d5c *self);
extern int func_0208a9c8(UnkStruct_02207d5c *self);
extern void func_0208aaa0(UnkStruct_02207d5c *self);

int func_ov002_02207d24(UnkStruct_02207d24 *obj, int flag);
void func_ov002_02207cf0(int p0);

void *func_ov002_02207e40(UnkStruct_02207e40 *p)
{
    unsigned char *q;

    func_0208ade8(p, 0);
    p->unk_00 = data_ov002_0220baa8;
    q = &p->b0;
    *q = 0;
    func_0208aa38(p, 1);
    func_0208aa40(p);
    q = &p->b1;
    *q = 0;
    q = &p->b2;
    *q = 0;
    return p;
}

void *func_ov002_02207e28(void *self)
{
    *(void **) self = (void *) ((char *) data_ov002_0220baa8);
    func_0208ad24(self);
    return self;
}

void *func_ov002_02207e08(void *obj)
{
    *(void **) obj = ((char *) data_ov002_0220baa8);
    func_0208ad24(obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov002_02207d5c(UnkStruct_02207d5c *self)
{
    int result = 0;

    if (self->unk_CE != 0) {
        self->unk_CE--;
        if (self->unk_CE == 0 && self->unk_CC == 3) {
            func_ov002_02207d24((UnkStruct_02207d24 *) self, result);
        }
    }

    switch (self->unk_CC) {
        case 1:
            if (func_0208a844(self) != 0) {
                func_0208a9ac(self);
            } else {
                result = 1;
                self->unk_CC = 2;
            }
            break;
        case 2:
            if (func_0208a9c8(self) != 0) {
                self->unk_CC = 3;
            }
            break;
        case 4:
            if (func_0208a844(self) == 0 || func_0208a9ac(self) != 0) {
                self->unk_CC = 0;
            }
            break;
    }

    func_0208aaa0(self);
    return result;
}

int func_ov002_02207d24(UnkStruct_02207d24 *obj, int flag)
{
    obj->unk_CE = 0;
    if (flag) {
        func_ov002_02207cf0((int) obj);
    }
    if (func_0208a844((UnkStruct_02207d5c *) obj) == 0) {
        obj->unk_CC = 0;
        return 1;
    } else {
        obj->unk_CC = 4;
        return 0;
    }
}

void func_ov002_02207d00(struct UnkStruct_02207d00 *s)
{
    s->unk_CE = 0;
    if (s->unk_CD != 0) {
        s->unk_CC = 1;
    }
    s->unk_CD = 0;
}

void func_ov002_02207cf8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (205))) + (0)) = 1;
}

void func_ov002_02207cf0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (205))) + (0)) = 0;
}

void func_ov002_02207cec(int *p0, int p1)
{
    p0[17] = p1;
}

void func_ov002_02207ce4(UnkStruct_02207ce4 *p, unsigned char v)
{
    p->unk_CE = v;
}

int func_ov002_02207cc0(int arg)
{
    if (func_0208a844((UnkStruct_02207d5c *) arg) == 2 || func_0208a844((UnkStruct_02207d5c *) arg) == 1) {
        return 1;
    } else {
        return 0;
    }
}
