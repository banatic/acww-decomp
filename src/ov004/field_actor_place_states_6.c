/* field_actor_place_states_6: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b6a0 @ 0x0222b6a0, 0x8 bytes, Thumb
 * func_ov004_0222b69c @ 0x0222b69c, 0x4 bytes, Thumb
 * func_ov004_0222b694 @ 0x0222b694, 0x6 bytes, Thumb
 * func_ov004_0222b5e0 @ 0x0222b5e0, 0xb4 bytes, Thumb
 * func_ov004_0222b5b4 @ 0x0222b5b4, 0x2c bytes, Thumb
 * func_ov004_0222b540 @ 0x0222b540, 0x74 bytes, Thumb
 * func_ov004_0222b524 @ 0x0222b524, 0x1a bytes, Thumb
 * func_ov004_0222b520 @ 0x0222b520, 0x4 bytes, Thumb
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b69c;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b520;

extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void func_0200fa1c(int *v, void *self, void *p, short *b, int *a);
extern void func_02051e04(int *w);
extern void func_020109fc(void *self, int m, int a, int b);
extern int func_ov004_0222b6a8(unsigned char *addr, unsigned char v, int n, int arg2);
extern int func_02051dfc(void);
extern int func_ov004_0222b3e8(void *self, int a, int b, int c);
extern int func_ov004_0222b4e0(void *self, int a, int b, int c);
extern int func_0200f554(void *self);
extern void func_02010f5c(void *self);

void func_ov004_0222b6a0(struct Pair *p, u8 b)
{
    p->a = 0;
    p->b = b;
}

void func_ov004_0222b69c(UnkStruct_0222b69c *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_0222b694(unsigned char *a, unsigned char *b)
{
    *b = *a;
}

void func_ov004_0222b5e0(void *self, void *msg, int previous)
{
    short b;
    int a;
    int w[3];
    int v[3];
    unsigned char k;
    int m;

    k = *((unsigned char *) msg + 0xc);
    func_ov004_0222b6a0((struct Pair *) ((char *) self + 0x7d4), k);
    func_ov004_0222b69c((UnkStruct_0222b69c *) ((char *) self + 0x8f0), k);
    if (k != 0) {
        m = 0xc;
    } else {
        m = 0xf;
    }
    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        if (k == 0) {
            a = -0x2000;
        } else {
            a = 0x2000;
        }
        b = (short) (*(short *) ((char *) self + 0x8e) + 0x4000);
        func_0200fa1c(v, self, (char *) self + 0x5c, &b, &a);
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        func_02051e04(w);
        func_020109fc(self, m, 3, 0);
    } else {
        func_020109fc(self, m, 3, 0);
    }
}

void func_ov004_0222b5b4(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_0222b694(base + 0x8f0, &val);
    func_ov004_0222b6a8(base, val, 6, arg2);
}

void func_ov004_0222b540(char *self)
{
    unsigned char *q;

    if (func_02073908((void *) ((*(char * *) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
        q = (unsigned char *) (self + 0x7d4);
        if (q[0] < 3) {
            q[0] = q[0] + 1;
        }
        switch (func_02051dfc()) {
            case 0:
                break;
            case 1:
                if (q[0] >= 3) {
                    func_ov004_0222b3e8(self, q[1], 6, -1);
                }
                break;
            case 2:
                if (q[0] >= 3) {
                    func_ov004_0222b4e0(self, q[1], 6, -1);
                }
                break;
        }
    }
}

void func_ov004_0222b524(void *self)
{
    func_0200f554(self);
    func_02010f5c(self);
    func_ov004_0222b540((char *) self);
}

void func_ov004_0222b520(UnkStruct_0222b520 *p, unsigned char v)
{
    p->unk_00 = v;
}
