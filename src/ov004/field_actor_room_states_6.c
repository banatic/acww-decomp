/* field_actor_room_states_6: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02228100 @ 0x02228100, 0x64 bytes, Thumb
 * func_ov004_022280b0 @ 0x022280b0, 0x50 bytes, Thumb
 * func_ov004_022280ac @ 0x022280ac, 0x2 bytes, Thumb
 * func_ov004_02228078 @ 0x02228078, 0x34 bytes, Thumb
 * func_ov004_02228038 @ 0x02228038, 0x40 bytes, Thumb
 * func_ov004_0222801c @ 0x0222801c, 0x1a bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02228100 {
    unsigned char pad_00[0x820];
    unsigned short unk_820;
    unsigned short unk_822;
} UnkStruct_02228100;

typedef struct UnkStruct_02228100_2 {
    int data[3];
} UnkStruct_02228100_2;

typedef struct UnkStruct_02228100_3 {
    int data[4];
} UnkStruct_02228100_3;

struct UnkStruct_022280b0 {
    int a;
    unsigned char b;
    int c;
    int d;
};

typedef struct BigStruct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x7fc - (0x7f0 + 4)];
    int unk_7FC;
} BigStruct;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov004_02228164(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_02057d58(void *dst, int a, int b, int c, void *self, int d);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_02057d0c(int k, void *self);
extern int func_020b65c4(void);
extern int func_0200f328(void *self, int msg);
extern int func_02056f28(void *, int);
extern void func_02010f5c(void *);
extern int func_02056f94(char *p);
extern int func_02008258(BigStruct *p, int x);
extern int func_0200c3b0(BigStruct *p, int a, int b, int c);
extern void func_02010d64(void *self);

int func_ov004_02228100(UnkStruct_02228100 *p0, unsigned short *p1, int p2, int p3, int p4, int p5, int p6, short p7)
{
    UnkStruct_02228100_2 s;
    UnkStruct_02228100_3 t;
    int result;

    func_0200e92c(&s);
    func_0200e90c(&s, 0x36, p6, p7);

    p0->unk_822 = *p1;
    p0->unk_820 = p0->unk_822;

    func_ov004_02228164(&t, p2, p3, p4, p5);
    result = func_0200e894(p0, &s);
    func_0200e91c(&s);

    return result;
}

void func_ov004_022280b0(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_022280b0 *q;
    q = (struct UnkStruct_022280b0 *) (p + 0xc);
    func_02057d58(self + 0x820, *(int *) (p + 0xc), q->b, q->c, self, q->d);
    func_020109a0(self, 0x2e, 3, 0);
    func_02057d0c(1, self);
    if (func_020b65c4() == 9) {
        func_0200f328(self, 0x4f);
    }
}

void func_ov004_022280ac(void *callbackObject, int event) {}

void func_ov004_02228078(u8 *self)
{
    if (func_02056f28(self + 0x2d0, 8) != 0 && func_020b65c4() == 9) {
        func_0200f328(self, 0x63);
    }
    func_02010f5c(self);
}

void func_ov004_02228038(BigStruct *p)
{
    if (func_02056f94((char *) p + 0x2d0)) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        func_0200c3b0(p, 3, 5, -1);
    }
}

void func_ov004_0222801c(void *self)
{
    func_ov004_02228078((u8 *) self);
    func_02010d64(self);
    func_ov004_02228038((BigStruct *) self);
}
