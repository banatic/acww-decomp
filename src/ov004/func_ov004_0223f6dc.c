/* func_ov004_0223f6dc @ 0x0223f6dc, 0x2ec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define BYTE(p, o) (*(u8 *) ((p) + (o)))
#define SBYTE(p, o) (*(signed char *) ((p) + (o)))
#define PTR(p, o) (*(void **) ((p) + (o)))
#define WORD(p, o) (*(int *) ((p) + (o)))
extern char data_ov004_022565b4[], data_ov004_022565c8[], data_ov004_022565dc[], data_ov004_022565f0[];
extern char data_ov004_02256604[], data_ov004_02256618[], data_ov004_0225662c[], data_ov004_02256640[], data_ov004_02256654[],
    data_ov004_02256668[];
extern char data_ov004_0225667c[], data_ov004_02256688[], data_ov004_02256694[], data_ov004_022566a0[];
extern u8 data_ov004_02256308[];
extern void *data_021fbe94;
extern void (*data_ov004_022563ec[])(char *);
extern int data_ov004_022563f0[];
extern void *func_0209d238(void *, void *);
extern char *func_02137550(char *, int);
extern void func_02064328(char *, const char *, ...);
extern int func_02064858(char *);
extern u8 func_0209d0ac(void *, void *, char *);
extern void *func_0209d088(void *);
extern int func_02055f2c(void *, void *, int);
extern void *func_0209d324(void *);
extern void *func_02064b2c(char *, void *, int, int);
extern void *NNS_G3dGetVisAnmSet(void *);
extern void *NNS_G3dGetJntAnmSet(void *);
extern void *NNS_G3dGetTexSRTAnmSet(void *);
extern void *func_02107cf0(void *, int), *func_02107b44(void *, int), *func_02107bbc(void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, void *, int, int, unsigned short, unsigned short);
extern int func_02055050(void *);
extern int func_0205650c(void *, void *, void *);
extern void func_02056478(void *, void *, int, int, unsigned short);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);
extern int func_0200430c(void *);
void func_ov004_0223f6dc(char *self, char *object)
{
    void *animation, *pool, *heap;
    char *resource, *model;
    u8 *flags;
    void *texture, *file;
    int kind, success, speed;
    char name[17], path[23], extra[33];
    pool = func_0209d238(self + 0x180, object + 0x284);
    resource = object + 0x288;
    func_02137550(name, 17);
    func_02137550(path, 23);
    kind = SBYTE(object, 0x196);
    if (kind == 0x25 && !BYTE(object, 0x22)) {
        func_02064328(name, data_ov004_022565b4);
        data_ov004_02256308[kind * 4] = 1;
    } else if (kind == 0x18) {
        func_02064328(name, data_ov004_022565c8, 60);
    } else if (kind == 0x23) {
        func_02064328(name, data_ov004_022565dc);
    } else if (kind == 0x38) {
        func_02064328(name, data_ov004_022565f0);
    } else if (kind < 10) {
        func_02064328(name, data_ov004_02256604, kind);
    } else if (kind < 20) {
        func_02064328(name, data_ov004_02256618, kind);
    } else if (kind < 30) {
        func_02064328(name, data_ov004_0225662c, kind);
    } else if (kind < 40) {
        func_02064328(name, data_ov004_02256640, kind);
    } else if (kind < 50) {
        func_02064328(name, data_ov004_02256654, kind);
    } else {
        func_02064328(name, data_ov004_02256668, kind);
    }
    func_02064328(path, data_ov004_0225667c, name);
    if (!func_02064858(path)) {
        return;
    }
    if (!func_0209d0ac(resource, pool, path)) {
        return;
    }
    model = object + 0xb0;
    func_02055f2c(model, func_0209d088(resource), 0);
    flags = &data_ov004_02256308[kind * 4];
    if (*flags) {
        func_02064328(path, data_ov004_02256688, name);
    } else {
        func_02064328(path, data_ov004_02256694, name);
    }
    if (!func_02064858(path)) {
        return;
    }
    heap = func_0209d324(pool);
    if (kind == 0x38) {
        PTR(self, 0x19c) = func_02064b2c(path, data_021fbe94, 4, 0);
        file = PTR(self, 0x19c);
    } else if (kind == 0x23) {
        PTR(self, 0x198) = func_02064b2c(path, data_021fbe94, 4, 0);
        file = PTR(self, 0x198);
    } else {
        file = func_02064b2c(path, heap, 4, 0);
    }
    if (!file) {
        return;
    }
    success = 1;
    if (*flags) {
        animation = func_02107cf0(NNS_G3dGetVisAnmSet(file), 0);
    } else {
        animation = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    }
    if (func_02055140(model, heap)) {
        speed = 0x1000;
        if (kind == 0x35 || kind == 9) {
            speed = 0;
        }
        func_02055060(model, animation, 0, speed, 0, 0);
        func_02055050(model);
    }
    if (kind == 0x18) {
        func_02064328(extra, data_ov004_022566a0, 60);
        success = 0;
        if (func_02064858(extra)) {
            file = func_02064b2c(extra, heap, 4, 0);
            if (file) {
                texture = func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0);
                if (func_0205650c(object, PTR(model, 0x5c), heap)) {
                    func_02056478(object, texture, 0, 0x1000, 0);
                    func_020563dc(object, func_02055e00(model));
                    success = 1;
                }
            }
        }
    }
    if (success) {
        data_ov004_022563ec[kind * 2](object);
        func_0200430c(object + 0x24);
        WORD(object, 0x2d4) = data_ov004_022563f0[kind * 2];
        WORD(object, 0x198) = 2;
    }
}
