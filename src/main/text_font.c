/* text_font: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051820 @ 0x02051820, 0xa bytes, Thumb
 * func_02051810 @ 0x02051810, 0x10 bytes, Thumb
 * func_02051794 @ 0x02051794, 0x7c bytes, Thumb
 * func_02051758 @ 0x02051758, 0x3c bytes, Thumb
 * func_0205171c @ 0x0205171c, 0x3c bytes, Thumb
 * func_020516b8 @ 0x020516b8, 0x64 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    char pad_0C[8];
    char unk_14;
} UnkStruct_02051758;

struct Entry {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

struct Node {
    unsigned int *value_ptr;
    struct Entry *entries;
    unsigned char pad_08[4];
    struct Node *next;
};

typedef struct {
    u16 value;
    u16 pad;
} Entry;

typedef struct {
    u32 *countptr;
    Entry *data;
} HighTable;

typedef struct {
    u32 *lowcount;
    Entry *lowdata;
    u32 pad;
    HighTable *high;
} UnkStruct_020516b8;

extern int func_0206493c(const void *a, int b, unsigned int c, ...);
extern int func_0212a13c(void *dst, const void *src, int param);
extern int FS_OpenFile(int *dst, const void *src);
extern const unsigned char data_020dcfa8[];
extern const unsigned char data_020dcfbc[];
extern const unsigned char data_020dcfcc[];
extern unsigned int data_020cb918[2];
extern void func_020e9898(void *);
extern int FS_CloseFile(void *);

void func_02051758(UnkStruct_02051758 *p);

void func_02051820(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

int func_02051810(int arg)
{
    func_02051758((UnkStruct_02051758 *) arg);
    return arg;
}

void func_02051794(int *out, int p1, int p2, int p3, unsigned char byte_param)
{
    int local[2];
    unsigned char buffer[0x84];
    int i;

    for (i = 0; i < 2; i++) {
        int result;
        if (p2 != 0) {
            result = func_0206493c(data_020dcfa8, p1, data_020cb918[i], p2);
        } else {
            result = func_0206493c(data_020dcfbc, p1, data_020cb918[i]);
        }
        local[i] = result;
    }

    out[0] = local[0];
    out[1] = local[1];

    func_0212a13c(buffer, data_020dcfcc, p1);
    FS_OpenFile(out + 5, buffer);

    out[3] = p3;
    ((unsigned char *) out)[0x10] = byte_param;
}

void func_02051758(UnkStruct_02051758 *p)
{
    if (p->unk_00) {
        func_020e9898(p->unk_00);
        p->unk_00 = 0;
    }
    if (p->unk_04) {
        func_020e9898(p->unk_04);
        p->unk_04 = 0;
    }
    if (p->unk_08) {
        func_020e9898(p->unk_08);
        p->unk_08 = 0;
    }
    FS_CloseFile(&p->unk_14);
}

unsigned int func_0205171c(struct Node *node, unsigned int key)
{
    unsigned int result = 0;
    if (key & 0x80000000) {
        result = func_0205171c(node->next, key & 0x7fffffff);
    } else if (key < *(node->value_ptr)) {
        result = node->entries[key].unk_02;
    }
    return result;
}

int func_020516b8(UnkStruct_020516b8 *p, int key)
{
    u32 i = 0;
    int result = -1;
    u32 count;
    count = *p->lowcount;
    while (i < (*p->lowcount)) {
        int value = result;
        if (i & 0x80000000) {
            HighTable *h = p->high;
            u32 idx = i & 0x7fffffff;
            if (idx < (*h->countptr)) {
                value = h->data[idx].value;
            }
        } else if (i < (*p->lowcount)) {
            value = p->lowdata[i].value;
        }
        if (value == key) {
            result = i;
            break;
        }
        i++;
    }

    return result;
}
