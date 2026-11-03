/* villager_talk_nickname_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202ac64 @ 0x0202ac64, 0x88 bytes, Thumb
 * func_0202abf4 @ 0x0202abf4, 0x70 bytes, Thumb
 * func_0202ab88 @ 0x0202ab88, 0x6c bytes, Thumb
 * func_0202ab30 @ 0x0202ab30, 0x58 bytes, Thumb
 * func_0202aab0 @ 0x0202aab0, 0x80 bytes, Thumb
 * func_0202aa04 @ 0x0202aa04, 0xac bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0202ac64 {
    unsigned char pad_00[0x824];
    unsigned char flag;
    unsigned char pad_825[0xb];
    int value;
};

struct Main {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202ac64 *sub;
    char buf[0x1e];
    unsigned char byte;
};

struct UnkStruct_0202ac64_2 {
    void *ptr;
    unsigned char byte;
};

struct Global {
    int value;
    unsigned char byte;
};

typedef struct SubA {
    unsigned char pad_00[0x824];
    unsigned char unk_824;
    unsigned char pad_825[0xB];
    unsigned int unk_830;
} SubA;

typedef struct UnkStruct_0202abf4 {
    unsigned char pad_00[0x100];
    SubA *sub100;
    char buf104[30];
    unsigned char unk_122;
} UnkStruct_0202abf4;

typedef struct UnkStruct_0202abf4_2 {
    char *p;
    unsigned char b;
} UnkStruct_0202abf4_2;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

typedef struct UnkStructT {
    char pad_00[0x830];
    int value;
} UnkStructT;

typedef struct UnkStructS {
    char pad_00[0x100];
    UnkStructT *t_ptr;
    char data[30];
    unsigned char unk_122;
} UnkStructS;

typedef struct UnkStruct_0202ab30 {
    char *ptr;
    unsigned char byte;
} UnkStruct_0202ab30;

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} UnkStruct_0202aa04;

struct UnkStruct_0202aa04_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x100 - 0x44];
    UnkStruct_0202aa04 *unk_100;
    char pad_104[0x12c - 0x104];
    void *unk_12C;
};

typedef struct {
    u32 data[8];
} Mutex;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern struct Global data_020c8b18;
extern int func_0200368c(char *, int, int, int);
extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);
extern void func_0202da74(void *object, Pair value);
extern Pair data_020d8f88;
extern char data_021c27ac;
extern char data_021c2824;
extern int data_020c8b20;
extern int func_020644cc(int);
extern int func_020b4448(void *, void *, unsigned char *);
extern const unsigned char data_020c8968[6];
extern int func_020984e8(void);
extern int func_02099870(int);
extern void *func_02094fd4(void *);
extern void *func_02095074(int, void *);
extern void *func_020a8bb8(void *, void *);
extern void func_0209df64(void *);
extern void *func_02081c40(void *, void *);
extern void func_0207a62c(void *, void *);
extern int func_020802c8(void *, void *, int);
extern void func_02068404(void *, int, void *);
extern void *func_02094fbc(void *);
extern unsigned char data_021e5a2c;

void func_0202ac64(struct Main *a, struct UnkStruct_0202ac64_2 *b)
{
    struct UnkStruct_0202ac64 *p;
    int arg5, arg6, arg7, arg8, arg9;

    p = a->sub;
    arg5 = func_020036e8(func_0208150c(p->value));
    arg6 = data_020c8b18.value;
    arg7 = 5;
    arg8 = p->flag & 1;
    arg9 = data_020c8b18.byte;

    func_0202da38(a, a->buf, &a->byte, 0x1e, arg5, arg6, arg7, arg8, arg9);

    a->byte += 7;
    b->ptr = a->buf;
    b->byte = a->byte;
    a->sub->flag = (a->sub->flag + 1) & 1;
}

void func_0202abf4(UnkStruct_0202abf4 *self, UnkStruct_0202abf4_2 *out)
{
    int temp;

    temp = func_020036e8(func_0208150c(self->sub100->unk_830));
    func_0200368c(self->buf104, 30, (*(int *) &data_020c8b18), temp);

    if (self->sub100->unk_824 == 0) {
        self->unk_122 = 2;
    } else {
        self->unk_122 = 3;
    }

    out->p = self->buf104;
    out->b = self->unk_122;
}

void func_0202ab88(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x45, 0x45, (void *) &data_021c27ac);
    func_0201cf90(param, buf, 1, 0x46, 0x46, (void *) &data_021c2824);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d8f88);
    func_02068388(param->unk_40, 1);
}

void func_0202ab30(UnkStructS *s, UnkStruct_0202ab30 *out)
{
    int v;

    v = func_020036e8(func_0208150c(s->t_ptr->value));
    func_0200368c(s->data, 30, data_020c8b20, v);
    s->unk_122 = 2;
    out->ptr = s->data;
    out->byte = s->unk_122;
}

int func_0202aab0(void *a, void *b, unsigned int idx)
{
    unsigned char mask;
    int avail;
    int j, i, k, base;
    unsigned char c;

    if (idx < 6) {
        base = data_020c8968[idx];
    } else {
        base = 0;
    }
    mask = 0xff;
    avail = 8;

    for (j = 0; j < 8; j++) {
        k = func_020644cc(avail);
        for (i = 0; i < 8; i++) {
            if (((mask >> i) & 1) != 0) {
                if (k == 0) {
                    c = i + base;
                    if (func_020b4448(a, b, &c) != 0) {
                        return 1;
                    }
                    mask &= ~(1 << i);
                    break;
                }
                k--;
            }
        }
        avail--;
    }
    return 0;
}

void func_0202aa04(struct UnkStruct_0202aa04_2 *self)
{
    int local1;
    Mutex mutex1;
    Mutex mutex2;
    int handle;

    handle = func_02099870((int) func_020984e8());

    func_02094fd4(&mutex1);
    func_02094fd4(&mutex2);
    func_02095074(handle, &mutex2);

    if (func_0202aab0(&mutex1, &mutex2, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) self->unk_100->unk_830)))) == 0) {
        func_020a8bb8(&mutex1, &mutex2);
    }

    if (self->unk_12C != 0) {
        func_0209df64(&local1);
        func_02081c40(self->unk_12C, &mutex1);
        func_0207a62c(&data_021e5a2c, &local1);
    } else {
        func_020802c8(self->unk_100->unk_830, &mutex1, handle);
    }

    func_02068404(self->unk_40, 0, &mutex1);
    func_02094fbc(&mutex2);
    func_02094fbc(&mutex1);
}
