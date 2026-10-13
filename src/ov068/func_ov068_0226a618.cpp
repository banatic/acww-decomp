/* func_ov068_0226a618 @ 0x0226a618, 0x304 bytes, Thumb, module ov068
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

struct Name {
    u16 id;
    u8 name[12];
    u8 pad_0E;
    u8 sex;
};

struct Big {
    u32 a[0x80];
    u16 b;
    u16 c[6];
    u16 d;
    u16 e[6];
    s8 unk_21C;
    u8 g;
    u16 h[10];
    u8 i;
};

struct List;

extern "C" {
extern Object *func_0201ce50(Object *obj);
extern int func_ov068_0226aca8(SomeState *self, void **out1, void **out2, int a, int b);
extern u16 *func_02080ce4(void *p);
extern Big *func_02081500(void *p);
extern void func_0207daf4(void *a, void *b);
extern void func_020801c4(void *a, void *b, int c);
extern int func_02072dd4(Big *a, Big *b);
extern Name *func_0208150c(void *p);
extern void *func_0207cec0(List *list, int i);
extern int func_02003704(Name *p);
extern int memcmp(const void *a, const void *b, int n);
extern int func_0207f1d8(void *e);
extern int func_0207cc54(int mask, int count, int n);
extern int func_0207cf74(int x);
extern void func_02080cd8(void *p, u16 *src);
extern void func_ov068_0226ae00(SomeState *self, Object *obj, void *data);
extern void func_ov068_0226ad78(SomeState *self, Object *obj, int a, int b, int c);
extern void func_020172d8(void *p, int a, u16 *src);

extern u8 data_ov068_02276754[];
extern List data_021e5a2c;

int func_ov068_0226a618(SomeState *self, Object *obj)
{
    Object *other;
    int flag;
    Name *myname;
    Name *othername;
    void *entry;
    int mask;
    int count;
    int i;
    int same;
    int nameEq;
    u16 hid;
    u16 loc30;
    u16 loc32;
    void *local_34;
    void *local_38;
    Big *mine;
    Name *ename;
    int ok;
    int r;
    u16 val;
    u16 *vp;

    other = func_0201ce50(obj);
    local_34 = 0;
    local_38 = 0;
    {
        int a = obj->v25();
        int b = other->v25();
        r = func_ov068_0226aca8(self, &local_34, &local_38, a, b);
    }
    if (r == 0) {
        self->unk_28 = other;
    } else {
        self->unk_28 = obj;
    }

    flag = 1;
    vp = func_02080ce4(local_34);
    ok = 0;
    val = *vp;
    if (val >= 0x12a8 && val <= 0x12af) {
        ok = 1;
    }
    if (ok != 0) {
        mine = func_02081500(local_34);
        func_0207daf4(local_38, local_34);
        func_020801c4(local_38, local_34, 0);

        vp = func_02080ce4(local_38);
        ok = 0;
        val = *vp;
        if (val >= 0x12a8 && val <= 0x12af) {
            ok = 1;
        }
        if (ok != 0 && func_02072dd4(func_02081500(local_38), mine) != 0) {
            myname = func_0208150c(local_34);
            othername = func_0208150c(local_38);
            flag = 0;
            local_38 = 0;
            if ((int) &data_021e5a2c != 0) {
                mask = 0;
                count = 0;
                for (i = 0; i < 8; i++) {
                    entry = func_0207cec0(&data_021e5a2c, i);
                    if (entry != 0) {
                        ename = func_0208150c(entry);
                        if (func_02003704(ename) != 0) {
                            same = 0;
                            nameEq = 0;
                            hid = ename->id;
                            if (hid == myname->id && memcmp(ename->name, myname->name, 12) == 0) {
                                nameEq = 1;
                            }
                            if (nameEq != 0 && ename->sex == myname->sex) {
                                same = 1;
                            }
                            if (same == 0) {
                                if (hid != othername->id || memcmp(ename->name, othername->name, 12) != 0 ||
                                    ename->sex != othername->sex) {
                                    vp = func_02080ce4(entry);
                                    ok = 0;
                                    val = *vp;
                                    if (val >= 0x12a8 && val <= 0x12af) {
                                        ok = 1;
                                    }
                                    if (ok == 0 || func_02072dd4(func_02081500(entry), mine) == 0) {
                                        if (func_0207f1d8(entry) != 0) {
                                            mask = (u8) (mask | (1 << i));
                                            count++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                i = func_0207cc54(mask, count, 8);
                if (func_0207cf74(i) != 0) {
                    local_38 = func_0207cec0(&data_021e5a2c, i);
                }
            }
        }

        if (local_38 != 0) {
            Big *dst = func_02081500(local_38);
            *dst = *mine;
            loc30 = 0x12a8;
            func_02080cd8(local_38, &loc30);
        }

        func_ov068_0226ae00(self, obj, data_ov068_02276754);

        if (flag != 0 && local_38 != 0) {
            func_ov068_0226ad78(self, obj, 1, 2, 0);
            func_ov068_0226ad78(self, other, 1, 2, 0);
            loc32 = 0x12a8;
            func_020172d8((u8 *) self->unk_28 + 0x564, 1, &loc32);
            self->unk_1C = 2;
        } else {
            func_ov068_0226ad78(self, obj, 1, 2, 1);
            func_ov068_0226ad78(self, other, 1, 2, 1);
            self->unk_1C = 3;
        }
        return 1;
    }
    return 0;
}
}
