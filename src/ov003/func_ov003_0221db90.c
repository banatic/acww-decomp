/* func_ov003_0221db90 @ 0x0221db90, 0x1e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0221db90 UnkStruct_0221db90;
typedef struct SubA SubA;
typedef struct SubB SubB;
typedef struct Vtbl Vtbl;
typedef struct PType PType;

struct SubA {
    u8 pad_00[1];
    u8 unk_01;
};

struct SubB {
    u8 pad_00[0x2c];
    PType *p;
};

struct UnkStruct_0221db90 {
    SubA *a;
    SubB *b;
};

struct Vtbl {
    u8 pad_00[0x60];
    void (*func)(PType *self, u8 arg1, UnkStruct_0221db90 *ctx);
};

struct PType {
    Vtbl *vt;
};

void func_ov003_0221db90(UnkStruct_0221db90 *obj)
{
    SubB *sb = obj->b;
    PType *p = sb->p;
    if (p) {
        u8 byte = obj->a->unk_01;
        p->vt->func(p, byte, obj);
    }
}
