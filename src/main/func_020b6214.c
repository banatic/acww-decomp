/* func_020b6214 @ 0x020b6214, 0x1e0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020b6214 {
    u8 kind;
    u8 pad_01[0x13];
    u8 flagA;
    u8 flagB;
    u8 pad_16[0x6];
} UnkStruct_020b6214;
typedef struct Desc {
    UnkStruct_020b6214 *data;
    u8 count;
    u8 pad_05[3];
} Desc;
typedef struct GObj {
    u8 pad_00[0xc];
    Desc *desc;
} GObj;
typedef struct UnkStruct_020b6214_2 {
    u32 pad_00;
} UnkStruct_020b6214_2;
extern GObj *data_021f6948;
extern UnkStruct_020b6214_2 data_021f69a0;
extern UnkStruct_020b6214_2 data_021f69b8;
extern int func_0204e414(UnkStruct_020b6214 *base, Desc *desc);
extern int func_0204e108(int ret, u32 *v, u32 *w1, u32 *w2);
extern int func_0204e08c(int ret, u32 *v, u32 *w1, u32 *w2);
extern u8 func_020b64dc(UnkStruct_020b6214_2 *obj);
extern u32 *func_020b64ec(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64e8(UnkStruct_020b6214_2 *obj);
extern u16 func_020b64e0(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64d4(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64cc(UnkStruct_020b6214_2 *obj);
inline u32 inline_fn(u32 *arg0)
{
    return arg0[1];
}

int func_020b6214(int unused, int idx, u8 *status, u32 *outVec, u32 *outWord, u16 *outShort, u32 *outWord2, u32 *outWord3,
                  u8 *outByte1, u8 *outByte2)
{
    UnkStruct_020b6214 *base;
    Desc *desc;
    UnkStruct_020b6214 *el;
    u32 w1;
    u32 w2;
    u32 v[3];
    int ret;
    int kind;
    int count;
    if (idx == (-1)) {
        goto fail;
    }
    if (data_021f6948 == 0) {
        goto fail;
    }
    desc = data_021f6948->desc;
    if (desc == 0) {
        goto fail;
    }
    base = desc->data;
    if (base == 0) {
        goto fail;
    }
    count = desc->count;
    if ((idx < 0) || (idx >= count)) {
        goto fail;
    }
    el = &base[idx];
    ret = func_0204e414(base, desc);
    kind = el->kind - 0x3c;
    switch (kind) {
        case 2:
            if (func_0204e108(ret, v, &w1, &w2)) {
                v[2] += 0x1000;
                *status = 0;
                outVec[0] = v[0];
                outVec[1] = inline_fn(v);
                outVec[2] = v[2];
                *outWord = 0x0f000000;
                *outShort = 0;
                *outWord2 = w1;
                *outWord3 = w2;
                *outByte1 = el->flagA;
                *outByte2 = el->flagB;
            }
            return 3;

        case 1:
            if (func_0204e08c(ret, v, &w1, &w2)) {
                v[2] += 0x1000;
                *status = 0;
                outVec[0] = v[0];
                outVec[1] = inline_fn(v);
                outVec[2] = v[2];
                *outWord = 0x0f000000;
                *outShort = 0;
                *outWord2 = w1;
                *outWord3 = w2;
                *outByte1 = el->flagA;
                *outByte2 = el->flagB;
            }
            return 3;

        case 3:
            *status = func_020b64dc(&data_021f69a0);
            {
                u32 *p = func_020b64ec(&data_021f69a0);
                outVec[0] = p[0];
                outVec[1] = inline_fn(p);
                outVec[2] = p[2];
            }
            *outWord = func_020b64e8(&data_021f69a0);
            *outShort = func_020b64e0(&data_021f69a0);
            *outWord2 = func_020b64d4(&data_021f69a0);
            *outWord3 = func_020b64cc(&data_021f69a0);
            *outByte1 = el->flagA;
            *outByte2 = el->flagB;
            return 2;

        case 0:
            *status = func_020b64dc(&data_021f69b8);
            {
                u32 *p = func_020b64ec(&data_021f69b8);
                outVec[0] = p[0];
                outVec[1] = inline_fn(p);
                outVec[2] = p[2];
            }
            *outWord = func_020b64e8(&data_021f69b8);
            *outShort = func_020b64e0(&data_021f69b8);
            *outWord2 = func_020b64d4(&data_021f69b8);
            *outWord3 = func_020b64cc(&data_021f69b8);
            *outByte1 = (*el).flagA;
            *outByte2 = el->flagB;
            return 3;

        default:
            goto fail_default;
    }

fail_default:
    return 1;

fail:
    return 1;
}
