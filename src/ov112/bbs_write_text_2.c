/* bbs_write_text_2: 5 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f35c @ 0x0229f35c, 0x84 bytes, Thumb
 * func_ov112_0229f328 @ 0x0229f328, 0x34 bytes, Thumb
 * func_ov112_0229f2bc @ 0x0229f2bc, 0x6c bytes, Thumb
 * func_ov112_0229f29c @ 0x0229f29c, 0x20 bytes, Thumb
 * func_ov112_0229f270 @ 0x0229f270, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    char pad_A0[0xb7 - 0xa0];
    unsigned char unk_B7;
    char pad_B8[0xc1 - 0xb8];
    unsigned char unk_C1;
} UnkStruct_0229f35c;

typedef void (*Fn)(void *);

extern int func_ov112_0229fe70(void *p, int a);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern void func_ov002_0220a000(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a1dc(void *);
extern void func_ov095_0229cce0(void *);
extern void func_ov002_0220a164(void *);

void func_ov112_0229f35c(UnkStruct_0229f35c *p)
{
    if (func_ov112_0229fe70(p, 0x800) != 0) {
        func_ov002_0220a000((char *) p + 0x4448, p->unk_98, p->unk_9C - p->unk_B7, 3, 2);
        p->unk_C1 = 0xc;
    } else {
        int a = func_ov095_02299b7c((char *) p + 0x384);
        int b = func_ov095_02299b38((char *) p + 0x384);
        func_ov002_0220a000((char *) p + 0x4448, a, b, 3, 2);
        p->unk_C1 = 0x6;
    }
    func_ov002_02208098(p, 7);
}

void func_ov112_0229f328(char *s, int a, int b)
{
    unsigned char *p = (unsigned char *) s;
    func_ov002_0220a000((void *) (s + 0x4448), a, b, 3, 2);
    p[0xc1] = p[0x8d];
    func_ov002_02208098((void *) s, 7);
}

void func_ov112_0229f2bc(char *self)
{
    int a;
    int b;
    void *obj;

    if (func_ov112_0229fe70((void *) self, 0x800) != 0) {
        func_ov002_0220a0b4(self + 0x4448, *(int *) (self + 0x98), *(int *) (self + 0x9c) - *(u8 *) (self + 0xb7));
    } else {
        a = func_ov095_02299b7c((void *) (self + 0x384));
        b = func_ov095_02299b38((void *) (self + 0x384));
        func_ov002_0220a0b4(self + 0x4448, a, b);
    }
    obj = self + 0x4448;
    (*(Fn **) obj)[3](obj);
}

void func_ov112_0229f29c(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x4448);
    func_ov002_02208098(arg0, 8);
}

void func_ov112_0229f270(void *self)
{
    func_ov095_0229cce0((char *) self + 0x384);
    func_ov002_0220a164((char *) self + 0x4448);
    func_ov002_02208098(self, 0xa);
}
