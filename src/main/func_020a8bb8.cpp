/* func_020a8bb8 @ 0x020a8bb8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a8bb8 {
  public:
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
};

extern "C" void *func_020a8be4(char *a, void *v);
extern "C" void func_020a9b1c(char *a, char *b);

extern "C" void *func_020a8bb8(char *a, char *b)
{
    void *ret = func_020a8be4(a, ((UnkStruct_020a8bb8 *) b)->f3());
    func_020a9b1c(a + 8, b + 8);
    return ret;
}
