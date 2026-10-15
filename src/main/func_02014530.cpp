/* func_02014530 @ 0x02014530, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void func_0206ea00(int);
extern unsigned short data_020c80f8;
}
struct Trio {
    int a, b, c;
    ~Trio() {}
};
struct UnkStruct_02014530;
extern "C" UnkStruct_02014530 *func_020160d4(void *);
struct UnkStruct_02014530 {
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
    virtual int v31();
    virtual void v32();
    virtual int v33();
    char pad0[0x58];
    Trio trio;
    char pad1[0x480];
    unsigned int flags;
    char pad_4EC[0x78];
    char sub[4];
    char pad_568[0xcc];
    void *unk_634;
};
struct Ctl {
    char pad0[4];
    short w;
    short h;
    char pad1[2];
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
};
extern "C" int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern "C" void func_0203af08(Trio *, Trio *);
extern "C" int func_0203af80(Trio *);
extern "C" void func_02014530(Ctl *c, UnkStruct_02014530 *o)
{
    Trio t;
    Trio *s = &o->trio;
    t.a = s->a;
    t.b = s->b;
    t.c = s->c;
    func_02019d0c(&o->sub, 3, 2, 0, 0, c->w, c->h, 0, 0, data_020c80f8, 0);

    if (c->unk_0C == 0) {
        UnkStruct_02014530 *m = (UnkStruct_02014530 *) o->unk_634;
        if (m != 0 && func_020160d4(m) != 0) {
            Trio t2;
            Trio *s2 = &func_020160d4(m)->trio;
            t2.a = s2->a;
            t2.b = s2->b;
            t2.c = s2->c;
            t.b += 0x2000;
            t2.b += 0x2000;
            func_0203af08(&t, &t2);
        } else {
            t.b += 0x2000;
            func_0203af80(&t);
        }
    }
    if ((o->flags & 2) == 0) {
        c->unk_0B = 1;
    }
    o->flags |= 2;
    if (o->v31() != 0) {
        int r = o->v33();
        if (r != 0xffff) {
            func_0206ea00(r);
        }
        o->v32();
    }
    c->unk_0A = 0;
}
