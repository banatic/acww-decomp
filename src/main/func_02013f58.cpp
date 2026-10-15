/* func_02013f58 @ 0x02013f58, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02013f58 {
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

    char pad0[0x3c];
    void *unk_40;
};

typedef struct UnkStruct_02013f58_2 {
    char pad0[4];
    int unk_04;
} UnkStruct_02013f58_2;

extern "C" void func_0203ee08(unsigned char *, void *);
extern "C" void *func_02015d68(void *p);
extern "C" void func_0201a7cc(void *p);
extern "C" int func_020160d4(unsigned int);
extern "C" int func_02019e00(unsigned char *);
extern "C" int func_02019de8(unsigned char *);
extern "C" int func_02016024(void *, int, int);
extern "C" void func_0201462c(unsigned char *, unsigned char *);
extern "C" void func_02016110(void *);
extern "C" void func_0201481c(void *, void *);

extern "C" void func_02013f58(unsigned char *param0, unsigned char *param1)
{
    UnkStruct_02013f58 *r4;
    UnkStruct_02013f58_2 *sub;
    void *p;
    int r7;
    int local0;

    r4 = *(UnkStruct_02013f58 **) (param1 + 0x634);
    if (r4 == 0) {
        goto END;
    }
    sub = (UnkStruct_02013f58_2 *) r4->unk_40;
    if (sub == 0) {
        goto END;
    }
    if (sub->unk_04 != 0) {
        goto BRANCH_A;
    }

    r4->v31();
    func_0203ee08(param1, r4);

    p = func_02015d68(r4);
    if (p != 0) {
        func_0201a7cc((unsigned char *) p + 0x418);
    }

    r7 = 0;
    if (func_020160d4((unsigned int) r4) != 0) {
        if (func_02019e00((unsigned char *) (func_020160d4((unsigned int) r4) + 0x564)) == 8) {
            if (func_02019de8((unsigned char *) (func_020160d4((unsigned int) r4) + 0x564)) == 0) {
                r7 = 1;
            }
        }
    }

    local0 = 0;
    if (func_02019e00(param1 + 0x564) == 8) {
        if (func_02019de8(param1 + 0x564) == 0) {
            local0 = 1;
        }
    }

    if (r7 != 0 || local0 != 0) {
        if (local0 != 0) {
            func_02016024(r4, 0, 0);
        }
        if (r7 != 0) {
            func_02016024(r4, 0, 1);
        }
        param0[0xa] = 2;
    } else {
        func_0201462c(param0, param1);
        param0[0xa] = 1;
        param0[8] = 5;
    }
    goto END;

BRANCH_A:
    func_02016110(r4);
    func_0201481c(param0, param1);

END:
    return;
}
