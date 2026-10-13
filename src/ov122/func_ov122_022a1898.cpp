/* func_ov122_022a1898 @ 0x022a1898, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022a1898 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual int m3();
};

extern "C" void func_ov122_022a1854(void *);

extern "C" int func_ov122_022a1898(void *arg)
{
    func_ov122_022a1854(arg);
    ((UnkStruct_022a1898 *) ((char *) arg + 0x4010))->m3();
    return ((UnkStruct_022a1898 *) ((char *) arg + 0x4058))->m3();
}
