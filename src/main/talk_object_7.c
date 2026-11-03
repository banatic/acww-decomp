/* talk_object_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206780c @ 0x0206780c, 0x10 bytes, Thumb
 * func_020677d0 @ 0x020677d0, 0x3c bytes, Thumb
 * func_020677c0 @ 0x020677c0, 0x10 bytes, Thumb
 */

struct Vtbl;

typedef struct UnkStruct_020677d0 UnkStruct_020677d0;

typedef void *(*VFunc)(UnkStruct_020677d0 *);

struct Vtbl {
    unsigned char pad_00[0x68];
    VFunc func;
};

struct UnkStruct_020677d0 {
    struct Vtbl *vtable;
};

typedef struct UnkStruct_020677d0_2 {
    unsigned char pad_00[0x14a8];
    UnkStruct_020677d0 *obj;
    unsigned char pad_14AC[0x8fc];
    unsigned char member;
} UnkStruct_020677d0_2;

extern void func_020a8c1c(int param);
extern void func_0207e008(void *p, void *q, int n);

void func_0206780c(int param)
{
    func_020a8c1c(param + 0x1da8);
}

int func_020677d0(UnkStruct_020677d0_2 *self)
{
    int r;
    void *res;

    res = self->obj->vtable->func(self->obj);
    r = 0;

    func_020a8c1c((int) (&self->member));

    if (res != 0) {
        func_0207e008(res, &self->member, r);
        r = 1;
    }

    return r;
}

void func_020677c0(int r0)
{
    func_020a8c1c(r0 + 0x1e04);
}
