/* room_pushes: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c908 @ 0x0223c908, 0x4a bytes, Thumb
 * func_ov004_0223c8b4 @ 0x0223c8b4, 0x54 bytes, Thumb
 * func_ov004_0223c8a8 @ 0x0223c8a8, 0xc bytes, Thumb
 * func_ov004_0223c86c @ 0x0223c86c, 0x3a bytes, Thumb
 * func_ov004_0223c85c @ 0x0223c85c, 0x10 bytes, Thumb
 * func_ov004_0223c820 @ 0x0223c820, 0x3a bytes, Thumb
 * func_ov004_0223c7f4 @ 0x0223c7f4, 0x2c bytes, Thumb
 * func_ov004_0223c7d8 @ 0x0223c7d8, 0x1c bytes, Thumb
 * func_ov004_0223c7b8 @ 0x0223c7b8, 0x1e bytes, Thumb
 * func_ov004_0223c758 @ 0x0223c758, 0x5e bytes, Thumb
 * func_ov004_0223c72c @ 0x0223c72c, 0x2c bytes, Thumb
 * func_ov004_0223c700 @ 0x0223c700, 0x2c bytes, Thumb
 */

#include "types.h"

#define g_00000020 (*(int *) 0x00002000)
#define g_x0 (*(int *) 0xffff8000)

typedef struct {
    long a, b, c;
} UnkStruct_0223c8b4;

typedef struct {
    long x, y, z;
} UnkStruct_0223c758;

extern int func_ov004_0223cb18(void *);
extern int func_ov004_0220ebd4(void *, int);
extern unsigned long data_ov004_022595dc;
extern UnkStruct_0223c8b4 data_ov004_02259628;
extern int data_ov004_0225961c;
extern void func_020012dc(void *object);
extern void __register_global_object(void *, void *destructor, void *);
extern void func_020ea6e0(void *, int);
extern int func_ov004_0220cefc();
extern int func_ov004_0223ca6c(char *argument0, int argument1);
extern int func_ov004_0223cadc(char *argument0, int argument1);
extern int func_ov004_0220ce5c();
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void func_ov004_0223cbe0(void *element);
extern void func_ov004_0223cbe4(void *element);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0223cbb8(char *argument0);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, long);
extern int func_ov004_0220fd8c(char *self);
extern void func_ov004_0223cb60(void *, long, UnkStruct_0223c758 *, UnkStruct_0223c758 *, long, UnkStruct_0223c758 *,
                                UnkStruct_0223c758 *, short, long);
extern int func_ov004_0223d348(void);
extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_020b65c4(void);

UnkStruct_0223c8b4 *func_ov004_0223c8b4(void *unused, int p);
void func_ov004_0223c7b8(char *self);

int func_ov004_0223c908(void *self, int y)
{
    void *a = (void *) func_ov004_0223cadc((char *) self, 0);
    void *b = (void *) func_ov004_0223ca6c((char *) self, 0);
    if (a != 0 && b != 0) {
        return func_ov004_0220ebd4(b, (int) func_ov004_0223c8b4(self, (short) ((short) (y + func_ov004_0223cb18(a)))));
    }
    return 0;
}

// 0x20 is loaded from the literal pool, so it is written as the address of g_00000020.
// The destructor of the local static object is registered with __register_global_object.
UnkStruct_0223c8b4 *func_ov004_0223c8b4(void *unused, int p)
{
    if (!(data_ov004_022595dc & 1)) {
        __register_global_object(&data_ov004_02259628, ((void *) &func_020012dc), &data_ov004_0225961c);
        data_ov004_022595dc |= 1;
    }
    data_ov004_02259628.a = 0;
    data_ov004_02259628.b = 0;
    data_ov004_02259628.c = (long) &g_00000020;
    func_020ea6e0(&data_ov004_02259628, p);
    return &data_ov004_02259628;
}

int func_ov004_0223c8a8(int a)
{
    return func_ov004_0223c908((void *) a, 0);
}

int func_ov004_0223c86c(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc(self, 0x0);
    v2 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0 && v2 != 0x0) {
        return func_ov004_0220cefc(v2, func_ov004_0223cb18((void *) (v1)));
    }
    return 0x0;
}

int func_ov004_0223c85c(int p0)
{
    return func_ov004_0223c908((void *) p0, (int) &g_x0);
}

int func_ov004_0223c820(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc(self, 0x0);
    v2 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0 && v2 != 0x0) {
        return func_ov004_0220ce5c(v2, func_ov004_0223cb18((void *) (v1)));
    }
    return 0x0;
}

void *func_ov004_0223c7f4(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x2, 0x40, ((void (*)(void *)) func_ov004_0223cbe4), ((void (*)(void *)) func_ov004_0223cbe0));
    func_ov004_0223c7b8((char *) self);
    return self;
}

void *func_ov004_0223c7d8(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0x2, 0x40, ((void (*)(void *)) func_ov004_0223cbe0));
    return self;
}

void func_ov004_0223c7b8(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x2; i++) {
        func_ov004_0223cbb8(self + (i << 6));
    }
}

int func_ov004_0223c758(char *p0, long id, UnkStruct_0223c758 *b, UnkStruct_0223c758 *c, long e, UnkStruct_0223c758 *f,
                        UnkStruct_0223c758 *g, short h, long i)
{
    void *selected;
    if (id != -1) {
        if ((selected = func_ov004_0223cd58(func_ov004_0223ce84(), id)) != 0) {
            func_ov004_0223cb60(p0 + ((func_ov004_0220fd8c((char *) selected) & 1) << 6), id, b, c, e, f, g, h, i);
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_ov004_0223c72c(void)
{
    if (func_ov004_0223d348() != 0) {
        return 0;
    }
    if (func_020b67d4() != 0 || func_020b6680() != 0) {
        return 1;
    }
    return 0;
}

int func_ov004_0223c700(void)
{
    int v;
    if (func_ov004_0223c72c() != 0) {
        return 1;
    }
    v = func_020b65c4();
    switch (v) {
        case 0x1f:
        case 0x21:
        case 0x22:
            return 1;
    }
    return 0;
}
