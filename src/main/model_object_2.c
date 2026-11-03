/* model_object_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020557a0 @ 0x020557a0, 0x24 bytes, Thumb
 * func_0205577c @ 0x0205577c, 0x24 bytes, Thumb
 * func_02055764 @ 0x02055764, 0x18 bytes, Thumb
 * func_02055744 @ 0x02055744, 0x20 bytes, Thumb
 * func_0205572c @ 0x0205572c, 0x18 bytes, Thumb
 * func_02055698 @ 0x02055698, 0x94 bytes, Thumb
 * func_020555dc @ 0x020555dc, 0xbc bytes, Thumb
 * func_020555c8 @ 0x020555c8, 0x14 bytes, Thumb
 * func_020555a4 @ 0x020555a4, 0x24 bytes, Thumb
 * func_0205556c @ 0x0205556c, 0x38 bytes, Thumb
 * func_020554ec @ 0x020554ec, 0x80 bytes, Thumb
 * func_020554b0 @ 0x020554b0, 0x3a bytes, Thumb
 * func_02055478 @ 0x02055478, 0x38 bytes, Thumb
 * func_02055454 @ 0x02055454, 0x24 bytes, Thumb
 * func_02055444 @ 0x02055444, 0x10 bytes, Thumb
 * func_02055438 @ 0x02055438, 0xc bytes, Thumb
 */

typedef struct UnkStruct_020557a0 UnkStruct_020557a0;

struct UnkStruct_020557a0 {
    int *unk_00;
    char pad_04[0x94];
    unsigned int unk_98;
};

struct UnkStruct_0205577c {
    void *unk_00;
    unsigned char pad_04[0x94];
    unsigned int unk_98;
};

struct UnkStruct_020555dc {
    unsigned char pad_00[0x5c];
    void *unk_5C;
    unsigned char pad_60[0x94 - 0x60];
    void *unk_94;
};

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x38];
    int unk_98;
} UnkStruct_0205556c;

typedef struct {
    char pad_00[0x5c];
    void *mdl;
} UnkStruct_020554ec;

typedef struct {
    char pad_00[0xe];
    unsigned short dictOff;
} Hdr;

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_020554ec_2;

typedef struct UnkStruct_020554b0 UnkStruct_020554b0;

struct UnkStruct_020554b0 {
    unsigned char unk_00[0x5c];
    void *unk_5C;
};

struct inner {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
};

struct outer {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    struct inner *inner_ptr;
    unsigned char pad_10[0x3c - 0x10];
    unsigned int unk_3C;
};

struct _func_02055444_struct {
    int *unk_00;
    int unk_04;
    int unk_08;
};

extern void *func_02056044(UnkStruct_020557a0 *);
extern void *func_02055ff4(void *self);
extern unsigned char data_020dd03c[];
extern void func_020edb3c(void *p);
extern int data_021fbe94;
extern int func_02064b2c(int, int, int, int);
extern void *func_02107828(int resource);
extern int func_021077e8(int);
extern int func_02056268(void *, int);
extern int func_020561fc(void *, int);
extern int func_02056064(int, int);
extern int NNS_G3dBindMdlPltt(int, int);
extern void func_020e993c(int, int);
extern void func_02055f6c(void *);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dForceBindMdlPltt(void *, void *, int, unsigned int);
extern int func_020562cc(int arg);
extern void *func_02072614(void);
extern void *func_02072630(void *a, int b, int c);
extern int NNS_G3dForceBindMdlTex(void *m, void *t, int a, int b);
extern int func_020e9948(int, int);
extern int func_02055f1c(void *);
extern unsigned char data_020dd04c[];

UnkStruct_020557a0 *func_020557a0(UnkStruct_020557a0 *obj)
{
    func_02056044(obj);
    obj->unk_00 = ((int *) data_020dd03c);
    obj->unk_98 = 0x4e554c4c;
    return obj;
}

struct UnkStruct_0205577c *func_0205577c(struct UnkStruct_0205577c *p)
{
    func_02056044((UnkStruct_020557a0 *) p);
    p->unk_00 = ((char *) data_020dd03c);
    p->unk_98 = 0x4e554c4c;
    return p;
}

void *func_02055764(void *self)
{
    *(void **) self = (void *) data_020dd03c;
    func_02055ff4(self);
    return self;
}

void *func_02055744(void *p)
{
    *(void **) p = (void *) data_020dd03c;
    func_02055ff4(p);
    func_020edb3c(p);
    return p;
}

void *func_0205572c(void *self)
{
    *(void **) self = (void *) data_020dd03c;
    func_02055ff4(self);
    return self;
}

int func_02055698(void *arg1, int arg2, int arg3, int arg4)
{
    int ret;
    int global_val;
    void *obj;
    int ext2;
    void *r7;
    unsigned short off;
    char *mid;
    int val;

    global_val = data_021fbe94;
    ret = func_02064b2c(arg2, global_val, -4, 0);
    if (ret == 0) {
        return 0;
    }

    obj = func_02107828(ret);
    off = *((unsigned short *) ((char *) obj + 0xe));
    mid = (char *) obj + off;
    val = *(int *) (mid + 0xc);
    r7 = (char *) obj + val;

    ext2 = func_021077e8(ret);

    if (arg3) {
        *(int *) ((char *) arg1 + 0x5c) = func_02056268(r7, arg3);
    } else {
        *(int *) ((char *) arg1 + 0x5c) = func_020561fc(r7, arg4);
    }

    if (ext2) {
        func_02056064(ext2, *(int *) ((char *) arg1 + 0x94));
        NNS_G3dBindMdlTex((void *) (*(int *) ((char *) arg1 + 0x5c)), (void *) ext2);
        NNS_G3dBindMdlPltt(*(int *) ((char *) arg1 + 0x5c), ext2);
    }

    func_020e993c(global_val, ret);
    func_02055f6c(arg1);

    return 1;
}

