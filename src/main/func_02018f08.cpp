/* func_02018f08 @ 0x02018f08, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern unsigned short data_020c80f8;
extern char data_020c8290[];

extern void *func_02019de4(void *a);
extern void func_0201a020(void *a);
extern void func_02016764(void *a1, void *a2, void *a3, int a4, unsigned char a5, int a6, int a7, int a8);
extern void func_02012444(void *a, int b, int c);
extern void func_0201a698(void *a, void *b, int c);
extern void func_02019af0(void *a, int b);
}

struct ObjA {
    unsigned char pad_00[0xa4];
    void *sub;            // 0xa4
    unsigned char unk_A8; // 0xa8
    unsigned char unk_A9; // 0xa9
};

class ObjB {
  public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual int v39();

    unsigned char pad_04[0x2a8];  // 0x4..0x2ac
    void *unk_2AC;                // 0x2ac
    unsigned char pad_2B0[0x84];  // 0x2b0..0x334
    void *unk_334;                // 0x334
    unsigned char pad_338[0xe8];  // 0x338..0x420
    void *unk_420;                // 0x420
    unsigned char pad_424[0x21];  // 0x424..0x445
    unsigned char unk_445;        // 0x445
    unsigned char pad_446[0x1e2]; // 0x446..0x628
    void *unk_628;                // 0x628
};

extern "C" int func_02018f08(ObjA *p, ObjB *q)
{
    unsigned char v;
    int r7;

    v = *(unsigned char *) ((char *) func_02019de4(p) + 0x21);
    r7 = data_020c80f8;
    if (v >= 0x3c) {
        v = 0;
    }

    p->unk_A9 = v;

    if (v == 0) {
        func_0201a020((char *) q + 0x2ac);
        r7 = q->v39();
    }

    p->sub = (void *) (data_020c8290 + 0x1c * v);
    p->unk_A8 = *(unsigned char *) ((char *) p->sub + 0x18);

    func_02016764((char *) q + 0x334, q, *(void **) p->sub, r7, p->unk_A8, 0x1000, 0, 0);

    {
        void *tmp = q->unk_628;
        if (tmp) {
            func_02012444(tmp, r7, 0);
        }
    }

    q->unk_445 = v;
    func_0201a698((char *) q + 0x420, p->sub, 0);
    func_02019af0(p, 0);

    return 1;
}
