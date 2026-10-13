/* func_0201a304 @ 0x0201a304, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_02082e1c(void *);
extern int func_0208308c(void *);
extern void func_02078ab0(void *, int);
extern void *func_02082d34(void *);
extern int func_02078a9c(void *);
extern int func_0205db38(void *);
extern int func_0205685c(void *, int, int, int, int);
extern void func_020645d4(void *);
}
struct UnkStruct_0201a304_2 {
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
    virtual int v27();
    char pad0[0x144];
    int unk_148;
};
struct UnkStruct_0201a304 {
    char pad0[4];
    char unk_04[8];
    char unk_0C[8];
    char unk_14[8];
    char unk_1C[0x2c];
    char unk_48[0x2c];
    int unk_74;
    int unk_78;
    char pad_7C[8];
    unsigned char unk_84;
};
extern "C" int func_0201a304(UnkStruct_0201a304 *p, UnkStruct_0201a304_2 *o)
{
    int x;
    void *h;
    void *t;
    int a, b;
    x = o->v27();
    if (func_02082e1c(&p->unk_0C) == 0 && x != 0) {
        if (func_0208308c(&p->unk_0C) == 0) {
            return 0;
        }
        h = (void *) func_02082e1c(&p->unk_0C);
        func_02078ab0(h, x);
        if (func_0208308c(&p->unk_04) == 0) {
            return 0;
        }
        t = func_02082d34(&p->unk_04);
        a = o->unk_148;
        b = func_02078a9c(h);
        if (func_0205685c(&p->unk_1C, a, b, 1, func_0205db38(t)) == 0) {
            return 0;
        }
        a = o->unk_148;
        b = func_02078a9c(h);
        if (func_0205685c(&p->unk_48, a, b, 1, func_0205db38(t)) == 0) {
            return 0;
        }
        if (func_0208308c(&p->unk_14) == 0) {
            return 0;
        }
        p->unk_74 = 0x16f;
        p->unk_78 = 0x16f;
        func_020645d4(p);
        p->unk_84 = 1;
    }
    return 1;
}
