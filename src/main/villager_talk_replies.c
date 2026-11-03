/* villager_talk_replies: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202066c @ 0x0202066c, 0x64 bytes, Thumb
 * func_02020600 @ 0x02020600, 0x6c bytes, Thumb
 * func_02020588 @ 0x02020588, 0x78 bytes, Thumb
 * func_02020558 @ 0x02020558, 0x30 bytes, Thumb
 * func_020204f4 @ 0x020204f4, 0x64 bytes, Thumb
 * func_02020490 @ 0x02020490, 0x64 bytes, Thumb
 * func_0202042c @ 0x0202042c, 0x64 bytes, Thumb
 * func_020203c8 @ 0x020203c8, 0x64 bytes, Thumb
 */

#include "types.h"

typedef struct InnerPtr {
    char pad_00[0x830];
    void *value;
} InnerPtr;

typedef struct UnkStruct_0202066c {
    char pad_00[0x100];
    InnerPtr *ptr;
    char data[0x1E];
    unsigned char byte;
} UnkStruct_0202066c;

typedef struct Output {
    void *ptr;
    unsigned char byte;
} Output;

typedef struct {
    char pad_00[0x20];
    unsigned char level;
    unsigned char sublevel;
} UnkStruct_02020600;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_02020588_2 {
    unsigned char pad_00[0x830];
    unsigned int unk_830;
} UnkStruct_02020588_2;

typedef struct TwoWords {
    unsigned int a;
    unsigned int b;
} TwoWords;

struct UnkStruct_02020588 {
    unsigned char pad_00[0xc8];
    TwoWords unk_C8;
    unsigned char pad_D0[0x30];
    UnkStruct_02020588_2 *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
};

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02020588_3;

typedef struct StructB_02020558 {
    unsigned char pad_00[0x830];
    int unk_830;
} StructB_02020558;

typedef struct StructA_02020558 {
    unsigned char pad_00[0x100];
    StructB_02020558 *unk_100;
} StructA_02020558;

typedef struct UnkStruct_020204f4 {
    unsigned char pad_00[0x830];
    int something;
} UnkStruct_020204f4;

typedef struct {
    unsigned char pad_00[0x100];
    struct UnkStruct_020204f4 *inner;
    unsigned char unk_104[30];
    unsigned char byte;
} UnkStruct_020204f4_2;

typedef struct {
    void *ptr;
    unsigned char ch;
} Result;

struct Output_02020490 {
    void *ptr;
    unsigned char byte;
};

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
} UnkStruct_0202042c;

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} InnerA;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_0202042c_2;

typedef struct {
    u32 word;
    u8 byte;
} UnkStruct_0202042c_3;

typedef struct Global {
    int unk_00;
    unsigned char unk_04;
} Global;

typedef struct UnkStruct_020203c8 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020203c8;

typedef struct UnkStruct_020203c8_2 {
    char pad_00[0x100];
    UnkStruct_020203c8 *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_020203c8_2;

typedef struct UnkStruct_020203c8_3 {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_020203c8_3;

extern int data_020c8ab0;
extern void func_0201cfb4(void *self, void *local);
extern void func_0201cf90(void *self, void *local, int idx, int a, int b, void *ptr);
extern void func_0201cec8(void *self, void *local);
extern void func_0202da74(void *self, Pair p);
extern void func_02068388(int field, int flag);
extern int data_021c24b4;
extern int data_021c24cc;
extern Pair data_020d9150;
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern unsigned int data_020d91f8[2];
extern void func_0206e94c(void);
extern int func_0208150c(int value);
extern void func_0207a4c0(void *base, void *value);
extern unsigned char data_021e5a2c[];

void func_0202066c(UnkStruct_0202066c *a, Output *b)
{
    func_0202da38((void *) a, (void *) a->data, (void *) (&a->byte), 30, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) a->ptr->value))), data_020c8ab0, 1, 6, 2);
    b->ptr = a->data;
    b->byte = a->byte;
}

void func_02020600(void *self, int event)
{
    UnkStruct_02020600 local;

    func_0201cfb4(self, &local);
    func_0201cf90(self, &local, 0, 0x44, 0x44, &data_021c24b4);
    func_0201cf90(self, &local, 1, 0x52, 0x52, &data_021c24cc);

    local.level = 2;
    local.sublevel = local.level - 1;

    func_0201cec8(self, &local);
    func_0202da74(self, data_020d9150);
    func_02068388(*(int *) ((char *) self + 0x40), 1);
}

void func_02020588(struct UnkStruct_02020588 *s, UnkStruct_02020588_3 *out)
{
    int local0;
    unsigned int local1;

    local0 = func_020036e8(func_0208150c(s->unk_100->unk_830));
    local1 = (*(unsigned int *) &data_020c8ab0);
    func_0202da38(s, &s->unk_104, &s->unk_122, 30, local0, local1, 1, 8, 2);

    out->ptr = &s->unk_104;
    out->byte = s->unk_122;

    *(TwoWords *) ((char *) s + 0xc8) = *(TwoWords *) data_020d91f8;
}

void func_02020558(StructA_02020558 *arg, int event)
{
    StructB_02020558 *p;
    int v;
    int res;

    func_0206e94c();
    p = arg->unk_100;
    v = p->unk_830;
    res = func_0208150c(v);
    func_0207a4c0((void *) data_021e5a2c, (void *) res);
}

void func_020204f4(UnkStruct_020204f4_2 *obj, Result *res)
{
    int arg5;
    int arg6;
    arg5 = func_020036e8(func_0208150c(obj->inner->something));
    arg6 = data_020c8ab0;
    func_0202da38(obj, obj->unk_104, (char *) obj + 0x122, 30, arg5, arg6, 1, 10, 2);
    res->ptr = obj->unk_104;
    res->ch = obj->byte;
}

void func_02020490(void *A, struct Output_02020490 *B)
{
    int *p = *(int **) ((char *) A + 0x100);
    int r1 = func_020036e8(func_0208150c(*(int *) ((char *) p + 0x830)));
    func_0202da38(A, (char *) A + 0x104, (char *) A + 0x122, 0x1e, r1, data_020c8ab0, 1, 0xc, 2);
    B->ptr = (char *) A + 0x104;
    B->byte = *(unsigned char *) ((char *) A + 0x122);
}

void func_0202042c(UnkStruct_0202042c *a, UnkStruct_0202042c_2 *b)
{
    void *tmp;

    tmp = (void *) func_020036e8((int) ((void *) func_0208150c((int) (((InnerA *) a->unk_100)->unk_830))));
    func_0202da38(a, &a->unk_104, &a->unk_122, 0x1e, (int) tmp, (*(UnkStruct_0202042c_3 *) &data_020c8ab0).word, 1, 0xe, (*(UnkStruct_0202042c_3 *) &data_020c8ab0).byte);
    b->ptr = &a->unk_104;
    b->byte = a->unk_122;
}

void func_020203c8(UnkStruct_020203c8_2 *self, UnkStruct_020203c8_3 *out)
{
    func_0202da38(self, self->unk_104, (void *) (&self->unk_122), 0x1E, func_020036e8(func_0208150c(self->unk_100->unk_830)), (*(Global *) &data_020c8ab0).unk_00, 1, 0x11, (*(Global *) &data_020c8ab0).unk_04);
    out->unk_00 = self->unk_104;
    out->unk_04 = self->unk_122;
}
