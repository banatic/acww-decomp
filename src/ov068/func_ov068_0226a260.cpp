/* func_ov068_0226a260 @ 0x0226a260, 0x180 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226a260 {
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
struct Rec {
    unsigned int a[0x80];
    unsigned short b;
    unsigned short c[6];
    unsigned short d;
    unsigned short e[6];
    signed char unk_21C;
    unsigned char g;
    unsigned short h[10];
    unsigned char i;
};
struct St {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad_1D[0xb];
    char *unk_28;
};
extern "C" {
extern UnkStruct_0226a260 *func_0201ce50(UnkStruct_0226a260 *);
extern int func_ov068_0226aca8(St *, void **, void **, void *, void *);
extern unsigned short *func_02080ce4(void *);
extern Rec *func_02081500(void *);
extern Rec *func_ov068_0226ac40(St *, Rec *);
extern void func_0207daf4(void *, void *);
extern void func_020801c4(void *, void *, int);
extern void func_ov068_0226ae00(St *, UnkStruct_0226a260 *, const void *);
extern void func_ov068_0226ad78(St *, char *, int, int, int);
extern void func_02080cd8(void *, unsigned short *);
extern int func_020172d8(void *, int, unsigned short *);
extern const char data_ov068_02276784[];
}

extern "C" int func_ov068_0226a260(St *s, UnkStruct_0226a260 *o)
{
    unsigned short w[2];
    void *v1;
    void *v2;
    UnkStruct_0226a260 *p;
    Rec *r;
    Rec *dst;
    int ok;
    unsigned short k;
    unsigned short *kp;

    p = func_0201ce50(o);
    v1 = 0;
    v2 = 0;
    if (func_ov068_0226aca8(s, &v1, &v2, o->v25(), p->v25()) == 0) {
        s->unk_28 = (char *) o;
    } else {
        s->unk_28 = (char *) p;
    }
    r = 0;
    kp = func_02080ce4(v1);
    ok = 0;
    k = *kp;
    if (k >= 0x12a8 && k <= 0x12af) {
        ok = 1;
    }
    if (ok != 0) {
        r = func_02081500(v1);
    }
    r = func_ov068_0226ac40(s, r);
    if (r != 0) {
        func_0207daf4(v2, v1);
        func_020801c4(v2, v1, 0);
        func_ov068_0226ae00(s, o, data_ov068_02276784);
        func_ov068_0226ad78(s, s->unk_28, 1, 2, 0);
        dst = func_02081500(v1);
        *dst = *r;
        w[0] = 0x12a8;
        func_02080cd8(v1, &w[0]);
        w[1] = 0x12a8;
        func_020172d8(s->unk_28 + 0x564, 1, &w[1]);
        s->unk_1C = 2;
        return 1;
    }
    return 0;
}
