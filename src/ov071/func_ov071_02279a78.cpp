/* func_ov071_02279a78 @ 0x02279a78, 0xb4 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02279a78 UnkStruct_02279a78;
typedef struct UnkStruct_02279a78_2 UnkStruct_02279a78_2;
struct UnkStruct_02279a78_2 {
    u8 p0[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
};
typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02279a78_3;
struct UnkStruct_02279a78 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
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
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual int slot98();
    u8 p0[0x564 - 4];
    u8 unk_564[0x729 - 0x564];
    u8 unk_729;
    u8 p1[0x72c - 0x72a];
    int unk_72C;
    u8 p2[0x734 - 0x730];
    UnkStruct_02279a78_2 *unk_734;
};
extern "C" void func_ov071_02279d04(UnkStruct_02279a78 *, int);
extern "C" int func_02019de8(u8 *);
extern "C" int func_ov071_02279b2c(UnkStruct_02279a78 *, int);
extern "C" int func_02019c20(u8 *, int, int, int, int, int);
extern "C" int func_02019d0c(u8 *, int, int, int, int, int, int, int, int, int, int);
extern u16 data_020c80f8;

extern "C" void func_ov071_02279a78(UnkStruct_02279a78 *self)
{
    UnkStruct_02279a78_2 *t;
    UnkStruct_02279a78_3 *q;
    int r;

    t = self->unk_734;
    if (t != 0) {
        if (func_02019de8(self->unk_564) == 0) {
            return;
        }
        if (func_ov071_02279b2c(self, 0x3000) != 0) {
            r = self->slot98();
            func_02019c20(self->unk_564, 1, r, 0, data_020c80f8, 0);
            self->unk_729 = 2;
            return;
        }
        t = self->unk_734;
        q = (UnkStruct_02279a78_3 *) ((int) t + 0x5c);
        func_02019d0c(self->unk_564, 2, 1, t->unk_5C, q->unk_08, 0, 0, 0, 0, data_020c80f8, 0);
        self->unk_72C = 0x12c;
        self->unk_729 = 1;
    } else {
        func_ov071_02279d04(self, 3);
    }
}
