/* obj_020dd33c_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02059694 @ 0x02059694, 0x88 bytes, Thumb
 * func_0205967c @ 0x0205967c, 0x18 bytes, Thumb
 * func_02059674 @ 0x02059674, 0x6 bytes, Thumb
 * func_0205963c @ 0x0205963c, 0x36 bytes, Thumb
 * func_020595fc @ 0x020595fc, 0x40 bytes, Thumb
 * func_02059598 @ 0x02059598, 0x64 bytes, Thumb
 */

typedef struct UnkStruct_0205967c UnkStruct_0205967c;

typedef struct VTable VTable;

struct VTable {
    unsigned char pad_00[0x5C];
    void (*method)(UnkStruct_0205967c *this, int arg);
};

struct UnkStruct_0205967c {
    VTable *vtable;
};

struct UnkStruct_0205967c_2 {
    unsigned char pad_00[0xCC];
    UnkStruct_0205967c *inner;
};

typedef struct {
    unsigned char pad_00[217];
    unsigned char unk_D9;
} UnkStruct_02059674;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x8e - 0x68];
    short unk_8E;
} Target;

typedef struct {
    char pad_00[0xcc];
    Target *targets[2];
} UnkStruct_020595fc;

struct Data12 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct PtrType {
    unsigned char pad_00[12];
    unsigned short type;
};

extern void func_0205971c(void *p, int arg1, void *arg2, void *arg3, void *arg4);
extern void func_020597a8(void *p, void *arg1, void *arg2, void *arg3, void *arg4);
extern int func_0205996c(void *a, void *b, int c);
extern void func_020ea6e0(Vec *p, int v);
extern void VEC_Add(Vec *p, Vec *q, Vec *r);
extern struct Data12 data_020cbb10;
extern struct Data12 data_020cbb1c;
extern struct Data12 data_020cbb28;
extern struct Data12 data_020cbb04;

void func_02059694(unsigned char *p)
{
    unsigned short val;
    if ((unsigned int) p[0xc8] >= 0x0c) {
        return;
    }
    val = *(unsigned short *) (p + 0x50);
    if (val == 0xfff1) {
        return;
    }
    if ((unsigned int) p[0xd8] != 1) {
        return;
    }
    if (*(unsigned int *) (p + 0x54) == 2) {
        if ((unsigned int) val >= 0x1561 && (unsigned int) val <= 0x1564) {
            // do nothing
        } else if ((unsigned int) val >= 0x155f && (unsigned int) val <= 0x1560) {
            // do nothing
        } else {
            func_0205971c(p, 0x27, p + 0x60, p + 0xa8, p + 0xb4);
            return;
        }
    }
    func_020597a8(p, p + 0x50, p + 0x60, p + 0xa8, p + 0xb4);
}

void func_0205967c(struct UnkStruct_0205967c_2 *self, int arg)
{
    UnkStruct_0205967c *inner = self->inner;
    if (inner != 0) {
        inner->vtable->method(inner, arg);
    }
}

void func_02059674(UnkStruct_02059674 *p, unsigned char v)
{
    p->unk_D9 = v;
}

int func_0205963c(unsigned char *param0, unsigned char param1, void *param2)
{
    int ret = 0;
    if (param0[200] != 0) {
        if (param0[217] != 1) {
            if (func_0205996c(param0, param2, 0) == 1) {
                param0[88] = param1;
                ret = 1;
            }
        }
    }
    return ret;
}

void func_020595fc(UnkStruct_020595fc *base, Vec *dest, Vec *src, unsigned int idx)
{
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    if (idx < 2 && base->targets[idx] != 0) {
        func_020ea6e0(dest, base->targets[idx]->unk_8E);
        VEC_Add(dest, &base->targets[idx]->pos, dest);
    }
}

void func_02059598(void *dst, char *base, int index)
{
    unsigned short type;
    void *ptr;
    type = 0xd8;
    ptr = *(void **) (base + (index << 2) + 0xcc);
    if (ptr) {
        type = ((struct PtrType *) ptr)->type;
    }
    if (type == 0x6b) {
        *(struct Data12 *) dst = data_020cbb10;
    } else if (type == 0x6a) {
        *(struct Data12 *) dst = data_020cbb1c;
    } else if (type == 0x76) {
        *(struct Data12 *) dst = data_020cbb28;
    } else {
        *(struct Data12 *) dst = data_020cbb04;
    }
}
