/* func_ov147_02299d58 @ 0x02299d58, 0xd0 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov147_0229aa2819func_ov147_02299d58Ev
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"

extern "C" {
extern int func_ov147_0229a614(void *);
extern void *func_020682e0(int);
extern void func_020a8164(void *, const void *);
extern int func_0209f150(const void *, int);
extern unsigned char func_ov147_02299320(void *receiver);
extern void func_02068340(void *, void *);
extern void *data_ov147_0229a8b0;
extern const char data_ov147_0229abe0[];
extern const char data_021dc7a8[];
}

struct UnkStruct_02299d58 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct UnkStruct_02299d58_2 {
    char pad_00[0x54];
    UnkStruct_02299d58 sub;
    char pad_58[0x1a];
    unsigned char unk_72;
    char pad_73[0x2f];
    unsigned char unk_A2;
    char pad_A3[0xd];
    char unk_B0;
    char pad_B1[0x43];
    unsigned char unk_F4;
};

struct Res {
    char pad_00[8];
    int unk_08;
};

void Obj_ov147_0229aa28::func_ov147_02299d58()
{
    UnkStruct_02299d58_2 *obj = (UnkStruct_02299d58_2 *) this;
    Res *r;

    if (func_ov147_0229a614(&obj->unk_B0) != 0) {
        r = (Res *) func_020682e0(0);
        obj->sub.v2();
        if (obj->unk_F4 != 0) {
            func_020a8164(&obj->sub, data_ov147_0229a8b0);
            obj->unk_72 = 0x32;
            obj->unk_F4 = 0;
        } else if (obj->unk_A2 != 0) {
            func_020a8164(&obj->sub, data_ov147_0229abe0);
            obj->unk_72 = 9;
        } else if (func_0209f150(data_021dc7a8, 0x12) != 0) {
            func_020a8164(&obj->sub, data_ov147_0229a8b0);
            obj->unk_72 = 0x24;
        } else {
            func_020a8164(&obj->sub, data_ov147_0229a8b0);
            obj->unk_72 = (unsigned char) func_ov147_02299320(&obj->sub);
        }
        func_02068340(r, &obj->sub);
        r->unk_08 = 1;
        ((Obj_ov147_0229aa28 *) obj)->func_ov147_02299fc8(2);
    }
}
