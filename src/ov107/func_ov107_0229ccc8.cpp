/* func_ov107_0229ccc8 @ 0x0229ccc8, 0x20 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

class UnkStruct_0229ccc8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov107_0229ccc8(void *self)
{
    char *base = (char *) self;
    func_ov002_0220a0ec(base + 0x22b4);
    ((UnkStruct_0229ccc8 *) (base + 0x22b4))->v3();
}
