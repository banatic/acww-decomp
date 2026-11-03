/* aquarium_objects: 57 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223a690 @ 0x0223a690, 0x1c bytes, Thumb
 * func_ov004_0223a5e4 @ 0x0223a5e4, 0xac bytes, Thumb
 * func_ov004_0223a594 @ 0x0223a594, 0x50 bytes, Thumb
 * func_ov004_0223a53c @ 0x0223a53c, 0x58 bytes, Thumb
 * func_ov004_0223a4ec @ 0x0223a4ec, 0x50 bytes, Thumb
 * func_ov004_0223a458 @ 0x0223a458, 0x94 bytes, Thumb
 * func_ov004_0223a3c4 @ 0x0223a3c4, 0x94 bytes, Thumb
 * func_ov004_0223a3ac @ 0x0223a3ac, 0x18 bytes, Thumb
 * func_ov004_0223a38c @ 0x0223a38c, 0x20 bytes, Thumb
 * func_ov004_0223a374 @ 0x0223a374, 0x18 bytes, Thumb
 * func_ov004_0223a31c @ 0x0223a31c, 0x58 bytes, Thumb
 * func_ov004_0223a304 @ 0x0223a304, 0x18 bytes, Thumb
 * func_ov004_0223a2e4 @ 0x0223a2e4, 0x20 bytes, Thumb
 * func_ov004_0223a2c0 @ 0x0223a2c0, 0x24 bytes, Thumb
 * func_ov004_0223a2a8 @ 0x0223a2a8, 0x18 bytes, Thumb
 * func_ov004_0223a288 @ 0x0223a288, 0x20 bytes, Thumb
 * func_ov004_0223a25c @ 0x0223a25c, 0x2c bytes, Thumb
 * func_ov004_0223a244 @ 0x0223a244, 0x18 bytes, Thumb
 * func_ov004_0223a224 @ 0x0223a224, 0x20 bytes, Thumb
 * func_ov004_0223a1e8 @ 0x0223a1e8, 0x3c bytes, Thumb
 * func_ov004_0223a1d0 @ 0x0223a1d0, 0x18 bytes, Thumb
 * func_ov004_0223a1b0 @ 0x0223a1b0, 0x20 bytes, Thumb
 * func_ov004_0223a18c @ 0x0223a18c, 0x24 bytes, Thumb
 * func_ov004_0223a174 @ 0x0223a174, 0x18 bytes, Thumb
 * func_ov004_0223a154 @ 0x0223a154, 0x20 bytes, Thumb
 * func_ov004_0223a114 @ 0x0223a114, 0x40 bytes, Thumb
 * func_ov004_0223a0fc @ 0x0223a0fc, 0x18 bytes, Thumb
 * func_ov004_0223a0dc @ 0x0223a0dc, 0x20 bytes, Thumb
 * func_ov004_0223a09c @ 0x0223a09c, 0x40 bytes, Thumb
 * func_ov004_0223a084 @ 0x0223a084, 0x18 bytes, Thumb
 * func_ov004_0223a064 @ 0x0223a064, 0x20 bytes, Thumb
 * func_ov004_0223a040 @ 0x0223a040, 0x24 bytes, Thumb
 * func_ov004_0223a028 @ 0x0223a028, 0x18 bytes, Thumb
 * func_ov004_0223a008 @ 0x0223a008, 0x20 bytes, Thumb
 * func_ov004_02239fd4 @ 0x02239fd4, 0x34 bytes, Thumb
 * func_ov004_02239fbc @ 0x02239fbc, 0x18 bytes, Thumb
 * func_ov004_02239f9c @ 0x02239f9c, 0x20 bytes, Thumb
 * func_ov004_02239f68 @ 0x02239f68, 0x34 bytes, Thumb
 * func_ov004_02239f50 @ 0x02239f50, 0x18 bytes, Thumb
 * func_ov004_02239f30 @ 0x02239f30, 0x20 bytes, Thumb
 * func_ov004_02239eec @ 0x02239eec, 0x44 bytes, Thumb
 * func_ov004_02239ed4 @ 0x02239ed4, 0x18 bytes, Thumb
 * func_ov004_02239eb4 @ 0x02239eb4, 0x20 bytes, Thumb
 * func_ov004_02239e9c @ 0x02239e9c, 0x18 bytes, Thumb
 * func_ov004_02239e84 @ 0x02239e84, 0x18 bytes, Thumb
 * func_ov004_02239e64 @ 0x02239e64, 0x20 bytes, Thumb
 * func_ov004_02239e40 @ 0x02239e40, 0x24 bytes, Thumb
 * func_ov004_02239e28 @ 0x02239e28, 0x18 bytes, Thumb
 * func_ov004_02239e08 @ 0x02239e08, 0x20 bytes, Thumb
 * func_ov004_02239df0 @ 0x02239df0, 0x18 bytes, Thumb
 * func_ov004_02239dd8 @ 0x02239dd8, 0x18 bytes, Thumb
 * func_ov004_02239db8 @ 0x02239db8, 0x20 bytes, Thumb
 * func_ov004_02239da8 @ 0x02239da8, 0x10 bytes, Thumb
 * func_ov004_02239d34 @ 0x02239d34, 0x74 bytes, Thumb
 * func_ov004_02239cd4 @ 0x02239cd4, 0x60 bytes, Thumb
 * func_ov004_02239c6c @ 0x02239c6c, 0x68 bytes, Thumb
 * func_ov004_02239c5c @ 0x02239c5c, 0x10 bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

extern int func_020edf70(unsigned int size);
extern void *func_02054e54(void *argument0);
extern void func_0209d0a4(void *argument0);
extern void *func_0209d11c(void *argument0);
extern void func_0209d34c(unsigned short *argument0);
extern void __cxa_vec_ctor();
extern void *func_ov004_02239c40(char *argument0);
extern void func_020012dc(void *arg0);
extern void func_020012e8(void *arg0);
extern void *data_ov004_02255db4;
extern void *func_02054e18(void *);
extern int func_0209d104(void *);
extern void func_0209d340(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_02239c28(void *);
extern void func_020edb3c(void *);
extern void *data_ov004_02255ea4;
extern void *data_ov004_02255e14;
extern void *data_ov004_02255d84;
extern void *data_ov004_02255d6c;
extern void *data_0213efe8;
extern void *data_0213f020;
extern void *data_ov004_02255e74;
extern void *data_ov004_02255e44;
extern void *data_ov004_02255dfc;
extern void *data_ov004_02255de4;
extern void *data_ov004_02255e8c;
extern void *data_ov004_02255dcc;
extern void *data_ov004_02255d9c;
extern void *data_ov004_02255d54;
extern int data_ov004_02255d3c;
extern void *data_ov004_02255e5c;
extern int data_ov004_02255e2c;
extern void func_0209d2b8(void *);
extern void *func_020ee660(void *);
extern void *func_020b82d0(void *arg0);
extern void *func_020b82ec(void *arg0);
extern void *data_020da13c;
extern void *data_ov004_02255ebc;
extern void func_0209d2b4(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

void *func_ov004_02239d34(char *self);
int func_ov004_02239c5c(int arg);

void func_ov004_0223a690(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x810)))) {
        func_ov004_02239d34((char *) conditionInput0);
    }
}

void *func_ov004_0223a5e4(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    func_ov004_02239c40(self + 0x4);
    func_02054e54(self + 0x64);
    func_0209d34c((unsigned short *) (self + 0x166));
    func_0209d11c(self + 0x168);
    __cxa_vec_ctor(self + 0x1d0, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    *(int *) (self + 0x15c) = -0x1;
    *(void **) (self + 0x160) = 0x0;
    func_0209d0a4(self + 0x168);
    *(u8 *) (self + 0x1c6) = 0x0;
    *(u8 *) (self + 0x1c7) = 0x1;
    *(u8 *) (self + 0x1f1) = 0x0;
    *(u16 *) (self + 0x1c4) = 0x0;
    for (i = 0; i < 0x4; i++) {
        *(void **) (self + (i << 2) + 0x54) = 0x0;
    }
    return self;
}

void *func_ov004_0223a594(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    __cxa_vec_cleanup(self + 0x1d0, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_0209d104(self + 0x168);
    func_0209d340(self + 0x166);
    func_02054e18(self + 0x64);
    func_ov004_02239c28(self + 0x4);
    return self;
}

void *func_ov004_0223a53c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    __cxa_vec_cleanup(self + 0x1d0, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_0209d104(self + 0x168);
    func_0209d340(self + 0x166);
    func_02054e18(self + 0x64);
    func_ov004_02239c28(self + 0x4);
    func_020edb3c(self);
    return self;
}

void *func_ov004_0223a4ec(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    __cxa_vec_cleanup(self + 0x1d0, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_0209d104(self + 0x168);
    func_0209d340(self + 0x166);
    func_02054e18(self + 0x64);
    func_ov004_02239c28(self + 0x4);
    return self;
}

void *func_ov004_0223a458(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255ea4;
    *(u8 *) (self + 0x1ee) = 0x2;
    *(u8 *) (self + 0x1fe) = 0x2;
    *(u16 *) (self + 0x200) = 0x3;
    *(u8 *) (self + 0x1fc) = 0x0;
    *(void **) (self + 0x21c) = 0x0;
    *(u16 *) (self + 0x220) = 0x0;
    *(u8 *) (self + 0x1ca) = 0x0;
    *(int *) (self + 0x224) = 0x28;
    *(u8 *) (self + 0x22e) = 0x0;
    *(int *) (self + 0x1cc) = 0x3000;
    *(int *) (self + 0x228) = 0x1000;
    *(u8 *) (self + 0x1ef) = 0x0;
    *(u8 *) (self + 0x254) = 0x0;
    return self;
}

void *func_ov004_0223a3c4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255ea4;
    *(u8 *) (self + 0x1ee) = 0x2;
    *(u8 *) (self + 0x1fe) = 0x2;
    *(u16 *) (self + 0x200) = 0x3;
    *(u8 *) (self + 0x1fc) = 0x0;
    *(void **) (self + 0x21c) = 0x0;
    *(u16 *) (self + 0x220) = 0x0;
    *(u8 *) (self + 0x1ca) = 0x0;
    *(int *) (self + 0x224) = 0x28;
    *(u8 *) (self + 0x22e) = 0x0;
    *(int *) (self + 0x1cc) = 0x3000;
    *(int *) (self + 0x228) = 0x1000;
    *(u8 *) (self + 0x1ef) = 0x0;
    *(u8 *) (self + 0x254) = 0x0;
    return self;
}

void *func_ov004_0223a3ac(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255ea4);
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_0223a38c(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255ea4);
    func_ov004_0223a4ec((char *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a374(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255ea4);
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_0223a31c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255e14;
    *(u8 *) (self + 0x255) = 0x1;
    *(void **) (self + 0x21c) = 0x0;
    *(int *) (self + 0x20c) = 0x41;
    *(int *) (self + 0x278) = 0x14;
    *(int *) (self + 0x27c) = 0xccd;
    *(u8 *) (self + 0x284) = 0x0;
    return self;
}

void *func_ov004_0223a304(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255e14);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_0223a2e4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e14);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a2c0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255d84;
    *(u8 *) (self + 0x238) = 0x0;
    return self;
}

void *func_ov004_0223a2a8(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255d84);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_0223a288(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255d84);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a25c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255d6c;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x256) = 0x0;
    return self;
}

void *func_ov004_0223a244(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255d6c);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_0223a224(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255d6c);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a1e8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4((char *) self);
    *(void **) (self) = &data_ov004_02255e74;
    *(void **) (self + 0x1fc) = &data_0213efe8;
    *(void **) (self + 0x1fc) = &data_0213f020;
    *(u8 *) (self + 0x211) = 0x2;
    return self;
}

void *func_ov004_0223a1d0(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255e74);
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_0223a1b0(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e74);
    func_ov004_0223a4ec((char *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a18c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4((char *) self);
    *(void **) (self) = &data_ov004_02255e44;
    *(u8 *) (self + 0x20e) = 0x0;
    return self;
}

void *func_ov004_0223a174(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255e44);
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_0223a154(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e44);
    func_ov004_0223a4ec((char *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a114(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255dfc;
    *(u8 *) (self + 0x255) = 0x1;
    *(void **) (self + 0x21c) = 0x0;
    *(int *) (self + 0x20c) = 0x41;
    *(u8 *) (self + 0x270) = 0x0;
    return self;
}

void *func_ov004_0223a0fc(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255dfc);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_0223a0dc(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255dfc);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a09c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255de4;
    *(u8 *) (self + 0x255) = 0x1;
    *(void **) (self + 0x21c) = 0x0;
    *(int *) (self + 0x20c) = 0xa3;
    *(u8 *) (self + 0x264) = 0x0;
    return self;
}

void *func_ov004_0223a084(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255de4);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_0223a064(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255de4);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_0223a040(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4((char *) self);
    *(void **) (self) = &data_ov004_02255e8c;
    *(u8 *) (self + 0x21c) = 0x2;
    return self;
}

void *func_ov004_0223a028(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255e8c);
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_0223a008(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e8c);
    func_ov004_0223a4ec((char *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239fd4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255dcc;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x256) = 0x0;
    *(u8 *) (self + 0x258) = 0x0;
    return self;
}

void *func_ov004_02239fbc(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255dcc);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_02239f9c(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255dcc);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239f68(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255d9c;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x257) = 0x0;
    *(u8 *) (self + 0x259) = 0x0;
    return self;
}

void *func_ov004_02239f50(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255d9c);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_02239f30(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255d9c);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239eec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255d54;
    *(u8 *) (self + 0x258) = 0x0;
    *(u8 *) (self + 0x257) = 0x0;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x256) = 0x1;
    *(u8 *) (self + 0x259) = 0x0;
    return self;
}

void *func_ov004_02239ed4(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255d54);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_02239eb4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255d54);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239e9c(void *arg)
{
    func_ov004_0223a458((char *) arg);
    *(void **) arg = &data_ov004_02255d3c;
    return arg;
}

void *func_ov004_02239e84(void *arg)
{
    *((void **) arg) = &data_ov004_02255d3c;
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_02239e64(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255d3c);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239e40(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458((char *) self);
    *(void **) (self) = &data_ov004_02255e5c;
    *(u8 *) (self + 0x255) = 0x0;
    return self;
}

void *func_ov004_02239e28(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255e5c);
    func_ov004_0223a374(arg);
    return arg;
}

void *func_ov004_02239e08(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e5c);
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov004_02239df0(void *arg)
{
    func_ov004_0223a5e4((char *) arg);
    *(void **) arg = &data_ov004_02255e2c;
    return arg;
}

void *func_ov004_02239dd8(void *arg)
{
    *((void **) arg) = &data_ov004_02255e2c;
    func_ov004_0223a4ec((char *) arg);
    return arg;
}

void *func_ov004_02239db8(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255e2c);
    func_ov004_0223a4ec((char *) obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov004_02239da8(int arg)
{
    func_ov004_02239c40((char *) arg);
    return arg;
}

void *func_ov004_02239d34(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02255ebc;
    __cxa_vec_ctor(self + 0x50, 0x5, 0x64, ((void (*)(void *)) func_ov004_02239da8), ((void (*)(void *)) func_ov004_02239c5c));
    func_ov004_02239c40((char *) (self + 0x244));
    __cxa_vec_ctor(self + 0x2a8, 0x2, 0x2a8, ((void (*)(void *)) func_020b82ec), ((void (*)(void *)) func_020b82d0));
    func_0209d2b8(self + 0x7f8);
    return self;
}

void *func_ov004_02239cd4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ebc;
    func_0209d2b4(self + 0x7f8);
    __cxa_vec_cleanup(self + 0x2a8, 0x2, 0x2a8, ((void (*)(void *)) func_020b82d0));
    func_ov004_02239c28(self + 0x244);
    __cxa_vec_cleanup(self + 0x50, 0x5, 0x64, ((void (*)(void *)) func_ov004_02239c5c));
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_02239c6c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ebc;
    func_0209d2b4(self + 0x7f8);
    __cxa_vec_cleanup(self + 0x2a8, 0x2, 0x2a8, ((void (*)(void *)) func_020b82d0));
    func_ov004_02239c28(self + 0x244);
    __cxa_vec_cleanup(self + 0x50, 0x5, 0x64, ((void (*)(void *)) func_ov004_02239c5c));
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_02239c5c(int arg)
{
    func_ov004_02239c28((void *) arg);
    return arg;
}
