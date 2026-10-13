/* func_ov103_0229d944 @ 0x0229d944, 0x1c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov103_0229d90c(void *);

class UnkStruct_0229d944 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229d944_2 {
    char pad_00[0x2274];
    UnkStruct_0229d944 sub;
};

extern "C" void func_ov103_0229d944(UnkStruct_0229d944_2 *arg)
{
    func_ov103_0229d90c(arg);
    arg->sub.f3();
}
