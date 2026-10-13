/* func_020679b0 @ 0x020679b0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class VBase {
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
    virtual void *Call(void);
};

struct UnkStruct_020679b0 {
    unsigned char pad_00[0x14a8];
    VBase *unk_14A8;
    unsigned char pad_14AC[0x1ccc - 0x14a8 - 4];
    unsigned char buf[1];
};

extern "C" void func_020a8c1c(void *);
extern "C" void func_0207ef00(void *, void *);

extern "C" int func_020679b0(UnkStruct_020679b0 *self)
{
    int result;
    void *obj;

    obj = self->unk_14A8->Call();
    result = 0;
    func_020a8c1c(self->buf);
    if (obj != 0) {
        func_0207ef00(obj, self->buf);
        result = 1;
    }
    return result;
}
