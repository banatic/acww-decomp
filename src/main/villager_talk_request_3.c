/* villager_talk_request_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020286f8 @ 0x020286f8, 0x98 bytes, Thumb
 * func_02028648 @ 0x02028648, 0xb0 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020286f8 {
    unsigned char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_020286f8_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_020286f8 *sub;
    void *unk_104;
    unsigned char pad_108[0x1A];
    unsigned char unk_122;
    unsigned char pad_123[0x35];
    unsigned char unk_158;
    unsigned char unk_159;
};

struct UnkStruct_020286f8_3 {
    void *ptr;
    unsigned char byte;
};

typedef struct UnkStruct_02028648_3 {
    u8 pad_00[0x40];
    void *unk_40;
} UnkStruct_02028648_3;

typedef struct UnkStruct_02028648 {
    unsigned int w[8];
    u8 a;
    u8 b;
} UnkStruct_02028648;

typedef struct UnkStruct_02028648_2 {
    int a, b;
} UnkStruct_02028648_2;

extern int func_020644cc(int a);
extern unsigned int func_0208150c(void *p);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern unsigned char data_020d8d28[];
extern struct {
    unsigned int word;
    unsigned char byte;
} data_020c8c28;
extern int data_021c2a34;
extern int data_021c2a4c;
extern int data_021c2a1c;
extern const UnkStruct_02028648_2 data_020d9140;
extern unsigned int func_0202d9c4(UnkStruct_02028648_3 *c);
extern int func_0209bc40(unsigned char *);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern int func_0209a1e8(void);
extern void func_0201cfb4(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w);
extern void func_0201cf90(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w, int i, int a, int b, void *p);
extern void func_0201cec8(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w);
extern void func_0202da74(UnkStruct_02028648_3 *c, UnkStruct_02028648_2 s);
extern void func_02068388(void *h, int n);

void func_020286f8(struct UnkStruct_020286f8_2 *obj, struct UnkStruct_020286f8_3 *out)
{
    int local0;
    int local1;
    int local2;
    int local3;
    int local4;
    unsigned char table[3];

    table[0] = data_020d8d28[0];
    table[1] = data_020d8d28[1];
    table[2] = data_020d8d28[2];

    obj->unk_159 = (unsigned char) func_020644cc(3);
    obj->unk_158 = table[obj->unk_159];

    local0 = func_020036e8((unsigned char *) func_0208150c(obj->sub->unk_830));
    local1 = data_020c8c28.word;
    local2 = data_020c8c28.byte;
    local3 = (int) obj->unk_159;
    local4 = 0;

    func_0202da38(obj, &obj->unk_104, &obj->unk_122, 30, local0, local1, local2, local3, local4);

    out->ptr = &obj->unk_104;
    out->byte = obj->unk_122;
}

void func_02028648(UnkStruct_02028648_3 *c)
{
    UnkStruct_02028648 w;
    void *p;

    p = &data_021c2a34;
    switch (func_0209bc40((unsigned char *) func_0202d9c4(c))) {
        case 0xa:
            if (func_020984e8()) {
                if (func_02098eb8((int) func_02099734((int) func_020984e8())) != -1) {
                    p = &data_021c2a4c;
                }
            }
            break;
        case 0x13:
            if (func_0209a1e8() != -1) {
                p = &data_021c2a4c;
            }
            break;
    }
    func_0201cfb4(c, &w);
    func_0201cf90(c, &w, 0, 0x21, 0x21, p);
    func_0201cf90(c, &w, 1, 0x22, 0x22, &data_021c2a1c);
    w.a = 2;
    w.b = w.a - 1;
    func_0201cec8(c, &w);
    func_0202da74(c, data_020d9140);
    func_02068388(c->unk_40, 1);
}
