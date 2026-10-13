/* func_ov009_022646b8 @ 0x022646b8, 0x60 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct Local48 {
    unsigned int b[0xc];
};

class UnkStruct_022646b8 {
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
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual int vfunc(Local48 *out);
};

extern "C" short func_0203f8d0(void *, void *);
extern "C" void func_ov009_022648a4(void *, void *);

extern "C" void func_ov009_022646b8(UnkStruct_022646b8 *self, Local48 *out)
{
    Local48 local;
    int r = self->vfunc(&local);
    if (r == 0) {
        short v = func_0203f8d0((char *) self + 0xc4, (char *) self + 0x5c);
        *(short *) ((char *) self + 0xd0) = v;
        func_ov009_022648a4(self, &local);
    }
    *(Local48 *) ((char *) self + 0x1a0) = local;
    if (out) {
        *out = local;
    }
}
