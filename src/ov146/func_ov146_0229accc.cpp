/* func_ov146_0229accc @ 0x0229accc, 0x1c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov146_0229aca0(void *p);

class UnkStruct_0229accc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov146_0229accc(void *arg)
{
    func_ov146_0229aca0(arg);
    ((UnkStruct_0229accc *) ((char *) arg + 0x15cc))->v3();
}
