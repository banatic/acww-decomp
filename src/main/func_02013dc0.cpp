/* func_02013dc0 @ 0x02013dc0, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void func_02019b78(void *);
extern void func_0206ea00(int);
extern unsigned short data_020c80f8;
}
struct Trio {
    int a, b, c;
    ~Trio() {}
};
struct UnkStruct_02013dc0 {
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
    char pad2[0x78];
    char sub[4];
};
struct Ctl {
    char pad0[4];
    short w;
    short h;
    char pad1[2];
    unsigned char unk_0A;
    unsigned char unk_0B;
    char pad2[1];
    unsigned char unk_0D;
};
extern "C" void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);

extern "C" void func_02013dc0(Ctl *c, UnkStruct_02013dc0 *o)
{
    Trio t;
    Trio *s = &o->trio;
    t.a = s->a;
    t.b = s->b;
    t.c = s->c;
    if (c->unk_0D != 0) {
        func_02019d0c(&o->sub, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    func_02019b78(&o->sub);
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
