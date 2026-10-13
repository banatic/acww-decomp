/* func_0206cb88 @ 0x0206cb88, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02067a74(void *arg);
extern "C" void func_020a9334(void *obj, int value);
extern "C" void func_020a7994(void *ptr, int value);

class UnkStruct_0206cb88 {
  public:
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual int f4();
};

struct Context {
    char pad_00[0x2C];
    char *base;
};

extern "C" void func_0206cb88(Context *p)
{
    func_02067a74(p->base);
    int result1 = ((UnkStruct_0206cb88 *) (p->base + 0x1C70))->f4();
    func_020a9334(p, result1);
    int result2 = ((UnkStruct_0206cb88 *) (p->base + 0x1C70))->f4();
    func_020a7994(p->base + 0x1A58, result2);
    *(int *) (p->base + 0x1A60) = 0;
}
