/* func_020acab8 @ 0x020acab8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020aca7c(void);
extern "C" int func_020aca74(void *p);
extern "C" void func_0208ea70(void *p, int a, int b);

class UnkStruct_020acab8_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct UnkStruct_020acab8 {
    char pad_00[0x10];
    UnkStruct_020acab8_2 base;
};

extern "C" void func_020acab8(UnkStruct_020acab8 *param)
{
    int a = func_020aca7c();
    int b = func_020aca74(param);
    func_0208ea70(&param->base, a, b);
    (&param->base)->m3();
}
