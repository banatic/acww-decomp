/* func_020c2f60 @ 0x020c2f60, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020c2f60 {
    int a;
    int b;
    int c;
} UnkStruct_020c2f60;

extern int func_0201ae40(u8 *p);
extern int func_0201aff8(u8 *p, u8 *q, int n);
extern void func_02019d0c(u8 *p, int a, int b, int c, int d, int e, int g, int h, int i, int j, int k);
extern int func_020c3060(u8 *p, UnkStruct_020c2f60 *s, void *t);
extern void func_0201afd4(u8 *p, UnkStruct_020c2f60 *s);
extern int func_0201afc0(u8 *p);
extern void func_0201af48(u8 *p);

extern u16 data_020c80f8;
extern int data_021fbcc0;
extern int data_021fbccc;

int func_020c2f60(u8 *p)
{
    u8 *pa;
    UnkStruct_020c2f60 loc;
    u8 *pb;
    int kind;
    int ret;

    pa = p + 0x564;
    pb = p + 0x350;
    kind = func_0201ae40(p + 0x3a8);
    ret = 0;
    if (!func_0201aff8(pb, p, 1)) {
        switch (kind) {
            case 3:
                func_02019d0c(pa, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                ret = 1;
                break;
            case 1:
                if (func_020c3060(p, &loc, &data_021fbccc)) {
                    func_0201afd4(pb, &loc);
                } else {
                    func_02019d0c(pa, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
                ret = 1;
                break;
            case 2:
                if (func_020c3060(p, &loc, &data_021fbcc0)) {
                    func_0201afd4(pb, &loc);
                } else {
                    func_02019d0c(pa, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
                ret = 1;
                break;
        }
    } else {
        if (func_0201afc0(pb)) {
            func_0201af48(pb);
        }
    }
    return ret;
}
