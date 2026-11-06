/* field_actor_35: 22 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02215624 @ 0x02215624, 0x40 bytes, Thumb
 * func_ov003_02215620 @ 0x02215620, 0x4 bytes, Thumb
 * func_ov003_0221561c @ 0x0221561c, 0x4 bytes, Thumb
 * func_ov003_02215614 @ 0x02215614, 0x6 bytes, Thumb
 * func_ov003_02215570 @ 0x02215570, 0xa4 bytes, Thumb
 * func_ov003_02215544 @ 0x02215544, 0x2c bytes, Thumb
 * func_ov003_022154ec @ 0x022154ec, 0x58 bytes, Thumb
 * func_ov003_022154cc @ 0x022154cc, 0x20 bytes, Thumb
 * func_ov003_02215494 @ 0x02215494, 0x36 bytes, Thumb
 * func_ov003_02215460 @ 0x02215460, 0x34 bytes, Thumb
 * func_ov003_02215454 @ 0x02215454, 0xc bytes, Thumb
 * func_ov003_022153e8 @ 0x022153e8, 0x6c bytes, Thumb
 * func_ov003_02215394 @ 0x02215394, 0x52 bytes, Thumb
 * func_ov003_0221535c @ 0x0221535c, 0x36 bytes, Thumb
 * func_ov003_022152f8 @ 0x022152f8, 0x64 bytes, Thumb
 * func_ov003_022152ec @ 0x022152ec, 0xc bytes, Thumb
 * func_ov003_022152b4 @ 0x022152b4, 0x38 bytes, Thumb
 * func_ov003_0221527c @ 0x0221527c, 0x38 bytes, Thumb
 * func_ov003_02215240 @ 0x02215240, 0x3c bytes, Thumb
 * func_ov003_0221523c @ 0x0221523c, 0x4 bytes, Thumb
 * func_ov003_02215234 @ 0x02215234, 0x6 bytes, Thumb
 * func_ov003_02215190 @ 0x02215190, 0xa4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x5a0];
    unsigned char addr_5a0;
    unsigned char pad_5A1[0x2f];
    unsigned int src[3];
    unsigned char pad_5DC[0x1f8];
    unsigned char addr_7d4;
    unsigned char pad_7D5[0x2b];
    unsigned int unk_800;
    unsigned char pad_804[0xc0];
    unsigned int dest1;
    unsigned int dest2;
    unsigned int dest3;
    unsigned char pad_8D0[0x20];
    unsigned char addr_8f0;
} UnkStruct_02215570;

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7d4 - 0x2d0 - 1];
    unsigned char unk_7D4;
    char pad_7D5[0x7f0 - 0x7d4 - 1];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} MrPeanut;

struct some_struct {
    char pad_00[0x800];
    int unk_800;
};

struct UnkStruct_02215240 {
    char data[0xc];
    char flag;
    char pad_0D[0x1c - 0xd];
};

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int n, int x, int y);
extern void func_ov003_02215664(void *p, void *q);
extern void *func_0200e894(void *p, void *q);
extern int func_0200e91c(void *p);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern int func_0200f328(void *, int);
extern int func_02073908(unsigned int *, unsigned int);
extern int func_0203b144(void);
extern int func_02056f94(void *ptr);
extern int func_02008258(void *self, int val);
extern int func_02008c40(void *self, int a, int b);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_02010f5c(void *);
extern int func_0200f554(void *);
extern void func_02010d64(void *);
extern int data_ov003_0223812c;
extern void func_0201107c(void *a, void *b);
extern void *data_020ccf94;
extern int func_0201100c(void *p);
extern int func_020113a4(int a, int b, int c);
extern int func_02060474(void *);
extern unsigned char func_0203cc38(void);
extern unsigned char *func_020604f8(unsigned char *);
extern void func_02079798(unsigned char *);
extern int func_0208b500(void);
extern void func_0208d09c(void *argument0);

int func_ov003_02215240(void *a, char b, int c, int d);

void *func_ov003_02215624(void *a, void *b, int c, int d)
{
    char s1[12];
    char s2[16];
    void *r;

    func_0200e92c(s1);
    func_0200e90c(s1, 0x51, c, d);
    func_ov003_02215664(s2, b);
    r = func_0200e894(a, s1);
    func_0200e91c(s1);
    return r;
}

void func_ov003_02215620(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_0221561c(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_02215614(u8 *src, u8 *dst)
{
    *dst = *src;
}

void func_ov003_02215570(UnkStruct_02215570 *self, const unsigned char *param, int previous)
{
    unsigned char byte;
    unsigned int *src;

    byte = param[0xc];

    func_ov003_02215620((unsigned char *) (&self->addr_7d4), (unsigned char) byte);
    func_ov003_0221561c((unsigned char *) (&self->addr_8f0), (unsigned char) byte);
    func_020109a0(self, 0x56, 3, 0);
    func_0205eae0(&self->addr_5a0, 0x19, 3, 0);
    func_0200f328(self, 0x84c);
    func_0200f328(self, 0x84e);

    src = self->src;
    self->dest1 = src[0];
    self->dest2 = src[1];
    self->dest3 = src[2];

    if (func_02073908((*(unsigned int **) &data_020ccf94), self->unk_800) != 0) {
        func_0203b144();
    }
}

void func_ov003_02215544(void *p, void *q)
{
    unsigned char c;
    func_ov003_02215614((u8 *) ((char *) p + 0x8f0), (u8 *) (&c));
    func_ov003_02215624(p, (void *) c, 6, (int) q);
}

int func_ov003_022154ec(MrPeanut *self)
{
    int result = func_02056f94(&self->unk_2D0);
    if (result == 0) {
        return result;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (self->unk_7D4 != 0) {
        return func_02008c40(self, 5, -1);
    } else {
        return func_0200d4e8(self, 3, 1, -1);
    }
}

void func_ov003_022154cc(void *p)
{
    func_02010f5c(p);
    func_0200f554(p);
    func_02010d64(p);
    func_ov003_022154ec((MrPeanut *) p);
}

void *func_ov003_02215494(void *r0, void *r1, void *r2)
{
    void *sp[8];
    void *r4;
    void *r5;
    void *r6;

    r5 = r0;
    r4 = r1;
    r6 = r2;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x52, (int) r4, (int) r6);
    r4 = func_0200e894(r5, sp);
    func_0200e91c(sp);
    return r4;
}

void func_ov003_02215460(void *obj, void *message, int previous)
{
    func_0201107c(obj, &data_ov003_0223812c);
    func_020109a0(obj, 0x57, 3, 0);
    func_0205eae0((char *) obj + 0x5a0, 0x1a, 3, 0);
}

void func_ov003_02215454(int a, int b)
{
    func_ov003_02215494((void *) a, (void *) 6, (void *) b);
}

void func_ov003_022153e8(char *self)
{
    if (func_02056f94(self + 0x2d0) == 0) {
        return;
    }
    if (func_02073908((unsigned int *) data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_0203b144();
    }
    *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    func_0200d4e8(self, 3, 1, -1);
    func_0205eae0(self + 0x5a0, 19, 3, 0);
}

void func_ov003_02215394(void *arg)
{
    int val, local;
    char *p;

    func_02010f5c(arg);
    if (func_0200f554(arg) != 0) {
        func_0201100c(arg);
    }
    func_02010d64(arg);

    p = (char *) arg;
    p += 0x98;
    val = *(int *) p;

    if (val < 0) {
        val = -val;
    }

    local = -1 * func_020113a4(val, 0, 0xc5);

    func_0201107c(arg, (void *) (&local));
    func_ov003_022153e8((char *) arg);
}

void *func_ov003_0221535c(void *r0, void *r1, void *r2)
{
    char sp[0x20];
    void *r4;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x53, (int) r1, (int) r2);
    r4 = func_0200e894(r0, sp);
    func_0200e91c(sp);
    return r4;
}

void func_ov003_022152f8(void *self, void *message, int previous)
{
    unsigned int *src;

    func_020109a0(self, 0x58, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 0x1b, 3, 1);
    func_0200f328(self, 0x84c);
    func_0200f328(self, 0x84e);

    src = (unsigned int *) ((char *) self + 0x5d0);
    *(unsigned int *) ((char *) self + 0x8c4) = src[0];
    *(unsigned int *) ((char *) self + 0x8c8) = src[1];
    *(unsigned int *) ((char *) self + 0x8cc) = src[2];
}

void func_ov003_022152ec(int a, int b)
{
    func_ov003_0221535c((void *) a, (void *) 6, (void *) b);
}

void func_ov003_022152b4(void *obj)
{
    if (func_02056f94((char *) obj + 0x2d0)) {
        if (func_02060474((char *) obj + 0x5c8)) {
            func_ov003_02215240(obj, 0, 6, -1);
        }
    }
}

void func_ov003_0221527c(struct some_struct *s)
{
    func_02010f5c(s);
    func_0200f554(s);
    func_02010d64(s);
    if (func_02073908((unsigned int *) ((*(int *) &data_020ccf94)), s->unk_800) != 0) {
        func_ov003_022152b4(s);
    }
}

int func_ov003_02215240(void *a, char b, int c, int d)
{
    struct UnkStruct_02215240 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x54, c, d);
    local.flag = b;
    result = (int) func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}

void func_ov003_0221523c(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_02215234(u8 *src, u8 *dst)
{
    *dst = *src;
}

void func_ov003_02215190(unsigned char *self, unsigned char *param, int previous)
{
    typedef struct {
        unsigned short field_0;
        unsigned char field_2;
        signed char field_3;
        unsigned char field_4;
        unsigned char field_5;
    } Block;
    unsigned char c;
    signed char t;
    Block *block;
    c = param[0xc];
    block = (Block *) (self + 0x7d4);
    block->field_4 = c;
    block->field_0 = 0x39;
    block->field_5 = func_0203cc38();
    if (c == 0) {
        if (func_02073908((unsigned int *) data_020ccf94, *((unsigned int *) (self + 0x800))) != 0) {
            t = *((signed char *) (func_020604f8(self + 0x5c8) + 0x7e));
            block->field_3 = t;
            if (t < 0x38) {
                func_02079798(self + 0x5c);

                func_0208d09c((void *) func_0208b500());
            }
        }
        block->field_2 = 0;
        func_020109a0((void *) ((int) (self)), (int) (0x59), (int) (3), 0);
        func_0205eae0((void *) (self + 0x5a0), 0x1c, 3, 1);
    } else {
        block->field_2 = 2;
        block->field_0 = 0x3a;
        *((unsigned int *) (self + 0x81c)) = 8;
    }
    func_ov003_0221523c(self + 0x8f0, (unsigned char) c);
}
