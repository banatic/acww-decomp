/* func_02010538 @ 0x02010538, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02010538;

struct UnkStruct_02010538_3 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual int v21(UnkStruct_02010538 *);
};

struct UnkStruct_02010538 {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad_60[0x8e - 0x60];
    short unk_8E;
    u8 pad_90[0x13c - 0x90];
    UnkStruct_02010538_3 *unk_13C;
    u8 unk_140;
    u8 pad_141[0x158 - 0x141];
    int unk_158;
    int unk_15C;
    int unk_160;
    u8 pad_164[0x170 - 0x164];
    int unk_170;
};

struct UnkStruct_02010538_2 {
    int x;
    int y;
    int z;
};

extern int data_020d72f8;

extern "C" {
extern int func_0203e31c(void);
extern int func_0200f290(UnkStruct_02010538 *, int);
extern int func_0200dc04(UnkStruct_02010538 *);
extern int func_0203e0e0(UnkStruct_02010538 *, UnkStruct_02010538_3 *);
extern int func_0203ef5c(UnkStruct_02010538 *);
extern int func_0203ee34(UnkStruct_02010538_3 *, UnkStruct_02010538 *);
extern int func_02010030(UnkStruct_02010538 *);
extern int func_02010004(UnkStruct_02010538 *, int);
extern void func_0200fa1c(UnkStruct_02010538_2 *, UnkStruct_02010538 *, int *, short *, void *);

int func_02010538(UnkStruct_02010538 *a1)
{
    volatile int save[3];
    UnkStruct_02010538_2 tmp;
    int r;

    if (func_0203e31c() || func_0200f290(a1, 0x13)) {
        return 0;
    }
    if (func_0200dc04(a1)) {
        func_0203e0e0(a1, a1->unk_13C);
        if (a1->unk_13C == 0) {
            if (func_0203ef5c(a1)) {
                return 1;
            }
        } else if (func_0203ee34(a1->unk_13C, a1) == 0) {
            if (a1->unk_13C->v21(a1)) {
                return 1;
            }
        } else {
            return 1;
        }
    }
    if (func_02010030(a1)) {
        return 1;
    }
    if (a1->unk_140 && a1->unk_170 == 2) {
        save[0] = a1->unk_158;
        save[1] = a1->unk_15C;
        save[2] = a1->unk_160;
        func_0200fa1c(&tmp, a1, &a1->unk_5C, &a1->unk_8E, &data_020d72f8);
        a1->unk_158 = tmp.x;
        a1->unk_15C = tmp.y;
        a1->unk_160 = tmp.z;
        r = func_02010004(a1, 0);
        a1->unk_158 = save[0];
        a1->unk_15C = save[1];
        a1->unk_160 = save[2];
        return r;
    }
    return 0;
}
}
