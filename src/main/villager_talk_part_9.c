/* villager_talk_part_9: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02027f74 @ 0x02027f74, 0x84 bytes, Thumb
 * func_02027f28 @ 0x02027f28, 0x4c bytes, Thumb
 * func_02027e4c @ 0x02027e4c, 0xdc bytes, Thumb
 * func_02027dcc @ 0x02027dcc, 0x80 bytes, Thumb
 * func_02027d68 @ 0x02027d68, 0x64 bytes, Thumb
 * func_02027d38 @ 0x02027d38, 0x30 bytes, Thumb
 */

typedef struct {
    int value;
    unsigned char byte;
} GlobalData;

typedef struct {
    char *buffer;
    unsigned char flag;
} UnkStruct_02027f74;

typedef struct {
    char pad_00[0x830];
    int value;
} UnkStruct_02027f28;

typedef struct {
    char pad_00[0x100];
    UnkStruct_02027f28 *ptr;
    char pad_104[0x5C];
    int unk_160;
} UnkStruct_02027f28_2;

struct Pair {
    int a;
    int b;
};

struct UnkStruct_02027e4c {
    char pad_00[0x830];
    int value;
};

struct UnkStruct_02027e4c_2 {
    char pad_00[0xc8];
    struct Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_02027e4c *sub;
    char buf[0x1e];
    unsigned char byte;
    char pad_123[0x160 - 0x123];
    void *ptr;
};

struct UnkStruct_02027e4c_3 {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_02027e4c_4 {
    void *ptr;
    unsigned char byte;
};

struct UnkStruct_02027dcc {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02027dcc_2 {
    char pad_00[0x100];
    struct UnkStruct_02027dcc *sub;
    char pad_104[0x5c];
    void *unk_160;
};

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_02027d68;

extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern GlobalData data_020c8990;
extern GlobalData data_020c8988;
extern void func_0207bae8(int, int, int, int);
extern void func_0209b56c(int);
extern unsigned char data_021e5a2c[];
extern struct UnkStruct_02027e4c_3 data_020c8998;
extern struct UnkStruct_02027e4c_3 data_020c8a40;
extern struct Pair data_020d8df0;
extern int func_0209b4cc(void *ptr, int idx);
extern void func_02015e10(void *self, int value, int idx);
extern int func_0209bb70(int);
extern void func_02015de4(void *self, int value, int a, int b);
extern int func_02015330(void *, int, int, int, int);
extern void func_0202dbf0(void *, struct Pair);
extern struct Pair data_020d8e00;
extern UnkStruct_02027d68 data_020c8978;

void func_02027f74(char *self, UnkStruct_02027f74 *out)
{
    GlobalData *r4 = 0;
    int x;
    int a, v, b;

    x = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) self));

    switch (x) {
        case 0xa:
            r4 = &data_020c8990;
            break;
        case 0x13:
            r4 = &data_020c8988;
            break;
        default:
            break;
    }

    if (r4 != 0) {
        a = func_020036e8(func_0208150c(*(int *) (*(char **) (self + 0x100) + 0x830)));
        v = r4->value;
        b = r4->byte;
        func_0202da38(self, self + 0x104, self + 0x122, 30, a, v, b, 0, 0);
    }

    out->buffer = self + 0x104;
    out->flag = *(unsigned char *) (self + 0x122);
}

void func_02027f28(UnkStruct_02027f28_2 *p)
{
    int a = func_0208150c(p->ptr->value);
    int b = func_0209b4cc((void *) p->unk_160, 1);
    func_0207bae8((unsigned int) data_021e5a2c, a, b, -20);
    func_0209b56c(p->unk_160);
}

void func_02027e4c(struct UnkStruct_02027e4c_2 *self, struct UnkStruct_02027e4c_4 *out)
{
    struct UnkStruct_02027e4c_3 *dp = 0;
    int v;
    int res;
    int tmp;
    v = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) self));
    switch (v) {
        case 10:
            dp = &data_020c8998;
            break;

        case 19:
            dp = &data_020c8a40;
            break;
    }

    if (dp != 0) {
        res = func_0208150c(self->sub->value);
        res = func_020036e8(res);
        func_0202da38(self, (void *) self->buf, (void *) (&self->byte), 30, res, dp->unk_00, dp->unk_04, 0, 0);
        if (self->ptr != 0) {
            tmp = func_0209b4cc(self->ptr, 0);
            func_02015e10(self, tmp, 0);
            tmp = func_0209b4cc(self->ptr, 1);
            func_02015e10(self, tmp, 1);
            tmp = func_0209bb70((int) func_0202d9c4((unsigned int *) self));
            func_02015de4(self, tmp, 0, 7);
        }
    }
    out->ptr = &self->buf;
    out->byte = self->byte;
    self->unk_C8 = data_020d8df0;
}

void func_02027dcc(struct UnkStruct_02027dcc_2 *self)
{
    int arg5;
    if (func_0209bc40((unsigned char *) ((int) func_0202d9c4((unsigned int *) self))) == 19) {
        arg5 = 0;
        func_02015330(self, func_0209bb70((int) func_0202d9c4((unsigned int *) self)), 0, 5, arg5);
        func_0202dbf0(self, data_020d8e00);
    }
    {
        int r4 = func_0208150c(self->sub->unk_830);
        int r2 = func_0209b4cc(self->unk_160, 1);
        func_0207bae8((unsigned int) data_021e5a2c, r4, r2, ~19);
        func_0209b56c((int) self->unk_160);
    }
}

void func_02027d68(char *p1, char *p2)
{
    char *inner;
    int value;
    int local0, local1, local2, local3, local4;

    inner = *(char **) (p1 + 0x100);
    value = *(int *) (inner + 0x830);
    local0 = func_020036e8(func_0208150c(value));
    local1 = data_020c8978.word;
    local2 = data_020c8978.byte;
    local3 = 0;
    local4 = 0;
    func_0202da38(p1, p1 + 0x104, p1 + 0x122, 30, local0, local1, local2, local3, local4);
    *(void **) p2 = p1 + 0x104;
    *(unsigned char *) (p2 + 4) = *(unsigned char *) (p1 + 0x122);
}

unsigned short func_02027d38(unsigned short *param1, int param2)
{
    unsigned short result;
    unsigned short value;
    int flag;

    result = 0;
    flag = 0;
    value = *param1;
    if (value >= 0x11a8 && value <= 0x12a7) {
        flag = 1;
    }
    if (flag != 0 && param2 == 2) {
        result = 1;
    }
    return result;
}
