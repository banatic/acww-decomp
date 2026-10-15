/* func_0203ea80 @ 0x0203ea80, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203ea80_2 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19(void *p, int x) = 0;
};

struct UnkStruct_0203ea80 {
    unsigned char pad_00[0x10];
    void *unk_10;
    unsigned char pad_14[1];
    unsigned char unk_15;
};

extern "C" UnkStruct_0203ea80_2 *func_0203ef90(void *);
extern "C" int func_0203ed8c(int);
extern "C" int func_0203f338(void);
extern "C" void func_0203f320(void *, void *);
extern "C" void func_0203dfe4(int);
extern "C" int func_02095f08(int);

extern "C" void func_0203ea80(UnkStruct_0203ea80 *arg5, void *arg4)
{
    UnkStruct_0203ea80_2 *obj = func_0203ef90(arg5->unk_10);
    if (obj != 0) {
        if (func_0203ed8c((int) obj) != 0) {
            if (func_0203f338() == 1) {
                func_0203f320(arg5->unk_10, arg4);
            }
        }
        obj->v19(arg4, 4);
    }
    func_0203dfe4(0);
    if (arg5->unk_15 == 7) {
        func_02095f08(0);
    }
}
