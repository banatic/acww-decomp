/* func_02095fc0 @ 0x02095fc0, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct UnkStruct_02095fc0 {
    unsigned char pad_00[0x5c];
    Vec vec;
    unsigned char pad_68[0x8e - 0x68];
    s16 unk_8E;
    unsigned char pad_90[0x7f0 - 0x90];
    int unk_7F0;
} UnkStruct_02095fc0;

extern UnkStruct_02095fc0 *func_02096718(int k);
extern void func_ov004_02228774(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_02228ac4(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_02228b90(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222b85c(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222ae34(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222b2d8(UnkStruct_02095fc0 *o, int a);
extern void func_0200fa1c(Vec *out, UnkStruct_02095fc0 *o, Vec *save, s16 *ang, void *tbl);
extern int data_020d18b4;

int func_02095fc0(Vec *outv, s16 *outang)
{
    UnkStruct_02095fc0 *o;
    Vec save;
    Vec tmp;
    Vec *q;
    s16 ang;
    int v;

    o = func_02096718(4);
    if (o == 0) {
        goto fail;
    }
    q = &o->vec;
    save.x = o->vec.x;
    save.y = q->y;
    save.z = q->z;
    ang = o->unk_8E;
    v = o->unk_7F0;
    switch (v) {
        case 16:
            v = 2;
            break;
        case 0x2c:
            v = 2;
            func_ov004_02228774(o, v);
            break;
        case 0x29:
        case 0x2a:
            if (v == 0x29) {
                func_ov004_02228ac4(o, 0x2c);
            } else {
                func_ov004_02228b90(o, 0x2c);
            }
            v = 2;
            func_0200fa1c(&tmp, o, &save, &o->unk_8E, &data_020d18b4);
            q = &o->vec;
            o->vec.x = tmp.x;
            q->y = tmp.y;
            q->z = tmp.z;
            break;
        case 14:
            v = 2;
            break;
        case 9:
        case 11:
        case 12:
            v = 8;
            break;
        case 10:
            v = 2;
            func_ov004_0222b85c(o, v);
            break;
        case 15:
            v = 8;
            func_ov004_0222ae34(o, v);
            break;
        case 13:
            v = 8;
            func_ov004_0222b2d8(o, v);
            break;
    }
    q = &o->vec;
    outv->x = o->vec.x;
    outv->y = q->y;
    outv->z = q->z;
    *outang = o->unk_8E;
    o->vec.x = save.x;
    q->y = save.y;
    q->z = save.z;
    o->unk_8E = ang;
    return v;
fail:
    return 0x93;
}
