/* post_clerk_talk_3: 3 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02260b70 @ 0x02260b70, 0x90 bytes, Thumb
 * func_ov054_02260b30 @ 0x02260b30, 0x3e bytes, Thumb
 * func_ov054_02260a88 @ 0x02260a88, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02260b70 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02260b70;

typedef struct Elem {
    int w[3];
} Elem;

struct UnkStruct_02260b30 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

extern Elem data_ov054_02262fac[];
extern u8 data_ov054_02262984[];
extern int func_020160b4(UnkStruct_02260b70 *self);
extern int func_020ab504(int a);
extern int func_0202ea40(char *p, u8 *q, int a);
extern void func_0202ea28(char *p, u8 *q);
extern void func_0206844c(int h, u8 *p, int k);
extern int func_020984e8(void);
extern void func_0203d480(int);
extern void func_0203d394(void);
extern int func_0202e9fc(void);
extern int func_02099020(void *, int);
extern int func_02060d3c(void *);
extern unsigned char func_ov054_02260484(void *receiver);
extern void func_0202eac8(void *, int, int, int);
extern void func_02068388(void *, int);
extern const int data_ov054_022629b4[];
extern const int data_ov054_02262f50[];
extern unsigned char data_021ebcd4[];

void func_ov054_02260b70(UnkStruct_02260b70 *self, unsigned int callbackArgument1)
{
    u8 m[2];
    int h;
    int a;
    int code;
    int idx;
    int v;

    h = self->unk_40;
    a = func_020ab504(func_020160b4(self));
    code = 0xff;
    idx = 1;
    v = (int) self->unk_1E;
    if (v >= 0 && v <= 0x19) {
        if (a == 1) {
            code = data_ov054_02262984[*(int *) (self->unk_B0 + 0x80c)];
            idx = 0;
        } else if (func_0202ea40(self->unk_B0, m, 0) != 0) {
            func_0202ea28(self->unk_B0, m);
        }
    }
    if (code != 0xff) {
        int k;
        k = data_ov054_02262fac[*(int *) (self->unk_B0 + 0x808)].w[idx];
        m[1] = (u8) code;
        func_0206844c(h, &m[1], k);
    }
}

void func_ov054_02260b30(struct UnkStruct_02260b30 *obj, unsigned int callbackArgument1)
{
    int v;

    v = func_020ab504((int) ((void *) func_020160b4((UnkStruct_02260b70 *) ((void *) obj))));
    func_020984e8();

    if (obj->unk_1E == 0x12) {
        switch (v) {
            case 0:
                func_0203d480(0);
                break;
            case 1:
                func_0203d480(1);
                break;
        }
        func_0203d394();
    }
}

void func_ov054_02260a88(void *obj, int event)
{
    void *h, *sub;
    int st;

    sub = *(void **) ((char *) obj + 0x40);
    h = (void *) func_020984e8();
    *(int *) ((char *) obj + 0xb4) = 0;
    if (func_0202e9fc() == 0) {
        *(int *) ((char *) obj + 0xb4) = 2;
    } else if (func_02099020(h, 1) == 0 && func_02060d3c((void *) data_021ebcd4) != 0) {
        if (func_ov054_02260484(*(void **) ((char *) obj + 0xb0)) != 0) {
            *(int *) ((char *) obj + 0xb4) = 4;
        } else {
            *(int *) ((char *) obj + 0xb4) = 1;
        }
    } else {
        if (func_ov054_02260484(*(void **) ((char *) obj + 0xb0)) != 0) {
            *(int *) ((char *) obj + 0xb4) = 3;
        }
    }
    st = *(int *) ((char *) obj + 0xb4);
    func_0202eac8(obj, data_ov054_02262f50[st], data_ov054_022629b4[st], data_ov054_022629b4[st] - 1);
    func_02068388(sub, 1);
}
