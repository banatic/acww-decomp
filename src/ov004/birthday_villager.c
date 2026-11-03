/* birthday_villager: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221c084 @ 0x0221c084, 0x4 bytes, Thumb
 * func_ov004_0221c080 @ 0x0221c080, 0x2 bytes, Thumb
 * func_ov004_0221c07c @ 0x0221c07c, 0x4 bytes, Thumb
 * func_ov004_0221c078 @ 0x0221c078, 0x2 bytes, Thumb
 * func_ov004_0221c074 @ 0x0221c074, 0x4 bytes, Thumb
 * func_ov004_0221c040 @ 0x0221c040, 0x34 bytes, Thumb
 * func_ov004_0221c034 @ 0x0221c034, 0xc bytes, Thumb
 * func_ov004_0221c020 @ 0x0221c020, 0x14 bytes, Thumb
 * func_ov004_0221c008 @ 0x0221c008, 0x18 bytes, Thumb
 * func_ov004_0221bfd4 @ 0x0221bfd4, 0x34 bytes, Thumb
 * func_ov004_0221bfa4 @ 0x0221bfa4, 0x30 bytes, Thumb
 * func_ov004_0221bf84 @ 0x0221bf84, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    char pad_04[0x8a0 - 4];
    void *unk_8A0;
} UnkStruct_0221bfa4;

struct _Obj {
    void *vtbl;
};

extern int func_020644cc(int);
extern void func_0206844c(int h, u8 *p, int k);
extern int func_ov004_0221c844(void *self, int a);
extern void *func_0202de4c(void *);
extern void *func_0202e5e0(void *argument0);
extern void func_020edf54(unsigned int argument0);
extern void *data_ov004_02253674;
extern char data_ov004_022535e4;
extern void func_020edb3c(void *);

int func_ov004_0221c084(void *callbackObject)
{
    return 1;
}

void func_ov004_0221c080(void *callbackObject) {}

int func_ov004_0221c07c(void *callbackObject)
{
    return 1;
}

void func_ov004_0221c078(void *callbackObject) {}

int func_ov004_0221c074(void *callbackObject)
{
    return 1;
}

void func_ov004_0221c040(char *self)
{
    u8 m;
    m = (u8) (func_020644cc(2) + 0x11);
    func_0206844c(*(int *) (self + 0x8e0), &m, 0);
    func_ov004_0221c844(self, 6);
}

void *func_ov004_0221c034(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x89c) = 0x1;
    return self;
}

int func_ov004_0221c020(unsigned char *p)
{
    if (p[0x89c] != 0) {
        return 0;
    }
    return 1;
}

void *func_ov004_0221c008(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_022535e4);
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_0221bfd4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02253674;
    *(void **) (self + 0x8a0) = ((void * *) &data_ov004_022535e4);
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    func_020edf54((unsigned int) (self));
    return self;
}

void *func_ov004_0221bfa4(UnkStruct_0221bfa4 *obj)
{
    obj->unk_00 = ((char *) &data_ov004_02253674);
    obj->unk_8A0 = &data_ov004_022535e4;
    func_0202de4c((void *) &obj->unk_8A0);
    func_0202e5e0(obj);
    return obj;
}

void *func_ov004_0221bf84(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022535e4;
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
