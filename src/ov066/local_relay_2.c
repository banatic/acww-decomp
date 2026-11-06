/* local_relay_2: 4 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226bc4c @ 0x0226bc4c, 0x16c bytes, ARM
 * func_ov066_0226bbb4 @ 0x0226bbb4, 0x98 bytes, ARM
 * func_ov066_0226bb7c @ 0x0226bb7c, 0x38 bytes, ARM
 * func_ov066_0226b9b8 @ 0x0226b9b8, 0x1c4 bytes, ARM
 */

#include "types.h"

typedef struct Src {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
} Src;

typedef struct UnkStruct_0226bc4c {
    char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    char pad_0D[0x14 - 0xd];
    unsigned char unk_14;
    char pad_15[0x17 - 0x15];
    unsigned char unk_17;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned short unk_20;
    unsigned short unk_22;
    unsigned short unk_24;
    char pad_26[0x28 - 0x26];
    int unk_28;
    char pad_2C[0x3c - 0x28 - 4];
    unsigned int unk_3C;
} UnkStruct_0226bc4c;

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    unsigned char pad_08[0x20 - 8];
    u8 id;
} Node;

typedef struct Cfg {
    unsigned char pad_00[0x1a];
    u16 size;
} Cfg;

struct Node_0226bb7c {
    int unk_00;
    struct Node_0226bb7c *next;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
};

typedef void (*Fn)(void);

typedef struct UnkStruct_0226b9b8 {
    u8 unk_00;
    u8 pad_01[7];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[8];
    void *unk_18;
    u8 pad_1C[0x14];
    void *unk_30;
} UnkStruct_0226b9b8;

typedef struct UnkStruct_0226b9b8_2 {
    u8 pad_00[0x9c];
    unsigned int (*unk_9C)(void);
    Fn unk_A0;
    Fn unk_A4;
    Fn unk_A8;
    void (*unk_AC)(int, int, int, int);
    int (*unk_B0)(int, int, int, int);
    int (*unk_B4)(void);
    void (*unk_B8)(int, char *, unsigned int);
    void (*unk_BC)(int);
} UnkStruct_0226b9b8_2;

typedef struct UnkStruct_0226b9b8_3 {
    u8 pad_00[0xb];
    u8 count;
} UnkStruct_0226b9b8_3;

typedef struct UnkStruct_0226b9b8_4 {
    u8 pad_00[6];
    u8 unk_06;
} UnkStruct_0226b9b8_4;

extern UnkStruct_0226bc4c *data_ov066_0226bdec;
void *func_ov066_02266908(u32 size, u32 align);
void MI_CpuFill8(void *dest, u8 data, u32 size);
extern UnkStruct_0226b9b8 *data_ov066_0226be08;
extern UnkStruct_0226b9b8_2 *data_ov066_0226bdf4;
extern void func_ov066_02269b88(void);
extern int WM_SetPortCallback(u32 port, void *cb, void *arg);
extern int WM_SetIndCallback(void *cb);
extern unsigned int func_ov066_0226a960(void);
extern void func_ov066_0226af3c(void);
extern void func_ov066_0226af04(void);
extern void func_ov066_0226ae1c(int a, int b, int c, int callback);
extern int func_ov066_0226b81c(int a, int b, int c, int callback);
extern int func_ov066_0226b8bc(void);
extern void func_ov066_0226b90c(void);
extern void func_ov066_0226aeb8(int peer);
extern void func_ov066_0226923c(void *argument0);
extern void func_ov066_0226aab8(void *argument0);
extern void func_ov066_0226b818(void);

