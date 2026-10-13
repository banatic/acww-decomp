/* func_ov145_0229a7d8 @ 0x0229a7d8, 0x4c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov145_02299da4(void *);
extern "C" void func_ov002_0220af74(void *);
extern "C" void func_020b9ccc(void *);

class VirtualObj {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov145_0229a7d8(void *base)
{
    func_ov145_02299da4(base);
    func_ov002_0220af74((char *) base + 0x174);
    func_020b9ccc((char *) base + 0xad8);
    func_020b9ccc((char *) base + 0xafc);
    func_020b9ccc((char *) base + 0xb20);
    ((VirtualObj *) ((char *) base + 0x12c))->v3();
}
