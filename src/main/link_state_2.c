/* link_state_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6b88 @ 0x020a6b88, 0x7c bytes, Thumb
 * func_020a6b38 @ 0x020a6b38, 0x50 bytes, Thumb
 * func_020a6a74 @ 0x020a6a74, 0xc4 bytes, Thumb
 * func_020a6998 @ 0x020a6998, 0xda bytes, Thumb
 */

#include "types.h"

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020a7754(void *);
extern void *func_020a7758(void *);
extern void func_020a7718(void *);
extern int func_020a771c(void *);
extern void func_020a76e4(void *);
extern void *func_020a76e8(void *);
extern void func_020a77c8(void *);
extern int func_020a77cc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020a772c(u8 *p);
extern void func_020a76f8(u8 *p);
extern void func_020a76d0(u8 *p);
extern void func_020a7768(u8 *p);
extern void func_020a5bac(u8 *self, int idx);
extern void func_020a635c(u8 *self, int idx, int flag);
extern void func_020a617c(u8 *self, int idx, int flag);
extern int func_020a6364(u8 *self);
extern void func_020a6368(u8 *self, int flag);
extern int func_020a6338(u8 *self);
extern void func_020a633c(u8 *self, int flag);
extern int func_020a6230(u8 *self);
extern void func_020a6238(u8 *self, int flag);
extern int func_020a6284(u8 *self);
extern void func_020a6288(u8 *self, int flag);
extern int func_020a627c(u8 *self);
extern void func_020a6280(u8 *self, int flag);
extern int func_020a628c(u8 *self);
extern void func_020a6290(u8 *self, int flag);
extern void func_020a5c00(char *);
extern void func_020a5be8(char *);
extern void func_020a5bd0(char *);
extern void func_020a5b98(char *);
extern void func_020a5748(char *, int);
extern void func_020a6160(char *);
extern void func_020a6340(char *);
extern void func_020a6688(char *, int);
extern void func_020a6248(char *, int);
extern void func_020a5c30(char *, int);
extern void func_020a6694(char *, int);
extern void func_020a5738(char *, int);
extern void func_020a5728(char *, int);
extern void func_020a5718(char *, int);

void func_020a6998(char *self);

void *func_020a6b88(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 4, 3, (((void (*)(void *)) func_020a7758)), (void (*)(void *)) func_020a7754);
    __cxa_vec_ctor((void *) ((char *) obj + 0xc), 4, 8, (((void (*)(void *)) func_020a771c)),
                   (void (*)(void *)) func_020a7718);
    __cxa_vec_ctor((void *) ((char *) obj + 0x2c), 4, 4, (((void (*)(void *)) func_020a76e8)),
                   (void (*)(void *)) func_020a76e4);
    __cxa_vec_ctor((void *) ((char *) obj + 0x3c), 4, 8, (((void (*)(void *)) func_020a77cc)),
                   (void (*)(void *)) func_020a77c8);
    func_020a6998((char *) obj);
    return obj;
}

void *func_020a6b38(void *self)
{
    __cxa_vec_cleanup((void *) ((char *) self + 0x3c), 4, 8, (void (*)(void *)) func_020a77c8);
    __cxa_vec_cleanup((void *) ((char *) self + 0x2c), 4, 4, (void (*)(void *)) func_020a76e4);
    __cxa_vec_cleanup((void *) ((char *) self + 0xc), 4, 8, (void (*)(void *)) func_020a7718);
    __cxa_vec_cleanup((void *) (self), 4, 3, (void (*)(void *)) func_020a7754);
    return self;
}

void func_020a6a74(u8 *self, int idx)
{
    int off8;

    func_020a772c(self + 3 * idx);

    off8 = idx * 8;
    func_020a76f8(self + 0xc + off8);

    func_020a76d0(self + 0x2c + idx * 4);

    func_020a7768(self + 0x3c + off8);

    func_020a5bac(self, idx);
    func_020a635c(self, idx, 0);

    if (idx != 0) {
        func_020a617c(self, idx, 7);
    }

    if (idx == func_020a6364(self)) {
        func_020a6368(self, 4);
    }
    if (idx == func_020a6338(self)) {
        func_020a633c(self, 4);
    }
    if (idx == func_020a6230(self)) {
        func_020a6238(self, 4);
    }
    if (idx == func_020a6284(self)) {
        func_020a6288(self, 4);
    }
    if (idx == func_020a627c(self)) {
        func_020a6280(self, 4);
    }
    if (idx == func_020a628c(self)) {
        func_020a6290(self, 4);
    }
}

void func_020a6998(char *self)
{
    int n = 3;
    int i;
    for (i = n; i >= 0; i--) {
        func_020a772c((u8 *) (self + i * n));
        func_020a76f8((u8 *) (self + 0xc + i * 8));
        func_020a76d0((u8 *) (self + 0x2c + i * 4));
        func_020a7768((u8 *) (self + 0x3c + i * 8));
    }
    func_020a5c00(self);
    func_020a5be8(self);
    func_020a5bd0(self);
    func_020a5b98(self);
    func_020a5748(self, 0);
    func_020a6160(self);
    func_020a6368((u8 *) self, 4);
    func_020a6340(self);
    func_020a633c((u8 *) self, 4);
    func_020a6688(self, 16);
    func_020a6288((u8 *) self, 4);
    func_020a6280((u8 *) self, 4);
    func_020a6290((u8 *) self, 4);
    func_020a6248(self, 0);
    func_020a6238((u8 *) self, 4);
    func_020a5c30(self, 4);
    func_020a6694(self, 0);
    func_020a5738(self, 0);
    func_020a5728(self, 4);
    func_020a5718(self, 0);
}
