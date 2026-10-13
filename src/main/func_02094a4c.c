/* func_02094a4c @ 0x02094a4c, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct Node {
    struct Node *next;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 unk_14[0x24 - 0x14];
    u16 unk_24;
    u16 unk_26;
    u8 unk_28[0x38 - 0x28];
    int unk_38;
    int unk_3C;
    int unk_40;
} Node;

typedef struct {
    u8 unk_00[0x30];
    int unk_30;
    u8 unk_34[0x3c - 0x34];
    int unk_3C;
} UnkStruct_02094a4c;

typedef struct {
    Node *pad_00;
    int d1;
    Node *unk_08;
} Head;

extern Vec data_021fbee8;
extern void func_02034270(UnkStruct_02094a4c *, Vec *, int, int);
extern void func_0203423c(UnkStruct_02094a4c *);
extern void func_02094cf8(int, int, Vec *, int, int, int);

int func_02094a4c(Head *h, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    int ret;
    Vec v;
    UnkStruct_02094a4c ctx;
    Node *n;

    n = h->unk_08;
    v.x = data_021fbee8.x;
    v.y = data_021fbee8.y;
    v.z = data_021fbee8.z;
    ret = 0;
    while (n) {
        ret = 1;
        v.x = n->unk_08 + n->unk_38;
        v.y = n->unk_0C + n->unk_3C;
        v.z = n->unk_10 + n->unk_40;
        func_02034270(&ctx, &v, 0, 0);
        if (ctx.unk_30) {
            if (v.y <= ctx.unk_3C) {
                v.y = ctx.unk_3C;
                if (p1 != -1) {
                    func_02094cf8(p1, 0x64, &v, 0, 0, p2);
                }
                if (p3 != -1) {
                    func_02094cf8(p3, 0x64, &v, 0, 0, p4);
                }
                n->unk_26 = n->unk_24;
            }
        } else {
            if (v.y <= 0) {
                if (p5 != -1) {
                    v.y = 0;
                    func_02094cf8(p5, 0x64, &v, 0, 0, p6);
                }
                if (p7 != -1) {
                    v.y = 0;
                    func_02094cf8(p7, 0x64, &v, 0, 0, p8);
                }
                n->unk_26 = n->unk_24;
            }
        }
        n = n->next;
        func_0203423c(&ctx);
    }
    return ret;
}
