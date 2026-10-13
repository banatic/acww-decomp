/* func_020677d0 @ 0x020677d0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern void func_020a8c1c(void *p);
extern void func_0207e008(void *p, void *q, int n);

int func_020677d0(UnkStruct_020677d0_2 *self)
{
    int r;
    void *res;

    res = self->obj->vtable->func(self->obj);
    r = 0;

    func_020a8c1c(&self->member);

    if (res != 0) {
        func_0207e008(res, &self->member, r);
        r = 1;
    }

    return r;
}
