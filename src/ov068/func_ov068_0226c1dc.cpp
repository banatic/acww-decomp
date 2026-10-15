/* func_ov068_0226c1dc @ 0x0226c1dc, 0x344 bytes, Thumb, module ov068
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
    virtual Object *v25();
};

struct SomeState {
    u8 pad_00[0x34];
    s16 unk_34;
    s16 unk_36;
};

struct Pair {
    int a;
    int b;
};

extern "C" {
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_020ba4e4(void);
extern void *func_0208150c(Object *p);
extern int func_02003704(void *p);
extern void *func_0207f270(Object *p);
extern int func_020794cc(void *p);
extern void func_0209e474(Pair *p);
extern void func_ov068_0226d408(Object *obj);
extern void func_0202e118(u16 *dst, Object *obj);
extern int func_0209c38c(int x);
extern void func_0209bd98(u16 *dst, int x);
extern void func_02080c60(u16 *dst, Object *r6);
extern void func_0202e0c8(Object *obj, u16 *src);
extern void func_ov068_0226cce8(SomeState *self, Object *obj, int a);
extern void func_ov068_0226cce4(SomeState *self, int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
}

inline int inR(const u16 *p, u16 lo, u16 hi)
{
    return *p >= lo && *p <= hi;
}

extern "C" {

int func_ov068_0226c1dc(SomeState *self, Object *obj)
{
    int x;
    u16 a0;
    u16 a1;
    u16 a2;
    u16 a3;
    u16 a4;
    u16 a5;
    u16 a6;
    u16 a7;
    u16 a8;
    u16 a9;
    u16 a10;
    u16 a11;
    u16 a12;
    u16 a13;
    Pair pair;
    Object *o;
    int lang;
    int ok;
    int eq;
    int h;
    s16 v34;
    u16 t;

    if (func_02019e00((u8 *) obj + 0x564) != 0) {
        goto Lfail;
    }
    if (func_02019de8((u8 *) obj + 0x564) == 0) {
        goto Lfail;
    }

    o = obj->v25();
    pair.a = 0;
    pair.b = 0;
    x = 7;
    lang = func_020ba4e4();
    if (o != 0 && func_02003704(func_0208150c(o)) != 0 && func_0207f270(o) != 0) {
        x = func_020794cc(func_0207f270(o));
    }
    func_0209e474(&pair);

    v34 = self->unk_34;
    if (v34 != 0 && self->unk_36 != 0) {
        goto L3ca;
    }

    if (v34 == 0) {
        func_ov068_0226d408(obj);
        if (o != 0 && func_02003704(func_0208150c(o)) != 0 && func_0207f270(o) != 0) {
            x = func_020794cc(func_0207f270(o));
        }
        self->unk_34 = 0x2ee0;
    }

    func_0202e118(&a1, obj);
    if (a1 == 0xfff1) {
        a0 = 0xfff1;
        if (func_0209c38c(x) != 0) {
            func_0209bd98(&a2, x);
            a0 = a2;
        }
        t = *(volatile u16 *) &a0;
        if ((a0 == 0xfff1 || (t >= 0x1378 && t <= 0x1378)) && lang == 1) {
            func_02080c60(&a3, o);
            a0 = a3;
        }
        self->unk_36 = -1;
        if (a0 == 0xfff1) {
            goto Lfail;
        }
        func_0202e0c8(obj, &a0);
        func_ov068_0226cce8(self, obj, 0xf);
        func_ov068_0226cce4(self, 0);
        return 1;
    }

    func_0202e118(&a4, obj);
    if (inR(&a4, 0x1380, 0x139f)) {
        if (lang == 1) {
            goto Lfail;
        }
        self->unk_36 = 0x12c;
        func_ov068_0226cce8(self, obj, 0x10);
        func_ov068_0226cce4(self, 0);
        return 1;
    }

    func_0209bd98(&a5, x);
    func_0202e118(&a6, obj);
    if (func_0204bcdc(&a5) != 0) {
        h = func_0204bc64(&a5);
        if (h == func_0204bc64(&a6)) {
            eq = 1;
        } else {
            eq = 0;
        }
    } else {
        if (a5 == a6) {
            eq = 1;
        } else {
            eq = 0;
        }
    }
    if (eq == 0) {
        func_ov068_0226cce8(self, obj, 0x10);
        func_ov068_0226cce4(self, 0);
        self->unk_36 = 0x12c;
        return 1;
    }
    self->unk_36 = -1;
    goto Lfail;

L3ca:

    func_0202e118(&a7, obj);
    if (a7 == 0xfff1) {
        if (lang != 1) {
            goto Lfail;
        }
        func_02080c60(&a8, o);
        func_0202e0c8(obj, &a8);
        func_ov068_0226cce8(self, obj, 0xf);
        func_ov068_0226cce4(self, 0);
        self->unk_36 = -1;
        return 1;
    }

    func_0202e118(&a9, obj);
    if (inR(&a9, 0x1380, 0x139f)) {
        if (lang == 1) {
            goto Lfail;
        }
        self->unk_36 = 0x12c;
        func_ov068_0226cce8(self, obj, 0x10);
        func_ov068_0226cce4(self, 0);
        return 1;
    }

    func_0202e118(&a10, obj);
    if (inR(&a10, 0x1378, 0x1378) && lang == 1) {
        func_ov068_0226cce8(self, obj, 0x10);
        func_ov068_0226cce4(self, 0);
        self->unk_36 = 0x12c;
        return 1;
    }

    func_0202e118(&a11, obj);
    func_0209bd98(&a12, x);
    if (func_0204bcdc(&a11) != 0) {
        h = func_0204bc64(&a11);
        if (h == func_0204bc64(&a12)) {
            eq = 1;
        } else {
            eq = 0;
        }
    } else {
        if (a11 == a12) {
            eq = 1;
        } else {
            eq = 0;
        }
    }
    if (eq != 0) {
        goto Lfail;
    }
    func_ov068_0226cce8(self, obj, 0x10);
    func_ov068_0226cce4(self, 0);
    self->unk_36 = 0x12c;
    return 1;

Lfail:
    return 0;
}
}
