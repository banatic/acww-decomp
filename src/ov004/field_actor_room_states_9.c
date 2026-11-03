/* field_actor_room_states_9: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222852c @ 0x0222852c, 0x44 bytes, Thumb
 * func_ov004_02228510 @ 0x02228510, 0x1c bytes, Thumb
 * func_ov004_02228480 @ 0x02228480, 0x90 bytes, Thumb
 * func_ov004_02228438 @ 0x02228438, 0x48 bytes, Thumb
 * func_ov004_02228410 @ 0x02228410, 0x26 bytes, Thumb
 * func_ov004_0222840c @ 0x0222840c, 0x4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222852c {
    unsigned char b;
    unsigned char pad_01;
    short e;
};

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_02228510;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_02228510 sub;
} UnkStruct_02228510_2;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222840c;

extern unsigned short func_ov004_022285c4(const unsigned char *a, unsigned char *b, int *c, int *d, unsigned short *e);
extern int func_ov004_02228628(int a, int b, int c, int d, short e, int f, short g);
extern void func_0200fbc4(UnkStruct_02228510_2 *self, unsigned int a, unsigned int b, short c);
extern unsigned int *func_0200f27c(void *self, int a);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_02073908(int a, int b);
extern int func_ov004_0223b33c(void *p, short a);
extern int data_020ccf94;
extern void func_0200f268(void *, int);
extern int func_02056f94(void *);
extern int func_ov004_022283cc(void *, int, int, int);
extern void func_02010f5c(void *);
extern void func_02010d64(void *);

void func_ov004_0222852c(char *self, short arg)
{
    struct UnkStruct_0222852c t;
    int c, d;

    func_ov004_022285c4((const unsigned char *) (self + 0x8f0), &t.b, &c, &d, (unsigned short *) &t.e);
    func_ov004_02228628((int) self, t.b, c, d, t.e, 6, arg);
    return;
}

void func_ov004_02228510(UnkStruct_02228510_2 *self)
{
    UnkStruct_02228510 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}

void func_ov004_02228480(unsigned char *self)
{
    int s, k, n;
    s = *(int *) (self + 0x704);
    if (s == 0x1a || s == 0) {
        n = ((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) == 0 ? 1 : 0;
        if (n < 6) {
            func_0200f27c(self, 2);
            switch (*(unsigned char *) (self + 0x7de)) {
                case 0:
                    k = 0x3b;
                    break;
                case 1:
                    k = 0x3c;
                    break;
                case 2:
                    k = 0x3d;
                    break;
            }
            func_020109a0(self, k, 3, 0);
            if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
                func_ov004_0223b33c(self + 0x5c, *(short *) (self + 0x8e));
            }
        }
    }
}

void func_ov004_02228438(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x704) != 0x1a && *(int *) (self + 0x704) != 0x0 && func_02056f94(self + 0x2d0) != 0x0) {
        func_0200f268(self, 0x2);
        func_ov004_022283cc(self, *(u8 *) (self + 0x7de), 0x6, -0x1);
        return;
    }
}

void func_ov004_02228410(void *p)
{
    func_ov004_02228510((UnkStruct_02228510_2 *) p);
    func_ov004_02228480((unsigned char *) p);
    func_02010f5c(p);
    func_02010d64(p);
    func_ov004_02228438((char *) p);
}

void func_ov004_0222840c(UnkStruct_0222840c *p, unsigned char v)
{
    p->unk_00 = v;
}
