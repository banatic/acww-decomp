/* field_actor_states_29: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200dbb4 @ 0x0200dbb4, 0x4c bytes, Thumb
 * func_0200dbac @ 0x0200dbac, 0x8 bytes, Thumb
 * func_0200db88 @ 0x0200db88, 0x24 bytes, Thumb
 * func_0200db84 @ 0x0200db84, 0x2 bytes, Thumb
 * func_0200da3c @ 0x0200da3c, 0x148 bytes, Thumb
 * func_0200d900 @ 0x0200d900, 0x13c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_0200dbac;

typedef struct {
    unsigned char pad_00[0x5c];
    u32 unk_5C;                           // 0x5c
    unsigned char pad_60[0x8];            // 0x60-0x67
    u32 unk_68;                           // 0x68
    unsigned char pad_6C[0x4];            // 0x6c-0x6f
    u32 unk_70;                           // 0x70
    unsigned char pad_74[0x7f8 - 0x74];   // 0x74-0x7f7
    u32 unk_7F8;                          // 0x7f8
    unsigned char pad_7FC[0x800 - 0x7fc]; // 0x7fc-0x7ff
    u32 unk_800;                          // 0x800
} UnkStruct_0200da3c;

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
} UnkStruct_0200d900;

typedef struct {
    u8 a;
    u8 b;
} TB;

typedef struct {
    u8 pad_00[0x234];
    u8 unk_234;
    u8 pad_235[0x388 - 0x235];
    u8 unk_388;
    u8 unk_389;
    u8 pad_38A[0x700 - 0x38a];
    u8 unk_700;
    u8 unk_701;
    u8 pad_702[0x710 - 0x702];
    u8 unk_710;
    u8 pad_711[0x73c - 0x711];
    u8 unk_73C;
    u8 pad_73D[0x7d4 - 0x73d];
    UnkStruct_0200d900 q;
    u8 pad_7D9[0x800 - 0x7d9];
    int unk_800;
    u8 pad_804[0xc8c - 0x804];
    int unk_C8C;
    u8 pad_C90[0xc94 - 0xc90];
    int unk_C94;
} UnkStruct_0200d900_2;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200dc00(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_02073908(void *a, u32 b);
extern int func_020b65c4(void);
extern int func_0200f290(void *a, int b);
extern int func_02096614(u16 *a, u32 *b, u32 *c, int d, u32 e);
extern int func_0209658c(u16 *a, int b, u32 c);
extern void func_020110a0(void *a, u16 *b);
extern int func_020984fc(u32 a);
extern u16 *func_02099728(unsigned int);
extern void func_0205eb8c(void *a, u16 *b, int c);
extern int func_0204bcdc(u16 *a);
extern int func_0204bc64(u16 *a);
extern void func_020109fc(void *a, int b, int c, int d);
extern void func_0205ea60(void *a);
extern void *data_020ccf94;
extern u8 data_020c75c0[];
extern TB data_020c75e8[];
extern void func_020058b4(void *state);
extern int func_0205cfe8(u8 *p);
extern int func_0205cfd4(u8 *p);
extern void func_020554b0(u8 *p, int a);
extern int func_020961d0(int a);
extern void func_0205f750(u8 *p, int a);
extern int func_0205f73c(u8 *p);
extern int func_020548cc(u8 *p, int a);
extern int func_02055478(u8 *p, int a);
extern void func_02010c34(UnkStruct_0200d900_2 *s);
extern void func_0205ccc4(u8 *p, int a);
extern void func_02055050(u8 *p);
extern void func_02055de0(u8 *p, int callback, int a, int b, UnkStruct_0200d900_2 *s, int c);
extern void func_02056730(u8 *p);

int func_0200dbb4(void *a, int b, int c, int d)
{
    int stack0[3];
    int stack1[4];
    int result;

    func_0200e92c(stack0);
    func_0200e90c(stack0, 0, c, d);
    func_0200dc00(stack1, b);
    *(int *) ((char *) a + 0x7f4) = 0;
    result = func_0200e894(a, stack0);
    func_0200e91c(stack0);
    return result;
}

void func_0200dbac(UnkStruct_0200dbac *p, int a)
{
    p->unk_00 = a;
    p->unk_04 = 0;
}

void func_0200db88(void *a, void *b, int previous)
{
    void *r4 = a;
    func_0200dbac((UnkStruct_0200dbac *) ((char *) r4 + 0x7d4), (int) (*(void **) ((char *) b + 0xc)));
    *(int *) ((char *) r4 + 0x7f8) = 0;
}

void func_0200db84(void *object, int event) {}

void func_0200da3c(UnkStruct_0200da3c *self, int kind)
{
    void *g;
    u16 buf[4];
    u32 x, y;
    int q;
    int ok;

    g = data_020ccf94;

    if (func_02073908(g, self->unk_800) != 0 || (kind != 2 && kind != 0x8b)) {
        self->unk_7F8 = 1;
    }

    if (func_02073908(g, self->unk_800) == 0) {
        kind = func_020b65c4();

        if (func_0200f290(self, 0x10) == 0 && kind != 0x2e && kind != 0xd && kind != 0xe && kind != 0xc && kind != 0x2f) {

            if (func_02096614(buf, &x, &y, -1, self->unk_800) != 0) {
                u32 *p0 = (u32 *) ((unsigned char *) self + 0x5c);
                u32 *p1 = (u32 *) ((unsigned char *) self + 0x68);

                p1[0] = x;
                p0[0] = p1[0];
                p1[2] = y;
                p0[2] = p1[2];
            }

            if (func_0209658c(buf + 1, -1, self->unk_800) != 0) {
                func_020110a0(self, buf + 1);
            }
        }
    }

    if (func_0200f290(self, 0) != 0) {
        q = func_020984fc(self->unk_800);
        buf[2] = *func_02099728(q);
        func_0205eb8c((unsigned char *) self + 0x5a0, &buf[2], q);

        if (func_0204bcdc(&buf[2]) != 0) {
            buf[3] = 0xfff1;
            ok = (func_0204bc64(&buf[2]) == func_0204bc64(&buf[3])) ? 1 : 0;
        } else {
            ok = (buf[2] == 0xfff1) ? 1 : 0;
        }

        if (ok == 0) {
            func_020109fc(self, 0, 0, 0);
            func_0205ea60((unsigned char *) self + 0x5a0);
        }
    }
}

int func_0200d900(UnkStruct_0200d900_2 *s)
{
    int ret;
    UnkStruct_0200d900 *q;
    int k;
    unsigned int ok1;
    unsigned int ok2;
    int a;
    int t;

    ret = 0;
    q = &s->q;
    if (q->unk_04 == 0) {
        a = func_0205cfe8(&s->unk_389);
        if (s->unk_C94 == 2) {
            ok1 = 1;
        } else {
            ok1 = ret;
        }
        ok2 = (s->unk_C8C == 2);
        if (a != 0 && ok1 != 0 && ok2 != 0) {
            t = func_0205cfd4(&s->unk_389);
            func_020554b0(&s->unk_234, t);
            t = func_020961d0(s->unk_800);
            func_0205f750(&s->unk_388, data_020c75c0[t]);
            t = func_0205f73c(&s->unk_388);
            func_020548cc(&s->unk_234, t);
            t = func_0205f73c(&s->unk_388);
            func_02055478(&s->unk_234, t);
            func_02010c34(s);
            k = func_020961d0(s->unk_800);
            func_0205ccc4(&s->unk_700, data_020c75e8[k].a);
            func_0205ccc4(&s->unk_701, data_020c75e8[k].b);
            func_020109fc((void *) s, 0, 0, 0);
            func_02055050(&s->unk_234);
            func_02055de0(&s->unk_234, (int) func_020058b4, 6, 1, s, 0);
            func_02056730(&s->unk_710);
            func_02056730(&s->unk_73C);
            ret = 1;
            q->unk_04 = q->unk_04 + 1;
        }
    }
    return ret;
}
