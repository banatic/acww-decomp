/* friend_code_entry_4: 9 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229bbf0 @ 0x0229bbf0, 0x16 bytes, Thumb
 * func_ov133_0229bbd4 @ 0x0229bbd4, 0x1c bytes, Thumb
 * func_ov133_0229bbb4 @ 0x0229bbb4, 0x20 bytes, Thumb
 * func_ov133_0229bb78 @ 0x0229bb78, 0x3c bytes, Thumb
 * func_ov133_0229bb64 @ 0x0229bb64, 0x14 bytes, Thumb
 * func_ov133_0229bb34 @ 0x0229bb34, 0x2e bytes, Thumb
 * func_ov133_0229badc @ 0x0229badc, 0x58 bytes, Thumb
 * func_ov133_0229ba84 @ 0x0229ba84, 0x58 bytes, Thumb
 * func_ov133_0229ba34 @ 0x0229ba34, 0x50 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229bb34 {
    u8 pad_00[0x9a];
    volatile u8 n;
    u8 pad_9B[0x15];
    u8 slots[1];
};

extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov133_0229ba10(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern int func_ov002_0220b9b8(void *, void *, int, int);
extern void *data_021f43ec;
extern void func_02070b84(void *);
extern void func_ov133_0229b938(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int val);
extern const int data_ov133_0229c7b4[];
extern int func_ov002_0220a768(char *p, int i);
extern const int data_ov133_0229c7e4[];
extern int func_ov002_0220a72c(char *p, int i);

void func_ov133_0229badc(unsigned char *p);
int func_ov133_0229ba84(char *self);
int func_ov133_0229ba34(char *self);

int func_ov133_0229bbf0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov133_0229ba10(self);
    return (int) func_ov002_02208098(self, 0x0);
}

void func_ov133_0229bbd4(void *r0)
{
    void *r4 = r0;
    func_ov133_0229badc((unsigned char *) r4);
    func_ov002_02207fc0(r4);
    func_ov002_02208098(r4, 3);
}

void func_ov133_0229bbb4(int param)
{
    if (func_0206fe60()) {
        func_ov133_0229bbf0((char *) param);
    } else {
        func_ov133_0229bbd4((void *) param);
    }
}

void func_ov133_0229bb78(char *self, int a1, int a2)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u8 *) (frame) = *(u8 *) ((char *) &data_021f43ec);
    *(u8 *) (frame) = a1;
    func_ov002_0220b9b8(self + 0x1394, frame, a2, 0x0);
    func_ov002_02208098(self, 0xb);
    func_ov133_0229ba10(self);
}

void func_ov133_0229bb64(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x9a) = 0x0;
    func_02070b84(self + 0xb0);
}

u8 *func_ov133_0229bb34(struct UnkStruct_0229bb34 *self)
{
    if (self->n >= 1) {
        return self->slots;
    }
    self->n = self->n + 1;
    return self->slots + (self->n - 1) * 0x6c;
}

void func_ov133_0229badc(unsigned char *p)
{
    int a;
    int b;
    a = func_ov133_0229ba84((char *) p);
    b = func_ov133_0229ba34((char *) p);
    func_ov002_0220a0b4(p + 0x11c, a, b);
    if ((unsigned char) (p[0x9c] + 0xf3) <= 1) {
        func_ov002_0220a374(p + 0x11c, 7);
    } else {
        func_ov002_0220a374(p + 0x11c, 1);
    }
    func_ov133_0229b938(p);
}

int func_ov133_0229ba84(char *self)
{
    u8 k = *(u8 *) (self + 0x9c);

    if (k <= 0xb) {
        return data_ov133_0229c7b4[k];
    }
    switch (k) {
        case 0xc:
            return (*(u8 *) (self + 0x9f) << 4) + 0x20;
        case 0xd:
            return func_ov002_0220a768(self + 0x180, 6);
        case 0xe:
            return func_ov002_0220a768(self + 0x180, 7);
    }
    return 0x80;
}

int func_ov133_0229ba34(char *self)
{
    u8 k = *(u8 *) (self + 0x9c);

    if (k <= 0xb) {
        return data_ov133_0229c7e4[k];
    }
    switch (k) {
        case 0xc:
            return 0x40;
        case 0xd:
            return func_ov002_0220a72c(self + 0x180, 6);
        case 0xe:
            return func_ov002_0220a72c(self + 0x180, 7);
    }
    return 0x60;
}
