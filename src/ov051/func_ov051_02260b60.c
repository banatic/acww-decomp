/* func_ov051_02260b60 @ 0x02260b60, 0xbc bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260b60_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02260b60_2;

typedef struct UnkStruct_02260b60 {
    u8 a;
    u8 b;
    u16 c;
} UnkStruct_02260b60;
typedef struct Row2 {
    UnkStruct_02260b60 e[2];
} Row2;
typedef struct Row {
    int w[2];
} Row;

extern Row data_ov051_022614cc[];
extern Row2 data_020d19d0[];
extern u8 data_021f43e8;

extern int func_020a12c0(void);
extern int func_020a12d4(void);
extern int func_020984e8(void);
extern void func_02099870(void);
extern int func_020950c0(void);
extern void func_02099834(int t, int a);
extern void func_020997e0(int t, int a);
extern void func_02099808(int t, int a);
extern void func_02099704(int t, u16 *p);
extern void func_0206844c(int h, u8 *p, int k);
extern void func_ov051_0226122c(char *p, int a);

void func_ov051_02260b60(UnkStruct_02260b60_2 *self)
{
    u16 hv;
    Row2 *q;
    UnkStruct_02260b60 *p;
    int t;
    int k;
    int code;
    int w;

    if (func_020a12c0() != 0 || func_020a12d4() != 0) {
        t = func_020984e8();
        func_02099870();
        k = func_020950c0();
        if (k == 0) {
            w = data_ov051_022614cc[*(int *) (self->unk_B0 + 0x714)].w[k];
            code = (u8) w;
        } else {
            w = data_ov051_022614cc[*(int *) (self->unk_B0 + 0x714)].w[k];
            code = (u8) (w + 8);
        }
        q = &data_020d19d0[w];
        p = &q->e[k];
        func_02099834(t, code);
        func_020997e0(t, p->b);
        func_02099808(t, q->e[k].a);
        hv = p->c;
        func_02099704(t, &hv);
    }
    func_0206844c(self->unk_40, &data_021f43e8, 0);
    func_ov051_0226122c(self->unk_B0, 4);
}
