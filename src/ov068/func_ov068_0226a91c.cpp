/* func_ov068_0226a91c @ 0x0226a91c, 0x1b8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

struct UnkStruct_0226a91c {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void *v25();
};
struct Id {
    unsigned short id;
    char nm[0xc];
    unsigned char pad;
    unsigned char unk_0F;
};
// Both are the same helper type, run through its out-of-line pair.
struct A {
    char pad[0x1c];
};
struct B {
    char pad[0x1c];
};
struct St {
    char pad_00[0x1c];
    unsigned char unk_1C;
};
extern "C" {
extern UnkStruct_0226a91c *func_0201ce50(UnkStruct_0226a91c *);
extern int func_ov068_0226aca8(St *, void **, void **, void *, void *);
extern void func_02080af0(void *, void *, int);
extern void func_0207daf4(void *, void *);
extern void func_020801c4(void *, void *, int);
extern int func_020a89ac(A *, B *);
extern Id *func_0208150c(void *);
extern int func_02003704(Id *);
extern void *func_0207cec0(const void *, int);
extern int memcmp(const void *, const void *, int);
extern int func_0207cc54(int, int, int);
extern int func_0207cf74(int);
extern void func_02080a94(void *, A *);
extern void func_ov068_0226ada8(St *, UnkStruct_0226a91c *, const void *);
extern void func_ov068_0226ad78(St *, void *, int, int, int);
extern const char data_021e5a2c[];
extern const char data_ov068_0227678c[];
}

extern "C" int func_ov068_0226a91c(St *s, UnkStruct_0226a91c *o)
{
    void *v1;
    void *v2;
    UnkStruct_0226a91c *p;
    Id *q1;
    Id *q2;
    Id *c;
    void *e;
    int mask, cnt, i;
    int m1, m2;
    unsigned short w;
    int sel;

    p = func_0201ce50(o);
    v1 = 0;
    v2 = 0;
    func_ov068_0226aca8(s, &v1, &v2, o->v25(), p->v25());
    A a;
    B b;
    func_020821bc(&a);
    func_020821bc(&b);
    func_02080af0(v1, &a, 0);
    func_02080af0(v2, &b, 0);
    func_0207daf4(v2, v1);
    func_020801c4(v2, v1, 0);
    if (func_020a89ac(&a, &b) != 0) {
        q1 = func_0208150c(v1);
        q2 = func_0208150c(v2);
        mask = 0;
        v2 = 0;
        if ((void *) data_021e5a2c != (void *) 0) {
            cnt = 0;
            for (i = 0; i < 8; i++) {
                e = func_0207cec0(data_021e5a2c, i);
                if (e != 0) {
                    c = func_0208150c(e);
                    if (func_02003704(c) != 0) {
                        m1 = 0;
                        m2 = 0;
                        w = c->id;
                        if (w == q1->id && memcmp(c->nm, q1->nm, 0xc) == 0) {
                            m2 = 1;
                        }
                        if (m2 != 0 && c->unk_0F == q1->unk_0F) {
                            m1 = 1;
                        }
                        if (m1 == 0) {
                            if (w != q2->id || memcmp(c->nm, q2->nm, 0xc) != 0 || c->unk_0F != q2->unk_0F) {
                                func_02080af0(e, &b, 0);
                                if (func_020a89ac(&a, &b) == 0) {
                                    mask |= 1 << i;
                                    mask = (unsigned char) mask;
                                    cnt++;
                                }
                            }
                        }
                    }
                }
            }
            sel = func_0207cc54(mask, cnt, 8);
            if (func_0207cf74(sel) != 0) {
                v2 = func_0207cec0(data_021e5a2c, sel);
            }
        }
    }
    if (v2 != 0) {
        func_02080a94(v2, &a);
    }
    func_ov068_0226ada8(s, o, data_ov068_0227678c);
    func_ov068_0226ad78(s, o, 1, 2, 1);
    func_ov068_0226ad78(s, p, 1, 2, 1);
    s->unk_1C = 3;
    func_020821a4(&b);
    func_020821a4(&a);
    return 1;
}
