/* func_020798a0 @ 0x020798a0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020798a0 {
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkStruct_020798a0_2 {
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
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual int alive();
    char pad_04[0x58];
    UnkStruct_020798a0 sub;
};

extern "C" UnkStruct_020798a0_2 *func_020825d8(void *key);

extern "C" int func_020798a0(void *key, int a, int b, int c, int d)
{
    UnkStruct_020798a0_2 *o = func_020825d8(key);
    UnkStruct_020798a0 *s;
    if (o == 0) {
        goto zero;
    }
    if (o->alive() == 0) {
        goto zero;
    }
    s = &o->sub;
    return o->sub.unk_00 > a && o->sub.unk_00 < b && s->unk_08 > c && s->unk_08 < d;
zero:
    return 0;
}
