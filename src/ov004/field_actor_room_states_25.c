/* field_actor_room_states_25: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229c14 @ 0x02229c14, 0xe4 bytes, Thumb
 * func_ov004_02229bec @ 0x02229bec, 0x26 bytes, Thumb
 * func_ov004_02229bb4 @ 0x02229bb4, 0x36 bytes, Thumb
 * func_ov004_02229b94 @ 0x02229b94, 0x20 bytes, Thumb
 * func_ov004_02229b88 @ 0x02229b88, 0xc bytes, Thumb
 * func_ov004_02229aa4 @ 0x02229aa4, 0xe4 bytes, Thumb
 * func_ov004_02229a7c @ 0x02229a7c, 0x26 bytes, Thumb
 * func_ov004_02229a44 @ 0x02229a44, 0x36 bytes, Thumb
 * func_ov004_02229a3c @ 0x02229a3c, 0x6 bytes, Thumb
 * func_ov004_022299fc @ 0x022299fc, 0x40 bytes, Thumb
 * func_ov004_022299f8 @ 0x022299f8, 0x2 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022299fc {
    int a;
    int b;
    int c;
};

struct UnkStruct_022299fc_2 {
    u8 pad_00[0x5c];
    u8 head[0x8e - 0x5c];
    u8 body[0x7d4 - 0x8e];
    u8 out[4];
};

extern int func_02056f94(void *p);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void *func_ov004_0223cb10(void);
extern int func_ov004_0223c8a8(int);
extern int func_020b67d4(void);
extern int func_0200f328(void *self, int k);
extern int func_0200dc10(void *self);
extern int func_0200dc8c(void *self);
extern int func_02008258(void *self, int a);
extern int func_ov004_0222a23c(void *self, int a, int b, int c, int d);
extern int func_ov004_0223c86c(char *);
extern int func_0201100c(void *);
extern void func_02010f5c(void *);
extern void func_02010d64(void *);
extern int func_02010ca4(void *);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109a0(void *, int, int, unsigned short d);
extern int func_ov004_0223c85c(int);
extern int func_ov004_02229928(void *, int, int);
extern int func_ov004_0223c820(char *);
extern int data_ov004_02247780;
extern void func_0200fa1c(struct UnkStruct_022299fc *v, struct UnkStruct_022299fc_2 *self, void *a, void *b, void *c);

int func_ov004_02229a44(void *a0, int a1, int a2);

void func_ov004_02229c14(void *self)
{
    unsigned char fl;
    unsigned char *p;
    int r;

    if (func_02056f94((char *) self + 0x2d0) != 0) {
        if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
            fl = 0;
            if (func_ov004_0223c8a8((int) func_ov004_0223cb10()) == 0) {
                fl = 1;
            }
            if (func_020b67d4() == 0 || *(int *) ((char *) self + 0x800) != 0) {
                fl = (unsigned char) (fl | 2);
            }
            if (fl != 0) {
                p = (unsigned char *) ((char *) self + 0x7d4);
                if (*p == 0) {
                    *p = 1;
                    if (fl == 1) {
                        func_0200f328(self, 0x6d);
                    }
                }
                r = func_0200dc10(self);
                if (func_0200dc8c(self) > 0 && r == 0) {
                    return;
                }
                *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_ov004_02229a44(self, 6, -1);
                func_ov004_0223c86c((char *) func_ov004_0223cb10());
            }
        } else {
            *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        }
    }
}

void func_ov004_02229bec(void *p)
{
    func_02010f5c(p);
    func_0201100c(p);
    func_02010d64(p);
    func_02010ca4(p);
    func_ov004_02229c14(p);
}

int func_ov004_02229bb4(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x21, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02229b94(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x1e, 0x3, 0x0);
    *(u8 *) (self + 0x7d4) = 0x0;
    return;
}

void func_ov004_02229b88(int a, int b)
{
    func_ov004_02229bb4((void *) a, 6, b);
}

void func_ov004_02229aa4(char *self)
{
    u8 m;
    int k;
    if (func_02056f94(self + 0x2d0) != 0) {
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            m = 0;
            if (func_ov004_0223c85c((int) func_ov004_0223cb10()) == 0) {
                m = 1;
            }
            if (func_020b67d4() == 0 || *(int *) (self + 0x800) != 0) {
                m = (u8) (m | 2);
            }
            if (m != 0) {
                char *q = self + 0x7d4;
                if (*(u8 *) q == 0) {
                    *(u8 *) q = 1;
                    if (m == 1) {
                        func_0200f328(self, 0x6d);
                    }
                }
                k = func_0200dc10(self);
                if (func_0200dc8c(self) > 0 && k == 2) {
                    return;
                }
                *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_ov004_02229928(self, 6, -1);
                func_ov004_0223c820((char *) func_ov004_0223cb10());
            }
        } else {
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        }
    }
}

void func_ov004_02229a7c(void *p)
{
    func_02010f5c(p);
    func_0201100c(p);
    func_02010d64(p);
    func_02010ca4(p);
    func_ov004_02229aa4((char *) p);
}

int func_ov004_02229a44(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x22, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02229a3c(void *p, int a, int b)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
}

void func_ov004_022299fc(struct UnkStruct_022299fc_2 *self, void *message, int previous)
{
    struct UnkStruct_022299fc v;

    func_020109a0((void *) self, 0x1f, 3, 0);
    func_0200fa1c(&v, self, &self->head, &self->body, &data_ov004_02247780);
    func_ov004_02229a3c(&self->out, v.a, v.c);
}

void func_ov004_022299f8(void *callbackObject, int event) {}
