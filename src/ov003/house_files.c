/* house_files: 22 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02220110 @ 0x02220110, 0x10 bytes, Thumb
 * func_ov003_0222010c @ 0x0222010c, 0x2 bytes, Thumb
 * func_ov003_0221ffec @ 0x0221ffec, 0x120 bytes, Thumb
 * func_ov003_0221ffcc @ 0x0221ffcc, 0x20 bytes, Thumb
 * func_ov003_0221ffc0 @ 0x0221ffc0, 0xa bytes, Thumb
 * func_ov003_0221ffb4 @ 0x0221ffb4, 0xc bytes, Thumb
 * func_ov003_0221ffb0 @ 0x0221ffb0, 0x4 bytes, Thumb
 * func_ov003_0221ffac @ 0x0221ffac, 0x4 bytes, Thumb
 * func_ov003_0221ff9c @ 0x0221ff9c, 0x10 bytes, Thumb
 * func_ov003_0221ff98 @ 0x0221ff98, 0x2 bytes, Thumb
 * func_ov003_0221ff80 @ 0x0221ff80, 0x18 bytes, Thumb
 * func_ov003_0221fec0 @ 0x0221fec0, 0xc0 bytes, Thumb
 * func_ov003_0221feb8 @ 0x0221feb8, 0x8 bytes, Thumb
 * func_ov003_0221feb4 @ 0x0221feb4, 0x4 bytes, Thumb
 * func_ov003_0221fea4 @ 0x0221fea4, 0x10 bytes, Thumb
 * func_ov003_0221fea0 @ 0x0221fea0, 0x4 bytes, Thumb
 * func_ov003_0221fe9c @ 0x0221fe9c, 0x4 bytes, Thumb
 * func_ov003_0221fe94 @ 0x0221fe94, 0x6 bytes, Thumb
 * func_ov003_0221fe90 @ 0x0221fe90, 0x2 bytes, Thumb
 * func_ov003_0221fe34 @ 0x0221fe34, 0x5c bytes, Thumb
 * func_ov003_0221fe30 @ 0x0221fe30, 0x2 bytes, Thumb
 * func_ov003_0221fe2c @ 0x0221fe2c, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *a[4];
    void *b[4];
    void *c;
    void *d;
} UnkStruct_0221ffec;

typedef struct {
    int a[4];
    int b[4];
    int x;
    int y;
} UnkStruct_0221ffcc;

struct UnkStruct_0221ffb4 {
    char pad_00[0x10];
    int arr[4];
};

typedef struct Server {
    unsigned char pad_00[0x20];
    struct Server *next;
} Server;

struct UnkStruct_0221ff80 {
    int unk_00;
    int arr[5];
    int unk_18;
    char unk_1C;
};

typedef struct {
    u32 unk_00;
    u32 arr[5];
    u32 unk_18;
    u8 unk_1C;
} UnkStruct_0221fec0;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0221fe94;

extern void *data_021fbe94;
extern int data_021f34b0;
extern const char data_ov003_02239bf8[];
extern const char data_ov003_02239c1c[];
extern const char data_ov003_02239c40[];
extern const char data_ov003_02239c58[];
extern unsigned char *func_020b3750(void *record);
extern int func_020b38c0(void *p, int i);
extern int func_ov003_022203dc(void);
extern void *func_02064960(void *a, int b, const char *f, int d, ...);
extern void *func_021077e8(void *p);
extern int func_020560e0(void *p, int x);
extern void *func_020561cc(void *p, void *q);
extern void func_020e9898(void *p);
extern int func_02056064(void *p, int x);
extern void *func_02064b2c(const char *f, void *g, int n, int z);
extern void *NNS_G3dGetJntAnmSet(void *p);
extern void *func_02107b44(void *p, int x);
extern int func_0204cb90(const void *a, int b);
extern int NNS_FndMountArchive(void *out, const void *src, int x);
extern int func_02064328(const void *a, const void *b, unsigned int c);
extern void *NNS_FndGetArchiveFileByName(const void *p);
extern void *func_02107828(void *p);
extern void *NNS_G3dGetTexPatAnmSet(void *p);
extern u32 func_02107bf8(void *p, int x);
extern int func_0210285c(void *p);
extern int data_021c9b1c;
extern char data_021f39fc[];
extern char data_ov003_02239b94[];
extern char data_ov003_02239ba4[];
extern char data_ov003_02239ba8[];
extern char data_ov003_02239bc4[];
extern char data_ov003_02239be0[];
extern char data_ov003_0223cec8[];
extern int func_02056084(int, int);
extern int data_ov003_02239b74;

void func_ov003_0221ffcc(volatile UnkStruct_0221ffcc *p);
void func_ov003_0221ff80(struct UnkStruct_0221ff80 *p);

int func_ov003_02220110(int x)
{
    func_ov003_0221ffcc((volatile UnkStruct_0221ffcc *) x);
    return x;
}

void func_ov003_0222010c(void) {}

int func_ov003_0221ffec(UnkStruct_0221ffec *self)
{
    int rem;
    void *m;
    void *g1;
    int neg4;
    u8 i;
    int z1;
    int z2;
    int idx;
    s8 letter;
    void *t;

    g1 = (*(void **) &data_021c9b1c);
    i = 0;
    neg4 = -4;
    z2 = 0;
    z1 = 0;
    do {
        idx = func_020b38c0(func_020b3750(&data_021f34b0), i);
        letter = (s8) (idx / 5 + 0x41);
        rem = idx % 5;
        t = data_021fbe94;
        m = func_02064960(t, neg4, data_ov003_02239bf8, letter, letter, rem, func_ov003_022203dc());
        self->a[i] = func_021077e8(m);
        if (func_020560e0(self->a[i], z1) != 0) {
            self->a[i] = func_020561cc(self->a[i], (*(void **) &data_021c9b1c));
        }
        func_020e9898(m);
        m = func_02064960(data_021fbe94, neg4, data_ov003_02239c1c, letter, letter, rem);
        self->b[i] = func_021077e8(m);
        if (func_02056064(self->b[i], z2) != 0) {
            self->b[i] = func_020561cc(self->b[i], g1);
        }
        func_020e9898(m);
        i = (u8) (i + 1);
    } while (i < 4);
    self->c = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_02239c40, g1, 4, 0)), 0);
    self->d = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_02239c58, g1, 4, 0)), 0);
    return 1;
}

void func_ov003_0221ffcc(volatile UnkStruct_0221ffcc *p)
{
    unsigned int i;
    int v;

    i = 0;
    v = i;
    do {
        p->a[i] = v;
        p->b[i] = v;
        i++;
    } while (i < 4);
    p->y = v;
    p->x = p->y;
}

int func_ov003_0221ffc0(int *p, int i)
{
    return p[i & 3];
}

int func_ov003_0221ffb4(struct UnkStruct_0221ffb4 *s, int idx)
{
    return s->arr[idx & 3];
}

Server *func_ov003_0221ffb0(Server *server)
{
    return server->next;
}

int func_ov003_0221ffac(int *p0)
{
    return p0[9];
}

int func_ov003_0221ff9c(int x)
{
    func_ov003_0221ff80((struct UnkStruct_0221ff80 *) x);
    return x;
}

void func_ov003_0221ff98(void) {}

void func_ov003_0221ff80(struct UnkStruct_0221ff80 *p)
{
    unsigned int i = 0;
    unsigned int zero = i;
    for (; i < 5; i++) {
        p->arr[i] = zero;
    }
    p->unk_00 = zero;
    p->unk_18 = zero;
    p->unk_1C = zero;
}

int func_ov003_0221fec0(UnkStruct_0221fec0 *s)
{
    u8 buf[0x6c];
    unsigned int i;
    int ret;

    func_ov003_0221ff80((struct UnkStruct_0221ff80 *) s);

    if (func_0204cb90(data_021f39fc, 0x11) == -1) {
        return 0;
    }

    ret = (int) func_02064b2c((const char *) data_ov003_02239b94, (void *) data_021c9b1c, 4, 0);

    if (NNS_FndMountArchive(buf, data_ov003_02239ba4, ret) != 0) {
        for (i = 0; i < 5; i++) {
            char *p;
            u16 a;
            u32 b;

            func_02064328(data_ov003_0223cec8, data_ov003_02239ba8, i);
            p = (char *) func_02107828(NNS_FndGetArchiveFileByName(data_ov003_0223cec8));
            a = *(u16 *) (p + 0xe);
            b = *(u32 *) (p + a + 0xc);
            s->arr[i] = (u32) (p + b);
        }

        s->unk_00 = (u32) func_021077e8(NNS_FndGetArchiveFileByName(data_ov003_02239bc4));
        func_02056064((void *) s->unk_00, 0);

        s->unk_18 = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_ov003_02239be0)), 0);
        s->unk_1C = 1;
        func_0210285c(buf);
    }

    return 1;
}

void func_ov003_0221feb8(void *argument0)
{
    func_ov003_0221ff80((struct UnkStruct_0221ff80 *) argument0);
}

int func_ov003_0221feb4(int *p0)
{
    return p0[0];
}

void *func_ov003_0221fea4(void **p, unsigned int index)
{
    if (index < 5) {
        return *(p + index + 1);
    }
    return 0;
}

int func_ov003_0221fea0(int *p0)
{
    return p0[6];
}

int func_ov003_0221fe9c(unsigned char *p0)
{
    return p0[28];
}

void func_ov003_0221fe94(UnkStruct_0221fe94 *p)
{
    p->unk_00 = 0;
}

void func_ov003_0221fe90(void) {}

int func_ov003_0221fe34(int *param)
{
    int a = (*(int *) &data_021fbe94);
    int t = func_ov003_022203dc();
    int ret = (int) func_02064960((void *) a, ~3, (const char *) (&data_ov003_02239b74), t);

    if (ret != 0) {
        *param = (int) func_021077e8((void *) ret);
        func_02056084(*param, 0);
        *param = (int) func_020561cc((void *) (*param), (void *) data_021c9b1c);
        func_020e9898((void *) ret);
        return 1;
    } else {
        return 0;
    }
}

void func_ov003_0221fe30(void *ptr) {}

int func_ov003_0221fe2c(int *p0)
{
    return p0[0];
}
