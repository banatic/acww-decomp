/* cafe_props_6: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f160 @ 0x0222f160, 0x1c bytes, Thumb
 * func_ov004_0222f0e8 @ 0x0222f0e8, 0x78 bytes, Thumb
 * func_ov004_0222f08c @ 0x0222f08c, 0x5c bytes, Thumb
 * func_ov004_0222f028 @ 0x0222f028, 0x64 bytes, Thumb
 * func_ov004_0222ed60 @ 0x0222ed60, 0x2c8 bytes, Thumb
 */

#include "types.h"

#define BYTE(p, o) (*(u8 *) ((p) + (o)))
#define HALF(p, o) (*(u16 *) ((p) + (o)))
#define WORD(p, o) (*(u32 *) ((p) + (o)))

typedef struct {
    int x, y, z;
} Vec;

extern int func_020edf70(unsigned int size);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov004_0222c87c(void *);
extern void *func_020551e0(void *arg0);
extern void *func_02055210(void *arg0);
extern void func_ov004_0222c394(void *element);
extern void func_ov004_0222c398(void *arg0);
extern int func_ov004_0222c538(int arg0);
extern int func_ov004_0222c548(int arg0);
extern void *data_ov004_02254fc8;
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern char *data_ov004_02258310;
extern char data_ov004_02255030[];
extern char data_ov004_02255048[];
extern char data_ov004_02255064[];
extern char data_ov004_0225507c[];
extern char data_ov004_02255098[];
extern char data_ov004_022550b0[];
extern char data_ov004_022550cc[];
extern char data_ov004_022550e4[];
extern char data_ov004_02255100[];
extern char data_ov004_02255118[];
extern char data_ov004_02255134[];
extern char data_ov004_0225514c[];
extern void *data_021c9b24;
extern Vec data_ov004_02258318;
extern Vec data_ov004_02258330;
extern int func_ov004_0222c600(char *, char *, char *);
extern void func_ov004_0222de14(char *, int, char *, char *);
extern void *func_ov004_0222c3c4(char *, int);
extern int func_02055140(char *, void *);
extern void func_02055060(char *, void *, int, int, u16, u16);
extern void func_02055050(char *);
extern void func_ov004_0222dd5c(char *, int);
extern int func_ov004_0222e73c(char *, int);
extern void func_ov004_0222db14(char *, int, char *, char *, u8, int, u16, u16);

void *func_ov004_0222f0e8(char *self);

void func_ov004_0222f160(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0xf44)))) {
        func_ov004_0222f0e8((char *) conditionInput0);
    }
}

void *func_ov004_0222f0e8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02254fc8;
    __cxa_vec_ctor(self + 0x290, 0x9, 0xb8, ((void (*)(void *)) func_02055210), ((void (*)(void *)) func_020551e0));
    __cxa_vec_ctor(self + 0x908, 0x9, 0xa4, ((void (*)(void *)) func_ov004_0222c548),
                   ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_ctor(self + 0xecc, 0x9, 0x4, ((void (*)(void *)) func_ov004_0222c398), ((void (*)(void *)) func_ov004_0222c394));
    return self;
}

void *func_ov004_0222f08c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254fc8;
    __cxa_vec_cleanup(self + 0xecc, 0x9, 0x4, ((void (*)(void *)) func_ov004_0222c394));
    __cxa_vec_cleanup(self + 0x908, 0x9, 0xa4, ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_cleanup(self + 0x290, 0x9, 0xb8, ((void (*)(void *)) func_020551e0));
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_0222f028(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254fc8;
    __cxa_vec_cleanup(self + 0xecc, 0x9, 0x4, ((void (*)(void *)) func_ov004_0222c394));
    __cxa_vec_cleanup(self + 0x908, 0x9, 0xa4, ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_cleanup(self + 0x290, 0x9, 0xb8, ((void (*)(void *)) func_020551e0));
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}

int func_ov004_0222ed60(char *self)
{
    u8 i;
    data_ov004_02258310 = self;
    func_ov004_0222c600(self, data_ov004_02255030, data_ov004_02255048);
    func_ov004_0222de14(self, 0, data_ov004_02255064, data_ov004_0225507c);
    func_ov004_0222de14(self, 1, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 2, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 3, data_ov004_02255100, data_ov004_02255118);
    func_ov004_0222de14(self, 4, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 5, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 6, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 7, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 8, data_ov004_02255134, data_ov004_0225514c);
    if (func_ov004_0222c3c4(self + 0x1a4, 0)) {
        if (func_02055140(self + 0xec, data_021c9b24)) {
            func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 1, 0x1000, 0, 0);
            func_02055050(self + 0xec);
            WORD(self, 0x198) = 0;
        }
    }
    for (i = 0; i < 9; i++) {
        func_ov004_0222dd5c(self, i);
    }
    func_ov004_0222e73c(self, 0);
    BYTE(self, 0xef3) = 1;
    func_ov004_0222db14(self, 8, self + 0x570, self + 0xb98, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 6, self + 0x628, self + 0xc3c, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 8, self + 0x6e0, self + 0xce0, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 6, self + 0x798, self + 0xd84, 0, 0x1000, 0, 0);
    WORD(self, 0xf1c) = data_ov004_02258318.x;
    WORD(self, 0xf20) = data_ov004_02258318.y;
    WORD(self, 0xf24) = data_ov004_02258318.z;
    WORD(self, 0xf28) = data_ov004_02258330.x;
    WORD(self, 0xf2c) = data_ov004_02258330.y;
    WORD(self, 0xf30) = data_ov004_02258330.z;
    HALF(self, 0xf34) = 0;
    HALF(self, 0xf36) = 0;
    WORD(self, 0x61c) = 0;
    WORD(self, 0x614) = (u16) (((WORD(self, 0x610) << 4) >> 16) - 1) << 12;
    WORD(self, 0x6d4) = 0;
    WORD(self, 0x6cc) = (u16) (((WORD(self, 0x6c8) << 4) >> 16) - 1) << 12;
    WORD(self, 0x78c) = 0;
    WORD(self, 0x784) = (u16) (((WORD(self, 0x780) << 4) >> 16) - 1) << 12;
    WORD(self, 0x844) = 0;
    WORD(self, 0x83c) = (u16) (((WORD(self, 0x838) << 4) >> 16) - 1) << 12;
    WORD(self, 0xf38) = -1;
    WORD(self, 0xf3c) = -1;
    WORD(self, 0xf40) = -1;
    return 1;
}
