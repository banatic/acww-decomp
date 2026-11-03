/* villager_talk_replies_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02020ce0 @ 0x02020ce0, 0xb8 bytes, Thumb
 * func_02020c7c @ 0x02020c7c, 0x64 bytes, Thumb
 * func_02020c18 @ 0x02020c18, 0x64 bytes, Thumb
 * func_02020bf0 @ 0x02020bf0, 0x28 bytes, Thumb
 * func_02020a5c @ 0x02020a5c, 0x194 bytes, Thumb
 * func_020208ec @ 0x020208ec, 0x170 bytes, Thumb
 * func_02020888 @ 0x02020888, 0x64 bytes, Thumb
 * func_0202081c @ 0x0202081c, 0x6c bytes, Thumb
 * func_020207b8 @ 0x020207b8, 0x64 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02020ce0 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02020ce0;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02020ce0_2 {
    char pad_00[0x100];
    UnkStruct_02020ce0 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02020ce0_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02020ce0_3;

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    char data[0x1e];
    unsigned char unk_122;
} UnkStruct_02020c7c;

typedef struct {
    unsigned char pad_00[0x830];
    int unk_830;
} SecondStruct;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02020c7c_2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02020c7c_3;

struct UnkStruct_02020c18 {
    char pad_00[0x830];
    unsigned int value;
};

struct UnkStruct_02020c18_2 {
    char pad_00[0x100];
    struct UnkStruct_02020c18 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_02020c18_3 {
    void *ptr;
    unsigned char byte;
};

struct GlobalData {
    int word;
    unsigned char byte;
};

typedef struct UnkStruct_02020a5c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02020a5c;

typedef struct UnkStruct_02020a5c_2 {
    u8 pad_00[0x100];
    UnkStruct_02020a5c *inner;
    char name[0x1e];
    u8 unk_122;
    u8 pad_123[0x13c - 0x123];
    u8 unk_13C;
} UnkStruct_02020a5c_2;

typedef struct {
    char *ptr;
    u8 byte;
} UnkStruct_02020a5c_3;

typedef struct {
    int a;
    u8 b;
} ErrData;

typedef struct {
    u8 pad_00[0x1d];
    u8 unk_1D;
} Obj2;

typedef struct UnkStruct_020208ec_3 {
    void *ptr;
    u8 byte;
} UnkStruct_020208ec_3;

typedef void (*Fn)(void *self2, UnkStruct_020208ec_3 *out);

typedef struct Pmf {
    int idx;
    int adj;
} Pmf;

typedef struct UnkStruct_020208ec {
    void *unk_00;
    u8 unk_04;
    u8 pad_05[0x82b];
    void *unk_830;
} UnkStruct_020208ec;

typedef struct UnkStruct_020208ec_4 {
    u8 pad_00[0xb0];
    Pmf pmf;
    u8 pad_B8[0x100 - 0xb8];
    UnkStruct_020208ec *unk_100;
    char arr_104[0x1e];
    u8 unk_122;
    u8 pad_123[5];
    u32 unk_128;
    u32 unk_12C;
} UnkStruct_020208ec_4;

typedef struct UnkStruct_020208ec_2 {
    u32 a;
    u8 b;
} UnkStruct_020208ec_2;

typedef struct UnkStruct_02020888 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_02020888;

typedef struct UnkStruct_02020888_2 {
    unsigned char pad_00[0x100];
    UnkStruct_02020888 *sub;
    char buffer[0x1E];
    unsigned char byte;
} UnkStruct_02020888_2;

typedef struct UnkStruct_02020888_3 {
    char *ptr;
    unsigned char byte;
} UnkStruct_02020888_3;

typedef struct {
    int a;
    unsigned char b;
} GlobalData;

typedef struct {
    char pad_00[0x20];
    unsigned char level;
    unsigned char sublevel;
} UnkStruct_0202081c;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_020207b8;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    void *unk_104;
    char pad_108[0x122 - 0x108];
    unsigned char unk_122;
} UnkStruct_020207b8_2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020207b8_3;

extern Cfg data_020c8a88;
extern int data_020ccf94;
extern int data_021e5a2c;
extern int func_020644cc(int x);
extern int func_02073d90(int x);
extern int func_0207f1c8(int x);
extern int func_0209b5ec(void *);
extern int func_0207f0c0(int x);
extern void func_0209c214(int x);
extern int func_0208150c(int x);
extern void func_0207c460(int *g, int x);
extern int func_020036e8(int x);
extern int func_0202da38(void *p1, void *p2, void *p3, int d, int e, int f, int g, int h, int i);
extern struct GlobalData data_020c8a98;
extern int func_02022454(char *);
extern ErrData data_020c89f8;
extern ErrData data_020c8b28;
extern ErrData data_020c8ca0;
extern ErrData data_020c8a38;
extern ErrData data_020c8970;
extern ErrData data_020c8c88;
extern Obj2 *func_0207f270(int);
extern void *func_020794c4(unsigned char *);
extern int func_0202c424(UnkStruct_02020a5c_2 *self, int *out);
extern void func_0202bcd4(UnkStruct_02020a5c_2 *self);
extern int func_0202c420(UnkStruct_02020a5c_2 *self);
extern int func_0202c3f0(UnkStruct_02020a5c_2 *self);
extern int func_0202c3e4(UnkStruct_02020a5c_2 *self, int r7);
extern ErrData *func_0202c388(UnkStruct_02020a5c_2 *self, int *a, void *b);
extern int func_0202c31c(UnkStruct_02020a5c_2 *self, int *a, void *b);
extern ErrData *func_0202c2c4(UnkStruct_02020a5c_2 *self, int a);
extern int func_0202c2a8(UnkStruct_02020a5c_2 *self);
extern int func_0202c37c(UnkStruct_02020a5c_2 *self, int r7);
extern ErrData *func_0202c350(UnkStruct_02020a5c_2 *self);
extern int func_0202c27c(UnkStruct_02020a5c_2 *self, Obj2 *obj2);
extern ErrData *func_0202c254(UnkStruct_02020a5c_2 *self, int *a, Obj2 *obj2);
extern int func_0202c248(UnkStruct_02020a5c_2 *self, void *a);
extern int func_0202c23c(UnkStruct_02020a5c_2 *self, void *a);
extern int func_0202c230(UnkStruct_02020a5c_2 *self, void *a);
extern UnkStruct_020208ec_2 data_020c8ab0;
extern char data_021c2454;
extern char data_021c24fc;
extern char data_021c2514;
extern void func_0202d8f8(void *self, void *p12c, void *p128, void *p830, int zero);
extern int func_020819bc(void *a);
extern int func_0207a47c(void *a, void *b);
extern void func_0202da88(UnkStruct_020208ec_4 *self, void *str);
extern void func_020819e0(void *a);
extern void func_0201cfb4(void *self, void *local);
extern void func_0201cf90(void *self, void *local, int idx, int a, int b, void *ptr);
extern void func_0201cec8(void *self, void *local);
extern void func_0202da74(void *self, Pair p);
extern void func_02068388(int field, int flag);
extern int data_021c246c;
extern int data_021c24e4;
extern Pair data_020d9420;

void func_02020ce0(UnkStruct_02020ce0_2 *self, UnkStruct_02020ce0_3 *out)
{
    // DECLS
    int mode;
    int h;
    // ENDDECLS

    if (func_020644cc(3) == 0 && func_02073d90(data_020ccf94) == 0) {
        int inner = self->unk_100->unk_830;
        h = (func_0209b5ec((void *) func_0207f1c8(inner)));
        if (func_0207f0c0(inner) == 0) {
            func_0209c214(h);
            func_0207c460(&data_021e5a2c, func_0208150c(inner));
        }
        mode = 3;
    } else {
        mode = 2;
    }
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), data_020c8a88.unk_00, data_020c8a88.unk_04, mode, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
}

void func_02020c7c(UnkStruct_02020c7c *p1, UnkStruct_02020c7c_3 *out)
{
    int local0;
    int local1;
    int local2;

    local0 = func_020036e8(func_0208150c(((SecondStruct *) p1->unk_100)->unk_830));
    local1 = (*(UnkStruct_02020c7c_2 *) &data_020c8a88).unk_00;
    local2 = (*(UnkStruct_02020c7c_2 *) &data_020c8a88).unk_04;

    func_0202da38(p1, p1->data, &p1->unk_122, 30, local0, local1, local2, 1, 0);

    out->ptr = p1->data;
    out->byte = p1->unk_122;
}

void func_02020c18(struct UnkStruct_02020c18_2 *a, struct UnkStruct_02020c18_3 *out)
{
    func_0202da38((void *) a, (void *) a->unk_104, (void *) (&a->unk_122), 30, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(a->unk_100->value))), data_020c8a98.word, data_020c8a98.byte, 0, 0);
    out->ptr = a->unk_104;
    out->byte = a->unk_122;
}

void func_02020bf0(unsigned char *r5, unsigned char *r4)
{
    unsigned char *r0;

    func_02022454((char *) r5);
    r0 = r5 + 0x104;
    *(unsigned int *) r4 = (unsigned int) r0;
    r0 = r5 + 0x122;
    *(unsigned char *) (r4 + 4) = *r0;
}

int func_02020a5c(UnkStruct_02020a5c_2 *self, UnkStruct_02020a5c_3 *out)
{
    void *local_18;
    ErrData *err = 0;
    int flag;
    void *local_20;
    int local_24 = -1;
    int local_28;
    int local_2c;
    Obj2 *r6;
    int r7;

    local_18 = self->inner->unk_830;
    r6 = func_0207f270((int) local_18);
    local_20 = func_020794c4((unsigned char *) r6);
    flag = 0;
    local_28 = 0;
    local_2c = 0;
    r7 = func_0202c424(self, &local_2c);
    func_0202bcd4(self);

    if (func_0202c420(self) != 0) {
        err = &data_020c89f8;
        if (r7 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3f0(self) != 0) {
        err = &data_020c8b28;
        if (r7 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3e4(self, r7) != 0) {
        err = func_0202c388(self, &local_28, local_18);
    } else if (func_0202c31c(self, &local_24, (char *) self->inner + 0x5c) != 0) {
        err = func_0202c2c4(self, local_24);
    } else if (func_0202c2a8(self) != 0) {
        err = &data_020c8ca0;
    } else if (func_0202c37c(self, r7) != 0) {
        err = func_0202c350(self);
    } else if (func_0202c27c(self, r6) != 0) {
        err = func_0202c254(self, &local_28, r6);
    } else if (func_0202c248(self, local_20) != 0) {
        err = &data_020c8a38;
    } else if (func_0202c23c(self, local_20) != 0) {
        err = &data_020c8970;
    } else if (func_0202c230(self, local_20) != 0) {
        err = &data_020c8c88;
    }

    if (err != 0) {
        func_0202da38((void *) self, (void *) self->name, (void *) (&self->unk_122), 0x1e, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) local_18))), err->a, err->b, local_28, 0);
        flag = 1;
    }

    out->ptr = self->name;
    out->byte = self->unk_122;
    r6->unk_1D |= 4;
    return flag;
}

void func_020208ec(UnkStruct_020208ec_4 *self, UnkStruct_020208ec_3 *out)
{
    void *f830;

    f830 = self->unk_100->unk_830;
    if (func_02020a5c((UnkStruct_02020a5c_2 *) self, (UnkStruct_02020a5c_3 *) out) != 0) {
        func_0202d8f8(self, (void *) &self->unk_12C, (void *) &self->unk_128, self->unk_100->unk_830, 0);
    } else {
        func_0202d8f8(self, (void *) &self->unk_12C, (void *) &self->unk_128, self->unk_100->unk_830, 0);
        if (self->unk_12C != 0 && func_020819bc((void *) self->unk_12C) == 0) {
            func_0202da38(self, self->arr_104, &self->unk_122, 0x1e, func_020036e8((int) ((void *) func_0208150c((int) f830))), data_020c8ab0.a,
                          data_020c8ab0.b, 0, 0);
            out->ptr = self->arr_104;
            out->byte = self->unk_122;
            func_020819e0((void *) self->unk_12C);
        } else {
            if (func_0207a47c((void *) ((char *) &data_021e5a2c), (void *) func_0208150c((int) f830)) == 0) {
                switch (func_020644cc(3)) {
                    case 0:
                        func_0202da88(self, &data_021c2454);
                        break;
                    case 1:
                        func_0202da88(self, &data_021c24fc);
                        break;
                    default:
                        func_0202da88(self, &data_021c2514);
                        break;
                }
                if (((volatile Pmf *) &self->pmf)->idx != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn f;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        f = (Fn) * (int *) (*(char **) t + pm->idx);
                    } else {
                        f = (Fn) pm->idx;
                    }
                    f(t, out);
                }
            } else {
                func_0202da88(self, &data_021c2514);
                if (((volatile Pmf *) &self->pmf)->idx != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn f;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        f = (Fn) * (int *) (*(char **) t + pm->idx);
                    } else {
                        f = (Fn) pm->idx;
                    }
                    f(t, out);
                }
            }
        }
    }
}

void func_02020888(UnkStruct_02020888_2 *obj, UnkStruct_02020888_3 *out)
{
    int val = func_020036e8(func_0208150c(obj->sub->unk_830));
    func_0202da38((void *) obj, (void *) obj->buffer, (void *) (&obj->byte), 30, val, (*(GlobalData *) &data_020c8ab0).a, 1, 3, (*(GlobalData *) &data_020c8ab0).b);
    out->ptr = obj->buffer;
    out->byte = obj->byte;
}

void func_0202081c(void *self, int event)
{
    UnkStruct_0202081c local;

    func_0201cfb4(self, &local);
    func_0201cf90(self, &local, 0, 0xc4, 0xc4, &data_021c246c);
    func_0201cf90(self, &local, 1, 0xd0, 0xd0, &data_021c24e4);

    local.level = 2;
    local.sublevel = local.level - 1;

    func_0201cec8(self, &local);
    func_0202da74(self, data_020d9420);
    func_02068388(*(int *) ((char *) self + 0x40), 1);
}

void func_020207b8(UnkStruct_020207b8_2 *s, UnkStruct_020207b8_3 *out)
{
    int result;
    int g_word;
    unsigned char g_byte;

    result = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) (*(void **) ((char *) s->unk_100 + 0x830)))));
    g_word = (*(UnkStruct_020207b8 *) &data_020c8ab0).word;
    g_byte = (*(UnkStruct_020207b8 *) &data_020c8ab0).byte;

    func_0202da38(s, &s->unk_104, &s->unk_122, 0x1e, result, g_word, 1, 0x14, g_byte);

    out->ptr = &s->unk_104;
    out->byte = s->unk_122;
}
