/* furniture_model_2: 9 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220e4ec @ 0x0220e4ec, 0x18 bytes, Thumb
 * func_ov004_0220e4d4 @ 0x0220e4d4, 0x18 bytes, Thumb
 * func_ov004_0220e4b4 @ 0x0220e4b4, 0x20 bytes, Thumb
 * func_ov004_0220e4b0 @ 0x0220e4b0, 0x4 bytes, Thumb
 * func_ov004_0220e474 @ 0x0220e474, 0x3c bytes, Thumb
 * func_ov004_0220e458 @ 0x0220e458, 0x1a bytes, Thumb
 * func_ov004_0220e448 @ 0x0220e448, 0xe bytes, Thumb
 * func_ov004_0220e41c @ 0x0220e41c, 0x2c bytes, Thumb
 * func_ov004_0220e3f0 @ 0x0220e3f0, 0x2c bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

typedef struct {
    unsigned char pad_00[24];
    unsigned long unk_18;
} UnkStruct_0220e4b0;

extern void func_020565ec(void *arg);
extern int data_ov004_0224fe44;
extern void *func_02056578(void *);
extern void func_020edb3c(void *);
extern void *func_02055b00(void *);
extern void func_ov004_0220da54(void *);
extern void func_02055af4(void *);
extern void func_ov004_0220da50(void *);
extern int func_02064328(void *, void *, int, int, int);
extern void *data_ov004_0224fffc;
extern void *data_ov004_02256e7c;
extern void *data_ov004_0224ffe4;
extern void *data_ov004_02256ea4;

void *func_ov004_0220e4ec(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov004_0224fe44;
    return arg;
}

void *func_ov004_0220e4d4(void *arg)
{
    *((void **) arg) = &data_ov004_0224fe44;
    func_02056578(arg);
    return arg;
}

void *func_ov004_0220e4b4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_0224fe44);
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}

unsigned long func_ov004_0220e4b0(UnkStruct_0220e4b0 *p)
{
    return p->unk_18;
}

void *func_ov004_0220e474(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055b00(self + 0x10);
    func_ov004_0220da54(self + 0x44);
    *(u16 *) (self + 0x70) = 0xfff1;
    *(void **) (self) = 0x0;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    *(u16 *) (self + 0x70) = 0xfff1;
    *(u8 *) (self + 0x72) = 0x0;
    return self;
}

void *func_ov004_0220e458(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220da50(self + 0x44);
    func_02055af4(self + 0x10);
    return self;
}

int func_ov004_0220e448(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0xc) != 0x0) {
        return 0x1;
    }
    return 0x0;
}

void *func_ov004_0220e41c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_02064328(&data_ov004_02256e7c, &data_ov004_0224fffc, (a1 >> 8), ((a1 & 0xff) >> 4), a1);
    return &data_ov004_02256e7c;
}

void *func_ov004_0220e3f0(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_02064328(&data_ov004_02256ea4, &data_ov004_0224ffe4, (a1 >> 8), ((a1 & 0xff) >> 4), a1);
    return &data_ov004_02256ea4;
}
