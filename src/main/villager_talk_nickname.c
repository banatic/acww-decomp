/* villager_talk_nickname: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202a774 @ 0x0202a774, 0x58 bytes, Thumb
 * func_0202a708 @ 0x0202a708, 0x6c bytes, Thumb
 * func_0202a6fc @ 0x0202a6fc, 0xc bytes, Thumb
 * func_0202a6a4 @ 0x0202a6a4, 0x58 bytes, Thumb
 * func_0202a64c @ 0x0202a64c, 0x58 bytes, Thumb
 * func_0202a5e8 @ 0x0202a5e8, 0x64 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x104 - 1];
    unsigned char unk_122;
} UnkStruct_0202a774;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202a774_2;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

struct B_0202a6a4 {
    u8 pad_00[0x830];
    u32 unk_830;
};

struct A_0202a6a4 {
    u8 pad_00[0x100];
    struct B_0202a6a4 *b;
    u8 buffer[0x1e];
    u8 unk_122;
};

struct Out_0202a6a4 {
    void *ptr;
    u8 byte;
};

typedef struct {
    u8 pad_00[0x830];
    u32 value;
} UnkStruct_0202a64c;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_0202a64c *inner;
    u8 data[0x1e];
    u8 flag;
} Big;

typedef struct {
    void *data;
    u8 flag;
} UnkStruct_0202a64c_2;

extern int func_0200368c(void *a, int b, int c, int d);
extern int func_020036e8(int);
extern int func_0208150c(int);
extern int data_020c8b20;
extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);
extern void func_0202da74(void *param, Pair p);
extern Pair data_020d93d8;
extern char data_021c280c;
extern char data_021c27f4;
extern void func_0202a8a4(int a, int b);
extern struct Data020c8af0 {
    unsigned int unk_00;
    unsigned char unk_04;
} data_020c8af0;
extern struct UnkStruct_0202a5e8 {
    void *unk_00;
    unsigned char unk_04;
} out;
extern int func_0202da38(void *, void *, void *, int, int base, int offset, int scale, int, int);

void func_0202a774(UnkStruct_0202a774 *p0, UnkStruct_0202a774_2 *p1)
{
    unsigned char *p = &p0->unk_122;
    int result = func_020036e8(func_0208150c(*((int *) ((char *) p0->unk_100 + 0x830))));

    func_0200368c(&p0->unk_104, 30, data_020c8b20, result);

    *p = 4;
    p1->ptr = &p0->unk_104;
    p1->byte = *p;
}

void func_0202a708(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x4a, 0x4a, (void *) &data_021c280c);
    func_0201cf90(param, buf, 1, 0x49, 0x49, (void *) &data_021c27f4);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d93d8);
    func_02068388(param->unk_40, 1);
}

void func_0202a6fc(int a, void *output)
{
    func_0202a8a4(a, 0);
}

void func_0202a6a4(struct A_0202a6a4 *a, struct Out_0202a6a4 *out)
{
    func_0200368c(a->buffer, 0x1e, (int) ((*(void * *) &data_020c8b20)), func_020036e8(func_0208150c(a->b->unk_830)));
    a->unk_122 = 5;
    out->ptr = a->buffer;
    out->byte = a->unk_122;
}

void func_0202a64c(Big *p, UnkStruct_0202a64c_2 *out)
{
    int ret;

    ret = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(p->inner->value)));
    func_0200368c((void *) p->data, 0x1e, (*(u32 *) &data_020c8b20), ret);
    p->flag = 1;
    out->data = p->data;
    out->flag = p->flag;
}

void func_0202a5e8(void *a, struct UnkStruct_0202a5e8 *out)
{
    unsigned int v0;
    unsigned int v4;
    unsigned int v8;

    v0 = (unsigned int) func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(unsigned int *) ((unsigned char *) (*(void **) ((unsigned char *) a + 0x100)) + 0x830))));
    v4 = data_020c8af0.unk_00;
    v8 = data_020c8af0.unk_04;
    func_0202da38(a, (unsigned char *) a + 0x104, (unsigned char *) a + 0x122, 0x1e, v0, v4, v8, 0, 0);
    out->unk_00 = (unsigned char *) a + 0x104;
    out->unk_04 = *(unsigned char *) ((unsigned char *) a + 0x122);
}
