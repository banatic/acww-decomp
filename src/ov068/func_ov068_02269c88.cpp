/* func_ov068_02269c88 @ 0x02269c88, 0x34c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct SomeState SomeState;

class Object {
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
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual int v47();
};

struct SomeState {
    u8 pad_00[0x1c];
    u8 unk_1C;
    u8 pad_1D[0x20 - 0x1d];
    int unk_20;
};

extern "C" {
extern Object *func_0201ce50(Object *obj);
extern int func_ov068_0226c0e0(SomeState *self, Object *obj);
extern int func_0202e174(Object *obj);
extern void func_0201ce5c(Object *obj, int a);
extern void func_0201ce44(Object *obj, int a);
extern void func_ov068_0226cce8(SomeState *self, Object *obj, int a);
extern void func_ov068_0226cbf4(SomeState *self);
extern int func_0201ce38(Object *obj);
extern int func_ov068_0226a098(SomeState *self, Object *obj);
extern int func_ov068_0226a020(SomeState *self, Object *obj, int a);
extern void func_0202e194(Object *obj);
extern int func_ov068_02269fd4(SomeState *self, Object *obj, int a);
extern void func_ov068_0226ad78(SomeState *self, Object *obj, int a, int b, int c);
extern int func_ov068_0226a0dc(SomeState *self, Object *obj);
extern int func_02019de8(void *p);
extern int func_02019e00(void *p);
extern int func_02019df8(void *p);
extern int func_020984e8(void);
extern void func_ov068_02269b88(SomeState *self, Object *obj);
extern int func_020644cc(int n);
extern void func_ov068_0226ad44(SomeState *self, Object *obj, void *data, int a, int b, int c);
extern void func_02019c90(void *p, int a, int b, int c);

extern u8 data_ov068_02276740[];
extern u8 data_ov068_0227679c[];
extern u16 data_020c80f8;

inline void talk(Object *obj)
{
    if (func_02019e00((u8 *) obj + 0x564) != 8) {
        return;
    }
    if (func_02019df8((u8 *) obj + 0x564) == 0) {
        return;
    }
    if ((*((u8 *) obj + 0x19c) != 0 && func_02019de8((u8 *) obj + 0x564) != 0) ||
        (*((u8 *) obj + 0x19c) == 0 &&
         (((u32) (*(int *) ((u8 *) obj + 0x190) << 4) >> 16) == 0 || func_02019de8((u8 *) obj + 0x564) != 0))) {
        func_02019c90((u8 *) obj + 0x564, 1, 0, data_020c80f8);
    }
}

void func_ov068_02269c88(SomeState *self, Object *obj)
{
    Object *other;
    int a;
    int flagA;
    int flagB;

    other = func_0201ce50(obj);
    if (func_ov068_0226c0e0(self, obj) != 0 && func_0202e174(obj) == 0 && other != 0 && other->v47() != 0) {
        func_0201ce5c(obj, 0);
        func_0201ce44(obj, 0);
        func_ov068_0226cce8(self, obj, 0x13);
        func_ov068_0226cbf4(self);
        return;
    }

    if (func_0201ce38(obj) != 0) {
        goto Ltalk;
    }

    a = func_ov068_0226a098(self, obj);
    if (func_ov068_0226a020(self, obj, a) != 0) {
        func_0202e194(obj);
        if (other != 0) {
            func_0202e194(other);
        }
        self->unk_1C = 3;
        return;
    }

    if (func_ov068_02269fd4(self, obj, a) != 0) {
        func_0202e194(obj);
        if (other != 0) {
            func_0202e194(other);
        }
        self->unk_1C = 3;
        func_ov068_0226ad78(self, obj, 2, 1, 1);
        if (other == 0) {
            return;
        }
        func_ov068_0226ad78(self, other, 2, 1, 1);
        return;
    }

    if (func_ov068_0226a0dc(self, obj) == 0) {
        func_0202e194(obj);
        if (other != 0) {
            func_0202e194(other);
        }
        self->unk_1C = 3;
        return;
    }

    flagA = 0;
    if (func_02019de8((u8 *) obj + 0x564) != 0 &&
        (func_02019e00((u8 *) obj + 0x564) != 8 || func_02019df8((u8 *) obj + 0x564) == 0)) {
        flagA = 1;
    }

    flagB = 0;
    if (func_02019de8((u8 *) other + 0x564) != 0 &&
        (func_02019e00((u8 *) obj + 0x564) != 8 || func_02019df8((u8 *) obj + 0x564) == 0)) {
        flagB = 1;
    }

    if (self->unk_20 == 0) {
        if (flagA != 0) {
            if (flagB == 0) {
                return;
            }
            if (func_020984e8() == 0) {
                if (func_020644cc(2) == 0) {
                    func_ov068_0226ad44(self, obj, data_ov068_02276740, 4, 2, 1);
                    func_ov068_0226ad44(self, other, data_ov068_02276740, 4, 2, 1);
                }
                self->unk_1C = 3;
                return;
            }
            func_ov068_02269b88(self, obj);
            return;
        }
        talk(obj);
        return;
    }

    if (flagA != 0) {
        if (self->unk_20 >= 0x14 && func_020644cc(0x20) == 0) {
            func_02019c90((u8 *) obj + 0x564, 1, data_ov068_0227679c[func_020644cc(8)], data_020c80f8);
        }
    } else {
        talk(obj);
    }

    if (flagB == 0) {
        return;
    }
    if (self->unk_20 >= 0x14 && func_020644cc(0x20) == 0) {
        func_02019c90((u8 *) other + 0x564, 1, data_ov068_0227679c[func_020644cc(8)], data_020c80f8);
    }
    return;

Ltalk:
    talk(obj);
}
}
