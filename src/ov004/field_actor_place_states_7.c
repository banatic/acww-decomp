/* field_actor_place_states_7: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b88c @ 0x0222b88c, 0x30 bytes, Thumb
 * func_ov004_0222b85c @ 0x0222b85c, 0x30 bytes, Thumb
 * func_ov004_0222b814 @ 0x0222b814, 0x48 bytes, Thumb
 * func_ov004_0222b7e4 @ 0x0222b7e4, 0x30 bytes, Thumb
 * func_ov004_0222b708 @ 0x0222b708, 0xdc bytes, Thumb
 * func_ov004_0222b6ec @ 0x0222b6ec, 0x1a bytes, Thumb
 * func_ov004_0222b6e8 @ 0x0222b6e8, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_0222b85c;

typedef struct {
    int a, b;
} UnkStruct_0222b7e4;

typedef struct {
    unsigned short low : 7, middle : 4, high : 5;
} Packed;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b6e8;

extern void func_ov004_0222b9b4(void *, void *);
extern int func_ov004_0222b9d4(void *, int, int, int, int);
extern void func_020110a0(void *object, short *values);
extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int a);
extern int func_0200f328(void *self, int a);
extern int func_02073908(int a, int b);
extern void func_02051e0c(void);
extern int data_020ccf94;
extern int func_020310c8(int value);
extern void func_02010d28(void *, void *);
extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern int func_0200c3b0(void *, int, int, int);
extern unsigned short *func_02096274(void);
extern void *func_02011368(void *);
extern short func_020997a8(void *);
extern unsigned short *func_0209627c(void);
extern int func_0200f86c(void *);
extern unsigned short *func_0209d358(unsigned short, unsigned short);
extern int func_020112bc(void *);
extern unsigned char *func_0209626c(void);
extern int func_0200d4e8(void *, int, int, int);

void func_ov004_0222b88c(char *self, int a1)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    func_ov004_0222b9b4(self + 0x8f0, frame);
    func_ov004_0222b9d4(self, *(u8 *) (frame), 0x0, 0x6, a1);
    return;
}

void func_ov004_0222b85c(u8 *self, int stateId)
{
    UnkStruct_0222b85c *q = (UnkStruct_0222b85c *) (self + 0x7d4);
    UnkStruct_0222b85c *d = (UnkStruct_0222b85c *) (self + 0x5c);
    d->a = q->a;
    d->c = q->b;
    func_020110a0(self, (short *) (&q->c));
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
}

void func_ov004_0222b814(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 0x15) != 0) {
        func_0200f328(self, 0x4c6);
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            func_02051e0c();
        }
    }
}

void func_ov004_0222b7e4(u8 *self)
{
    int p[3];
    UnkStruct_0222b7e4 *q = (UnkStruct_0222b7e4 *) (self + 0x7d4);
    p[0] = q->a;
    p[1] = func_020310c8(0);
    p[2] = q->b;
    func_02010d28(self, p);
}

void func_ov004_0222b708(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0)) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        if (self[0x7de]) {
            // Preserve the observed halfword store/reload before the copy.
            struct {
                volatile unsigned short value;
                unsigned short copy;
            } item;
            int mode, base;
            unsigned short *output, *first, *second;
            func_0200c3b0(self, 0, 5, -1);
            *func_02096274() = 0x4650;
            item.value = func_020997a8(func_02011368(self));
            item.copy = item.value;
            *func_0209627c() = item.copy;
            mode = func_0200f86c(self);
            output = func_0209d358(0, 80);
            base = func_020112bc(self);
            first = func_0209627c();
            second = func_0209627c();
            *output = base + 1000 * ((Packed *) first)->middle + 10 * ((Packed *) second)->high;
            if (!mode) {
                *func_0209626c() = 17;
            } else {
                *func_0209626c() = 0;
            }
        } else {
            func_0200d4e8(self, 0, 1, -1);
        }
    }
}

void func_ov004_0222b6ec(void *self)
{
    func_ov004_0222b814((char *) self);
    func_ov004_0222b7e4((u8 *) self);
    func_ov004_0222b708((unsigned char *) self);
}

void func_ov004_0222b6e8(UnkStruct_0222b6e8 *p, unsigned char v)
{
    p->unk_00 = v;
}
