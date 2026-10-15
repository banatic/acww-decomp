/* func_ov068_0226a49c @ 0x0226a49c, 0x17c bytes, Thumb, module ov068
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
    virtual int v25();
};

struct SomeState {
    u8 pad_00[0x1c];
    u8 unk_1C;
    u8 pad_1D[0x28 - 0x1d];
    void *unk_28;
};

extern "C" {
extern Object *func_0201ce50(Object *obj);
extern int func_ov068_0226aca8(SomeState *self, void **out1, void **out2, int a, int b);
extern void func_0207daf4(void *a, void *b);
extern void func_020801c4(void *a, void *b, int c);
extern void func_ov068_0226ada8(SomeState *self, Object *obj, void *data);
extern void *func_0207f270(void *ptr);
extern void *func_02079464(void *ptr);
extern void func_02080bd4(void *dst, void *src);
extern void func_02080c24(void *a, void *b);
extern void func_02080c84(void *dst, void *src);
extern void *func_02080ce4(void *ptr);
extern int func_0204bcdc(void *ptr);
extern int func_0204bc64(void *ptr);
extern void func_02080cd8(void *a, void *b);
extern int func_020172d8(void *ptr, int a, void *b);
extern void func_ov068_0226ad44(SomeState *self, Object *obj, void *data, int a, int b, int c);

extern char data_ov068_02276744[];
extern char data_ov068_02276730[];

int func_ov068_0226a49c(SomeState *self, Object *obj)
{
    struct {
        u16 a;
        u16 b;
        u16 c;
        u16 d;
    } buf;
    void *local_10;
    void *local_14;
    Object *other;
    int r7;
    int stack_arg;
    unsigned int val;
    int flag;
    u16 *p;
    int result;
    int hash1;
    int hash2;

    buf.a = 0xfff1;
    local_10 = 0;
    local_14 = 0;

    other = func_0201ce50(obj);

    r7 = obj->v25();
    stack_arg = other->v25();

    r7 = func_ov068_0226aca8(self, &local_10, &local_14, r7, stack_arg);

    func_0207daf4(local_14, local_10);
    func_020801c4(local_14, local_10, 0);

    if (r7 == 0) {
        self->unk_28 = obj;
    } else {
        self->unk_28 = other;
    }

    func_ov068_0226ada8(self, obj, data_ov068_02276744);

    {
        u16 *vp = (u16 *) func_02079464(func_0207f270(local_10));
        flag = 0;
        val = *vp;
    }
    if (val < 0x1380) {
        // nothing
    } else if (val > 0x139f) {
        // nothing
    } else {
        flag = 1;
    }

    if (flag == 0) {
        func_02080bd4(&buf.b, local_10);
        buf.a = buf.b;
        func_02080c24(local_10, &buf);
    }

    func_02080c84(&buf.c, local_10);
    buf.a = buf.c;
    p = (u16 *) func_02080ce4(local_10);

    if (func_0204bcdc(p)) {
        hash1 = func_0204bc64(p);
        hash2 = func_0204bc64(&buf);
        if (hash1 == hash2) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (*p == buf.a) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result == 0) {
        func_ov068_0226ad44(self, obj, data_ov068_02276730, 4, 2, 0);
        func_ov068_0226ad44(self, other, data_ov068_02276730, 4, 2, 0);
        func_02080cd8(local_10, &buf);
        func_020172d8((void *) ((char *) self->unk_28 + 0x564), 1, &buf);
        self->unk_1C = 2;
    } else {
        func_ov068_0226ad44(self, obj, data_ov068_02276730, 4, 2, 1);
        func_ov068_0226ad44(self, other, data_ov068_02276730, 4, 2, 1);
        self->unk_1C = 3;
    }

    return 1;
}
}