int func_020555dc(struct UnkStruct_020555dc *self, unsigned int a, void *b, void *c, void *d, unsigned int *e, int f,
                  unsigned int g)
{
    unsigned int local0;
    unsigned int local1;
    unsigned char *p, *obj;
    unsigned short off;
    unsigned int w;
    void *r;
    int i;

    local1 = (*(unsigned int *) &data_021fbe94);
    local0 = (unsigned int) func_02064b2c(a, local1, -4, 0);
    if (local0 == 0) {
        return 0;
    }

    p = (unsigned char *) func_02107828(local0);
    off = *(unsigned short *) (p + 0xe);
    w = *(unsigned int *) (p + off + 0xc);
    obj = p + w;

    if (b != 0) {
        self->unk_5C = (void *) func_02056268(obj, (int) b);
    } else {
        self->unk_5C = (void *) func_020561fc(obj, g);
    }

    if (c != 0) {
        NNS_G3dBindMdlTex(self->unk_5C, c);
    } else {
        r = (void *) func_021077e8(local0);
        if (r != 0) {
            func_02056064((int) r, (int) self->unk_94);
            NNS_G3dBindMdlTex(self->unk_5C, r);
        }
    }

    if (d != 0) {
        for (i = 0; i < f; i++) {
            NNS_G3dForceBindMdlPltt(self->unk_5C, d, i, e[i]);
        }
    }

    func_020e993c(local1, local0);
    func_02055f6c((void *) self);

    return 1;
}

int func_020555c8(int arg0, int arg1, int arg2)
{
    return func_02055698((void *) arg0, arg1, arg2, 0x4E554C4C);
}

int func_020555a4(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    int v1;
    int v2;
    int v3;
    int v4;

    v1 = a5;
    v2 = a6;
    v3 = a7;
    v4 = 0x4e554c4c;

    return func_020555dc((struct UnkStruct_020555dc *) a1, a2, (void *) a3, (void *) a4, (void *) v1, (unsigned int *) v2, v3, v4);
}

int func_0205556c(UnkStruct_0205556c *ptr, int arg2, int arg3)
{
    ptr->unk_5C = func_020562cc(arg2);
    if (ptr->unk_5C != 0) {
        func_02055f6c((void *) ptr);
        return 1;
    } else {
        ptr->unk_98 = arg2;
        return func_02055698((void *) ptr, arg3, 0, arg2);
    }
}

int func_020554ec(UnkStruct_020554ec *self, void *file, int a2, int a3)
{
    void *heap = (*(void * *) &data_021fbe94);
    Hdr *res;
    Hdr *h;
    void *tex;

    res = (Hdr *) func_02064b2c((int) file, (int) heap, -4, 0);
    if (res == 0) {
        return 0;
    }
    h = (Hdr *) func_02107828((int) res);
    self->mdl = (void *) func_020561fc((char *) h + ((UnkStruct_020554ec_2 *) ((char *) h + h->dictOff))->unk_0C, 0x4e554c4c);
    tex = func_02072630(func_02072614(), a2, a3);
    NNS_G3dForceBindMdlTex(self->mdl, tex, 0, 0);
    NNS_G3dForceBindMdlPltt(self->mdl, tex, 0, 0);
    func_020e993c((int) heap, (int) res);
    func_02055f6c((void *) self);
    return 1;
}

void func_020554b0(UnkStruct_020554b0 *that, void *arg2)
{
    char *list;
    char *node;
    void *other;
    unsigned short offset;
    unsigned int node_offset;

    list = (char *) func_02107828((int) arg2);
    offset = *(unsigned short *) (list + 0xe);
    node_offset = *(unsigned int *) (list + offset + 0xc);
    node = list + node_offset;
    other = (void *) func_021077e8((int) arg2);
    that->unk_5C = node;
    NNS_G3dBindMdlTex(that->unk_5C, other);
    NNS_G3dBindMdlPltt((int) that->unk_5C, (int) other);
    func_02055f6c((void *) that);
}

int func_02055478(struct outer *self, int flag)
{
    int offset;
    int result;

    offset = self->inner_ptr->unk_17 * 0x58;

    if (flag == 0) {
        flag = data_021fbe94;
    }

    result = func_020e9948(flag, offset);

    if (result == 0) {
        return 0;
    }

    self->unk_3C = result;
    self->unk_08 |= 1;
    return 1;
}

int func_02055454(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = 1;
    result = func_02055f1c((void *) param);
    r4 &= result;
    *(unsigned int *) (r5 + 0x98) = 0x4e554c4c;
    return r4;
}

void func_02055444(struct _func_02055444_struct *obj)
{
    obj->unk_00 = ((int *) data_020dd04c);
    obj->unk_04 = 0;
    obj->unk_08 = 0;
}

void func_02055438(void **pp)
{
    *pp = data_020dd04c;
}
