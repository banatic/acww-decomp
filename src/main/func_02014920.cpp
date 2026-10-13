/* func_02014920 @ 0x02014920, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0203ad88(void);
extern "C" unsigned int func_0203ad30(void);
extern "C" void *func_02015d78(void *, unsigned char);
extern "C" void func_0201a7cc(void *, int);
extern "C" int func_0201c250(void *);
extern "C" void func_020668d8(void *, void *, int);
extern "C" void func_02094fd4(void *);
extern "C" void func_02094fbc(void *);

typedef struct PtrStruct {
    int unk_00;
    int unk_04;
    int unk_08;
} PtrStruct;

typedef struct UnkStruct_02014920 {
    char pad_00[0x40];
    PtrStruct *unk_40;
    char pad_44[0x55 - 0x44];
    unsigned char unk_55;
    char pad_56[0xac - 0x56];
    unsigned char unk_AC;
} UnkStruct_02014920;

class UnkStruct_02014920_2 {
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
    virtual void method_74(void *arg);
};

extern "C" int func_02014920(void *self)
{
    UnkStruct_02014920 *s = (UnkStruct_02014920 *) self;
    int ret;
    char buf[0x24];
    void *p;
    void *obj;
    int val;

    if (s->unk_40 == 0) {
        goto fail;
    }
    if (s->unk_40->unk_04 != 5) {
        goto fail;
    }
    if (func_0203ad88() != 0) {
        if (func_0203ad30() >= 0x11) {
            goto fail;
        }
    }
    p = func_02015d78(s, s->unk_55);
    if (p) {
        func_0201a7cc((char *) p + 0x418, 0x418);
    }
    s->unk_55 = (s->unk_55 + 1) & 1;
    obj = func_02015d78(s, s->unk_55);
    if (!obj) {
        goto fail;
    }
    func_02094fd4(buf);
    ((UnkStruct_02014920_2 *) obj)->method_74(buf);
    val = func_0201c250(obj);
    func_020668d8(self, buf, val);
    s->unk_40->unk_08 = 1;
    s->unk_AC = 3;
    func_02094fbc(buf);
    ret = 1;
    goto done;
fail:
    ret = 0;
done:
    return ret;
}
