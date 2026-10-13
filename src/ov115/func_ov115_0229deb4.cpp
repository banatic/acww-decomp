/* func_ov115_0229deb4 @ 0x0229deb4, 0x1c bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

class VTableClass {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov002_0220a374(void *p, int n);

extern "C" void func_ov115_0229deb4(void *self)
{
    func_ov002_0220a374((char *) self + 0x94, 0);
    VTableClass *obj = (VTableClass *) ((char *) self + 0x94);
    obj->v3();
}
