/* func_02071aa8 @ 0x02071aa8, 0x2b8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 w[0x80];
} Big;
typedef struct {
    u16 v[6];
} UnkStruct_02071aa8;
typedef struct {
    u16 v[10];
} A10;

typedef struct {
    Big big;
    u16 unk_200;
    UnkStruct_02071aa8 unk_202;
    u16 unk_20E;
    UnkStruct_02071aa8 unk_210;
    char unk_21C;
    u8 unk_21D;
    A10 unk_21E;
    u8 unk_232;
} UnkStruct_02071aa8_2;

extern int func_02071d60(void *a);
extern UnkStruct_02071aa8_2 *func_02071604(int k, int a);
extern void func_02072dbc(UnkStruct_02071aa8_2 *p);
extern void __register_global_object(UnkStruct_02071aa8_2 *p, void *fn, void *node);
extern void func_020720ac(int k, int a);
extern int func_02073d90(void *p);
extern void func_02073820(void *h);
extern void func_020737f0(void *h, unsigned int *u, int n);
extern void func_02073770(void *h, int a, int b);
extern void func_02072da4(void);

extern int data_021d0474;
extern UnkStruct_02071aa8_2 data_021d05cc;
extern int data_021d0498;
extern void *data_020ccf94;

int func_02071aa8(void *a0, int a1, void *a2, int a3, u8 a5)
{
    int k1;
    int k2;
    UnkStruct_02071aa8_2 *p1;
    UnkStruct_02071aa8_2 *p2;
    unsigned int u;
    void *h;

    k1 = func_02071d60(a0);
    k2 = func_02071d60(a2);
    if (k1 == 7 || k2 == 7) {
        return 0;
    }
    p1 = func_02071604(k1, a1);
    p2 = func_02071604(k2, a3);
    if ((data_021d0474 & 1) == 0) {
        func_02072dbc(&data_021d05cc);
        __register_global_object(&data_021d05cc, (void *) func_02072da4, &data_021d0498);
        data_021d0474 |= 1;
    }

    data_021d05cc.big = p2->big;
    data_021d05cc.unk_200 = p2->unk_200;
    data_021d05cc.unk_202 = p2->unk_202;
    data_021d05cc.unk_20E = p2->unk_20E;
    data_021d05cc.unk_210 = p2->unk_210;
    data_021d05cc.unk_21C = p2->unk_21C;
    data_021d05cc.unk_21D = p2->unk_21D;
    data_021d05cc.unk_21E = p2->unk_21E;
    data_021d05cc.unk_232 = p2->unk_232;

    p2->big = p1->big;
    p2->unk_200 = p1->unk_200;
    p2->unk_202 = p1->unk_202;
    p2->unk_20E = p1->unk_20E;
    p2->unk_210 = p1->unk_210;
    p2->unk_21C = p1->unk_21C;
    p2->unk_21D = p1->unk_21D;
    p2->unk_21E = p1->unk_21E;
    p2->unk_232 = p1->unk_232;

    p1->big = data_021d05cc.big;
    p1->unk_200 = data_021d05cc.unk_200;
    p1->unk_202 = data_021d05cc.unk_202;
    p1->unk_20E = data_021d05cc.unk_20E;
    p1->unk_210 = data_021d05cc.unk_210;
    p1->unk_21C = data_021d05cc.unk_21C;
    p1->unk_21D = data_021d05cc.unk_21D;
    p1->unk_21E = data_021d05cc.unk_21E;
    p1->unk_232 = data_021d05cc.unk_232;

    func_020720ac(k1, a1);
    func_020720ac(k2, a3);
    if (a5 != 0 && func_02073d90(data_020ccf94) != 0) {
        k1 &= 0xf;
        u = (u & ~0xf) | k1;
        a1 &= 0x3ff;
        u = (u & 0xffffc00f) | (a1 << 4);
        k2 &= 0xf;
        u = (u & 0xfffc3fff) | (k2 << 14);
        a3 &= 0x3ff;
        u = (u & 0xf003ffff) | (a3 << 18);
        u = u | 0x10000000;
        u = u & 0x1fffffff;
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &u, 4);
        func_02073770(h, 0x15, 4);
    }
    return 1;
}
