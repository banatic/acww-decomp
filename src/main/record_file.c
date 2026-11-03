/* record_file: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206e8c4 @ 0x0206e8c4, 0x12 bytes, Thumb
 * func_0206e8b4 @ 0x0206e8b4, 0x10 bytes, Thumb
 * func_0206e890 @ 0x0206e890, 0x22 bytes, Thumb
 * func_0206e854 @ 0x0206e854, 0x3c bytes, Thumb
 * func_0206e83c @ 0x0206e83c, 0x18 bytes, Thumb
 * func_0206e808 @ 0x0206e808, 0x32 bytes, Thumb
 * func_0206e7bc @ 0x0206e7bc, 0x4c bytes, Thumb
 * func_0206e778 @ 0x0206e778, 0x44 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
} UnkStruct_0206e8c4;

struct UnkStruct_0206e890 {
    int pad_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int pad_10;
    int pad_14;
    void *unk_18;
};

struct Pair {
    u32 lo, hi;
};

struct UnkStruct_0206e854 {
    struct Pair data;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
};

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[4];
    char *unk_10;
    unsigned int unk_14;
    char *unk_18;
} UnkStruct_0206e7bc;

typedef struct {
    void *arc;
    unsigned int file_id;
} FSFileID;

struct UnkStruct_0206e778 {
    FSFileID id;
    int unk_08;
    char pad_0C[12];
    int unk_18;
};

extern int FS_ConvertPathToFileID(struct UnkStruct_0206e890 *obj, int b);
extern void *func_020e98b4(int value);
extern int func_02050974(void *);
extern void func_020647ec(struct Pair, u32, u32, u32);
extern int data_021c8188;
extern void func_020e9898(int);
extern void FS_InitFile(void *buf);
extern int FS_OpenFileFast(void *buf, FSFileID id);
extern void func_02064658(void *buf, int a, int b, int c);
extern int FS_CloseFile(void *buf);

void func_0206e808(void *arg);
void func_0206e778(void *selfv, unsigned int idx);

void func_0206e8c4(UnkStruct_0206e8c4 *s)
{
    s->unk_00 = 0;
    s->unk_14 = -1;
    s->unk_0C = 0;
    s->unk_10 = 0;
    s->unk_18 = 0;
    s->unk_08 = 0;
}

int func_0206e8b4(int arg)
{
    func_0206e808((void *) arg);
    return arg;
}

int func_0206e890(struct UnkStruct_0206e890 *obj, int b, int c, int d)
{
    obj->unk_08 = c;
    obj->unk_0C = d;
    FS_ConvertPathToFileID(obj, b);
    obj->unk_18 = func_020e98b4(c << 3);
    return 1;
}

void func_0206e854(struct UnkStruct_0206e854 *self)
{
    u32 prod;

    prod = self->unk_08 * self->unk_0C;
    if (self->unk_10 == 0) {
        self->unk_10 = (u32) func_020e98b4(prod);
    }
    func_02050974(&data_021c8188);
    func_020647ec(self->data, self->unk_10, prod, 0);
}

void func_0206e83c(void *arg0)
{
    int condition_value0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) arg0 + 0x10))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x10) = 0;
    }
}

void func_0206e808(void *arg)
{
    unsigned int *p = (unsigned int *) arg;
    unsigned int zero = 0;
    unsigned int neg_one = 0xFFFFFFFF;

    p[0] = zero;
    p[5] = neg_one;
    p[3] = zero;
    p[2] = zero;

    if (p[4] != 0) {
        func_020e9898((int) ((void *) p[4]));
        p[4] = 0;
    }

    if (p[6] != 0) {
        func_020e9898((int) ((void *) p[6]));
        p[6] = 0;
    }
}

char *func_0206e7bc(UnkStruct_0206e7bc *a, unsigned int i)
{
    if (a->unk_10 != 0) {
        return a->unk_10 + a->unk_08 * i;
    }
    if (a->unk_14 == (i >> 3)) {
        return a->unk_18 + a->unk_08 * (i & 7);
    }
    if (a->unk_18 == 0) {
        goto ret0;
    }
    func_0206e778((void *) a, i);
    {
        int off = a->unk_08 * (i & 7);
        a->unk_14 = i >> 3;
        return a->unk_18 + off;
    }
ret0:
    return 0;
}

void func_0206e778(void *selfv, unsigned int idx)
{
    struct UnkStruct_0206e778 *self = (struct UnkStruct_0206e778 *) selfv;
    char buf[0x4c];
    unsigned int shifted = idx >> 3;
    func_02050974(((char *) &data_021c8188));
    FS_InitFile(buf);
    if (FS_OpenFileFast(buf, self->id) != 0) {
        int scaled = self->unk_08 << 3;
        int mulres = shifted * scaled;
        func_02064658(buf, self->unk_18, scaled, mulres);
        FS_CloseFile(buf);
    }
}