void func_ov066_0226bc4c(Src *p)
{
    unsigned short a = p->unk_06;
    unsigned char b = p->unk_04;
    unsigned short mulval = (unsigned short) (a * b + 4);

    data_ov066_0226bdec->unk_28 = p->unk_00;
    data_ov066_0226bdec->unk_3C &= ~8;
    data_ov066_0226bdec->unk_3C &= ~1;
    data_ov066_0226bdec->unk_3C |= 0x20;
    data_ov066_0226bdec->unk_3C |= 0x40;
    data_ov066_0226bdec->unk_3C |= 0x80;
    data_ov066_0226bdec->unk_3C &= ~0x200;
    data_ov066_0226bdec->unk_3C &= ~0x100;
    data_ov066_0226bdec->unk_3C |= 4;
    data_ov066_0226bdec->unk_3C |= 2;

    data_ov066_0226bdec->unk_17 = p->unk_07;
    data_ov066_0226bdec->unk_08 = 0xfe;
    data_ov066_0226bdec->unk_09 = 1;
    data_ov066_0226bdec->unk_0A = p->unk_04 - 1;
    data_ov066_0226bdec->unk_0B = p->unk_04;
    data_ov066_0226bdec->unk_0C = p->unk_05;
    data_ov066_0226bdec->unk_18 = a;
    data_ov066_0226bdec->unk_1A = mulval;
    data_ov066_0226bdec->unk_1C = mulval;
    data_ov066_0226bdec->unk_1E = a;
    data_ov066_0226bdec->unk_22 = 0x1e;
    data_ov066_0226bdec->unk_20 = 0x5a;
    data_ov066_0226bdec->unk_24 = 0xc8;
    data_ov066_0226bdec->unk_14 = 4;
}

Node *func_ov066_0226bbb4(int n)
{
    u32 stride;
    u32 total;
    Node *cur;
    Node *head;
    u16 i;
    Node *prev;
    int last;
    stride = ((*(Cfg **) &data_ov066_0226bdec)->size + 0x43) & ~0x1f;
    total = stride * n;
    cur = (Node *) func_ov066_02266908(total, 0x20);
    MI_CpuFill8(cur, 0, total);
    head = cur;
    last = n - 1;
    i = 0;
    {
        u8 b = (u8) i;
        while ((int) i < last) {
            cur->id = b;
            i = (u16) (i + 1);
            cur->next = (Node *) ((u8 *) cur + stride);
            prev = cur;
            cur = cur->next;
            cur->prev = prev;
        }
    }
    cur->id = (u8) last;
    cur->next = head;
    head->prev = cur;
    return head;
}

void func_ov066_0226bb7c(struct Node_0226bb7c *node, int count)
{
    unsigned short i = 0;
    if (count > 0) {
        unsigned short v = i;
        do {
            i = i + 1;
            node->unk_08 = v;
            node->unk_0A = v;
            node->unk_0C = v;
            node = node->next;
        } while (i < count);
    }
}

int func_ov066_0226b9b8(UnkStruct_0226b9b8_4 *p)
{
    u32 n;

    if (data_ov066_0226be08 != NULL) {
        return (int) p;
    }
    func_ov066_0226bc4c((Src *) p);
    func_ov066_02269b88();
    data_ov066_0226bdf4->unk_9C = func_ov066_0226a960;
    data_ov066_0226bdf4->unk_A0 = func_ov066_0226af3c;
    data_ov066_0226bdf4->unk_A4 = func_ov066_0226af04;
    data_ov066_0226bdf4->unk_AC = func_ov066_0226ae1c;
    data_ov066_0226bdf4->unk_B0 = func_ov066_0226b81c;
    data_ov066_0226bdf4->unk_B4 = func_ov066_0226b8bc;
    data_ov066_0226bdf4->unk_A8 = func_ov066_0226b90c;
    data_ov066_0226bdf4->unk_BC = func_ov066_0226aeb8;

    data_ov066_0226be08 = (UnkStruct_0226b9b8 *) func_ov066_02266908(0x34, 4);

    n = (u32) (*(UnkStruct_0226b9b8_3 **) &data_ov066_0226bdec)->count << 4;
    data_ov066_0226be08->unk_30 = func_ov066_02266908(n, 4);
    MI_CpuFill8(data_ov066_0226be08->unk_30, 0, n);

    data_ov066_0226be08->unk_08 = (void *) func_ov066_0226bbb4(3);
    data_ov066_0226be08->unk_0C = (void *) func_ov066_0226bbb4(3);

    n = (u32) (*(UnkStruct_0226b9b8_3 **) &data_ov066_0226bdec)->count << 2;
    data_ov066_0226be08->unk_18 = func_ov066_02266908(n, 4);
    MI_CpuFill8(data_ov066_0226be08->unk_18, 0, n);

    data_ov066_0226be08->unk_00 = p->unk_06;
    WM_SetPortCallback(0xc, (void *) (void (*)(void *)) func_ov066_0226923c, NULL);
    WM_SetPortCallback(0xd, (void *) (void (*)(void *)) func_ov066_0226aab8, NULL);
    WM_SetIndCallback((void *) func_ov066_0226b818);
    return func_ov066_0226a960();
}
