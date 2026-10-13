/* func_020b4e08 @ 0x020b4e08, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a8354(void *);
extern "C" void func_020a9334(void *, int);

class UnkStruct_020b4e08 {
  public:
    virtual int f0() = 0;
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
};

struct ParamType {
    char pad_00[0x24];
    void *base;
    char unk_28[4];
};

extern "C" void func_020b4e08(ParamType *param)
{
    int index = func_020a8354(&param->unk_28);
    char *p = (char *) param->base + 0x14fc;
    p += index * 0x5c;
    UnkStruct_020b4e08 *obj = (UnkStruct_020b4e08 *) p;
    int result = obj->f3();
    func_020a9334(param, result);
}
