/* func_ov114_0229d87c @ 0x0229d87c, 0x30 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020b9ccc(void *);
extern "C" void func_ov114_0229cde4(void *);
extern "C" void func_ov114_0229cda0(void *);

class UnkStruct_0229d87c {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_0229d87c_2 {
    char pad_00[0x924];
    int member_at_0924;
    char pad_928[0x121c - 0x928];
    UnkStruct_0229d87c obj;
};

extern "C" void func_ov114_0229d87c(UnkStruct_0229d87c_2 *p)
{
    func_020b9ccc(&p->member_at_0924);
    func_ov114_0229cde4(p);
    p->obj.vf3();
    func_ov114_0229cda0(p);
}
