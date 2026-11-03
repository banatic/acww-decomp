/* town_villager_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020817a8 @ 0x020817a8, 0xbc bytes, Thumb
 * func_02081710 @ 0x02081710, 0x98 bytes, Thumb
 * func_02081660 @ 0x02081660, 0xb0 bytes, Thumb
 * func_0208164c @ 0x0208164c, 0x14 bytes, Thumb
 * func_02081518 @ 0x02081518, 0x134 bytes, Thumb
 * func_0208150c @ 0x0208150c, 0xc bytes, Thumb
 * func_02081500 @ 0x02081500, 0xc bytes, Thumb
 * func_020814f4 @ 0x020814f4, 0xc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020817a8 {
    u8 pad_00[0x400];
    u8 pad_400[0x634 - 0x400];
    u8 pad_634[0x734 - 0x634];
    u8 pad_734[0x78c - 0x734];
    u8 pad_78C[0x7a0 - 0x78c];
    u8 pad_7A0[0x7b0 - 0x7a0];
    u8 pad_7B0[0x7b8 - 0x7b0];
    u8 pad_7B8[0x7ce - 0x7b8];
    u16 unk_7CE;                   // offset 0x7ce
    u8 pad_extra[0x7d2 - 0x7d0];   // offset 0x7d0, size 2
    u16 unk_7D2;                   // offset 0x7d2
    u8 pad_7D4[0x7dc - 0x7d2 - 2]; // remaining to 0x7dc
};

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02081f18(void *);
extern void *func_02081f30(void *);
extern char *func_02072dbc(void *);
extern void func_02066694(void *);
extern void *func_0209b634(void *);
extern void func_02034ce0(void *);
extern void func_020051b0(void *);
extern int func_02003780(void *);
extern void func_020642fc(void *);
extern int func_02081fa0(void *);
extern void func_020642f8(void *);
extern void func_02081f9c(void *);
extern int func_02003750(void *);
extern void *func_0209b61c(void *);
extern void func_02066688(void *);
extern void *func_02072da4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void MI_CpuFill8(void *p, int a, int b);
extern void func_02003738(void *p);
extern void func_02080b50(void *p);
extern void func_02081ef0(void *p);
extern void func_020642e0(void *p);
extern void func_02081f94(void *p);
extern void func_0209b604(void *p);
extern void func_02066650(void *p);
extern void func_0207dfec(void *p);
extern void MI_CpuCopy8(int, int, int);
extern void *func_02082500(void *b);
extern unsigned int *func_02082164(void *local);
extern void func_0205195c(void *local);
extern int func_02082308(void *local, void *b);
extern void func_02082114(void *local, void *ptr, int n);
extern void *func_0208214c(void *local);
extern void func_020036ec(void *a, void *b, int r7, int d);
extern void func_0207f2f4(void *a, unsigned char v);
extern void func_0207f2e8(void *a, unsigned char v);
extern void *func_0207f1c8(void *a);
extern void func_0209b5f0(void *a, unsigned char *ptr, unsigned char w);
extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern void func_0207f414(void *a, int r, int zero);
extern void func_0207d634(void *a);
extern void func_0207ef3c(void *a, int c);

void *func_020817a8(struct UnkStruct_020817a8 *p)
{
    __cxa_vec_ctor((void *) (p), 8, 0x80, (((void (*)(void *)) func_02081f30)), (((void (*)(void *)) func_02081f18)));
    func_02072dbc((char *) p + 0x400);
    func_02066694((char *) p + 0x634);
    func_0209b634((char *) p + 0x734);
    __cxa_vec_ctor((void *) ((char *) p + 0x78c), 10, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_02003780((char *) p + 0x7a0);
    __cxa_vec_ctor((void *) ((char *) p + 0x7b0), 4, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_020642fc((char *) p + 0x7b8);
    func_02081fa0(&p->unk_7CE);
    p->unk_7D2 = 0xfff1;
    func_020642fc((char *) p + 0x7dc);
    return p;
}

void *func_02081710(void *obj)
{
    func_020642f8((char *) obj + 0x7dc);
    func_02081f9c((char *) obj + 0x7ce);
    func_020642f8((char *) obj + 0x7b8);
    __cxa_vec_cleanup((void *) ((char *) obj + 0x7b0), 4, 2, (void (*)(void *)) func_020051b0);
    func_02003750((char *) obj + 0x7a0);
    __cxa_vec_cleanup((void *) ((char *) obj + 0x78c), 0xa, 2, (void (*)(void *)) func_020051b0);
    func_0209b61c((char *) obj + 0x734);
    func_02066688((char *) obj + 0x634);
    func_02072da4((char *) obj + 0x400);
    __cxa_vec_cleanup((void *) (obj), 8, 0x80, (((void (*)(void *)) func_02081f18)));
    return obj;
}

void func_02081660(void *self)
{
    int i;
    int j;

    MI_CpuFill8(self, 0, 0x7ec);
    func_02003738((char *) self + 0x7a0);
    *(unsigned short *) ((char *) self + 0x7d2) = 0x11a8;
    func_02080b50(self);

    for (i = 0; i < 8; i++) {
        func_02081ef0((char *) self + (i << 7));
    }

    func_020642e0((char *) self + 0x7b8);

    for (j = 0; j < 10; j++) {
        *(unsigned short *) ((char *) self + (j << 1) + 0x78c) = 0xfff1;
    }

    func_02081f94((char *) self + 0x7ce);
    func_0209b604((char *) self + 0x734);
    *(unsigned char *) ((char *) self + 0x7d6) = 3;
    func_02066650((char *) self + 0x634);
    func_0207dfec(self);
    func_020642e0((char *) self + 0x7dc);
}

void func_0208164c(int p0, int p1)
{
    MI_CpuCopy8(p1, p0, 2028);
}

void func_02081518(void *a, void *b, int c, int d, unsigned char e)
{
    unsigned char local[0x18];
    int i;
    int res;
    int res2;
    unsigned char v;
    unsigned char v2;
    unsigned short x;
    void *r4;
    int r7;

    r4 = func_02082500(b);
    r7 = 0;

    func_02082164(local);
    if (r4) {
        r7 = ((unsigned char *) r4)[0x4a];
    }
    func_020036ec((char *) a + 0x7a0, b, r7, d);
    func_0205195c(local);
    if (func_02082308(local, b)) {
        func_02082114(local, (char *) a + 0x7c6, 4);
    }

    if (r4) {
        x = *(unsigned short *) ((char *) r4 + 0x2c);
        if (x < 0x100) {
            x = (unsigned short) (x + 0x11a8);
        } else {
            x = 0x11a8;
        }
        *(unsigned short *) ((char *) a + 0x7d2) = x;

        for (i = 0; i < 10; i++) {
            *(unsigned short *) ((char *) a + i * 2 + 0x78c) = *(unsigned short *) ((char *) r4 + i * 2 + 6);
        }

        func_0207f2f4(a, ((unsigned char *) r4)[0x30]);
        func_0207f2e8(a, ((unsigned char *) r4)[0x31]);
        func_0209b5f0(func_0207f1c8(a), (unsigned char *) r4 + 0x32, e);
        res = func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(a)));
        func_0207f414(a, res, 0);
        ((unsigned char *) a)[0x7d8] = ((unsigned char *) r4)[0x2f];
        res2 = func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(a)));
        if (res2 == 2) {
            v = ((unsigned char *) a)[0x7d8];
            v2 = v % 10;
            ((unsigned char *) a)[0x7d8] = v2;
        }
        func_0207d634(a);
        ((unsigned char *) a)[0x7da] = ((unsigned char *) r4)[0x2e];
    }
    func_0207ef3c(a, c);
    func_0208214c(local);
}

unsigned int func_0208150c(unsigned int r0)
{
    return r0 + 0x7a0;
}

unsigned int func_02081500(unsigned int r0)
{
    return r0 + 0x400;
}

int func_020814f4(int a)
{
    return a + 0x634;
}
