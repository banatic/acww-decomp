/* villager_talk_request: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020285d0 @ 0x020285d0, 0x78 bytes, Thumb
 * func_020285b4 @ 0x020285b4, 0x1c bytes, Thumb
 * func_02028550 @ 0x02028550, 0x64 bytes, Thumb
 * func_0202854c @ 0x0202854c, 0x2 bytes, Thumb
 * func_020284c0 @ 0x020284c0, 0x8c bytes, Thumb
 * func_02028478 @ 0x02028478, 0x48 bytes, Thumb
 * func_0202836c @ 0x0202836c, 0x10c bytes, Thumb
 * func_02028358 @ 0x02028358, 0x12 bytes, Thumb
 * func_02028284 @ 0x02028284, 0xd4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xC8];
    unsigned int word_at_c8;
    unsigned int word_at_cc;
    unsigned char pad_D0[0x30];
    unsigned int *ptr_at_100;
    unsigned char data_at_104[0x1E];
    unsigned char byte_at_122;
} UnkStruct_020285d0;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020285d0_2;

typedef struct {
    unsigned int word;
    unsigned char byte;
} GlobalC8C40;

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} GlobalD9130;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
} UnkStruct_02028550;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02028550_2;

typedef struct UnkStruct_02028478 {
    unsigned char pad_00[0x158];
    unsigned char unk_158;
    unsigned char unk_159;
} UnkStruct_02028478;

typedef struct UnkStruct_0202836c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_0202836c;

typedef struct UnkStruct_0202836c_2 {
    u8 pad_00[0x100];
    UnkStruct_0202836c *unk_100;
    u8 pad_104[0x20];
    u16 unk_124;
    u8 pad_126[0x36];
    void *unk_15C;
    void *unk_160;
} UnkStruct_0202836c_2;

typedef struct UnkStruct_0202836c_3 {
    s32 a, b;
} UnkStruct_0202836c_3;

typedef struct {
    u8 pad_00[0x830];
    u32 unk_830;
} UnkStruct_02028284_2;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_02028284_2 *unk_100;
    u8 unk_104[0x122 - 0x104];
    u8 unk_122;
    u8 pad_123[0x160 - 0x123];
    u32 unk_160;
} UnkStruct_02028284_3;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_02028284_4;

typedef struct {
    u32 w;
    u8 b;
} UnkStruct_02028284;

extern GlobalC8C40 data_020c8c40;
extern GlobalD9130 data_020d9130;
extern unsigned int func_0202d9c4(unsigned int *);
extern void func_0209bd5c(void *);
extern void func_0207b57c(void *ptr);
extern unsigned char data_021e5a2c[];
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int scale, int, int);
extern int data_020c8ab8;
extern unsigned int data_020c8c48[];
extern unsigned int data_020c8a90[];
extern int func_0209bc40(unsigned char *);
extern void *func_0209bc20(void *record);
extern void func_0209e474(int);
extern void func_0209e234(int, unsigned char);
extern void func_0209bb74(int, unsigned char);
extern UnkStruct_0202836c_3 data_020d8f50;
extern UnkStruct_0202836c_3 data_020d8f00;
extern void *func_020984e8(void);
extern int func_02099640(int);
extern int func_0209b4d8(void *, int, int, void *);
extern int func_0209b4d4(void *);
extern void func_0202d9d0(UnkStruct_0202836c_2 *, int);
extern u16 *func_0209bb70(void *);
extern void *func_02099734(void *);
extern int func_02098eb8(void *);
extern int func_02098f0c(void *, u16 *, int, int);
extern int func_0209a1d0(void);
extern void func_0209b2a8(void *, int);
extern int func_020154b4(UnkStruct_0202836c_2 *, u16 *, int, int, int);
extern void func_0202dbf0(UnkStruct_0202836c_2 *, UnkStruct_0202836c_3);
extern void func_0202db48(UnkStruct_0202836c_2 *, UnkStruct_0202836c_3);
extern int func_0209bb88(int x);
extern int func_0209b4cc(u32 x, int y);
extern void func_02015e10(UnkStruct_02028284_3 *self, int r, int idx);
extern void func_02015de4(UnkStruct_02028284_3 *self, int r, int idx, int val);
extern UnkStruct_02028284 data_020c89d8;
extern UnkStruct_02028284 data_020c8a70;

void func_020285d0(UnkStruct_020285d0 *a, UnkStruct_020285d0_2 *b)
{
    func_0202da38(
        a, (void *) a->data_at_104, (void *) (&a->byte_at_122), 0x1e,
        (unsigned int) func_020036e8((unsigned int) func_0208150c(*(unsigned int *) ((char *) a->ptr_at_100 + 0x830))),
        data_020c8c40.word, data_020c8c40.byte, 0, 0);
    b->ptr = a->data_at_104;
    b->byte = a->byte_at_122;
    *(GlobalD9130 *) &a->word_at_c8 = data_020d9130;
}

void func_020285b4(unsigned int *argument0)
{
    func_0209bd5c((void *) func_0202d9c4((unsigned int *) argument0));
    func_0207b57c((void *) data_021e5a2c);
}

void func_02028550(UnkStruct_02028550 *a, UnkStruct_02028550_2 *b)
{
    int r = func_020036e8(func_0208150c(*(int *) ((char *) a->unk_100 + 0x830)));
    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, r, data_020c8ab8, ((unsigned char *) &data_020c8ab8)[4], 0,
                  0);
    b->unk_00 = (char *) a + 0x104;
    b->unk_04 = *(unsigned char *) ((char *) a + 0x122);
}

void func_0202854c(void) {}

void func_020284c0(char *p1, char *p2)
{
    unsigned int *msg = 0;
    int val;

    switch (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p1))) {
        case 0xa:
            msg = data_020c8c48;
            break;
        case 0x13:
            msg = data_020c8a90;
            break;
    }
    if (msg != 0) {
        val = func_020036e8(func_0208150c(*(int *) (*(int *) (p1 + 0x100) + 0x830)));
        func_0202da38(p1, p1 + 0x104, p1 + 0x122, 0x1e, val, msg[0], *(unsigned char *) (msg + 1), 0, 0);
    }
    *(void **) p2 = p1 + 0x104;
    *(unsigned char *) (p2 + 4) = *(unsigned char *) (p1 + 0x122);
    *(unsigned short *) (p1 + 0x15a) = 0x5e;
}

void func_02028478(UnkStruct_02028478 *arg)
{
    if ((int) func_0202d9c4((unsigned int *) arg) != 0) {
        int v;
        v = (int) func_0209bc20((void *) (int) func_0202d9c4((unsigned int *) arg));
        func_0209e474(v);
        func_0209e234(v, arg->unk_158);
        func_0209bb74((int) func_0202d9c4((unsigned int *) arg), arg->unk_159);
    }
}

void func_0202836c(UnkStruct_0202836c_2 *p)
{
    void *a1;
    void *q;
    int v;
    int t;
    int t2;

    a1 = func_020984e8();
    func_02099640((int) a1);
    q = p->unk_100->unk_830;
    v = 2;
    if (p->unk_160 != 0) {
        func_0209b4d8(p->unk_160, func_0209bc40((unsigned char *) ((void *) func_0202d9c4((unsigned int *) p))),
                      func_0208150c((int) q), p->unk_15C);
        func_0209bd5c((void *) func_0202d9c4((unsigned int *) p));
        func_0207b57c((void *) (((int *) data_021e5a2c)));
        func_0202d9d0(p, func_0209b4d4(p->unk_160));
        p->unk_124 = *func_0209bb70((void *) func_0202d9c4((unsigned int *) p));
        switch (func_0209bc40((unsigned char *) ((void *) func_0202d9c4((unsigned int *) p)))) {
            case 0xa:
                t2 = func_02098eb8(func_02099734(a1));
                func_02098f0c(func_02099734(a1), &p->unk_124, t2, v);
                break;
            case 0x13:
                t = func_0209a1d0();
                if (t != 0) {
                    func_0209b2a8(p->unk_160, t);
                }
                v = 0;
                break;
        }
    }
    func_020154b4(p, &p->unk_124, v, 5, 0);
    func_0202dbf0(p, data_020d8f50);
    func_0202db48(p, data_020d8f00);
}

void func_02028358(unsigned int *argument0)
{
    func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) argument0));
}

void func_02028284(UnkStruct_02028284_3 *self, UnkStruct_02028284_4 *out)
{
    UnkStruct_02028284 *r4;
    int v, a, b;

    r4 = 0;
    v = func_0209bc40((unsigned char *) ((int) func_0202d9c4((unsigned int *) self)));
    switch (v) {
        case 10:
            r4 = &data_020c89d8;
            break;
        case 19:
            r4 = &data_020c8a70;
            break;
    }

    if (r4 != 0) {
        a = func_020036e8(func_0208150c(self->unk_100->unk_830));
        b = func_0209bb88((int) func_0202d9c4((unsigned int *) self));
        func_0202da38((void *) self, self->unk_104, &self->unk_122, 0x1e, a, r4->w, r4->b, b, 0);

        if (self->unk_160 != 0) {
            func_02015e10(self, func_0209b4cc(self->unk_160, 0), 0);
            func_02015e10(self, func_0209b4cc(self->unk_160, 1), 1);
            func_02015de4(self, (int) func_0209bb70((void *) ((int) func_0202d9c4((unsigned int *) self))), 0, 7);
        }
    }

    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
}
