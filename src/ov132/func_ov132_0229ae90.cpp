/* func_ov132_0229ae90 @ 0x0229ae90, 0x1c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ae90 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

extern "C" void func_ov002_0220a374(UnkStruct_0229ae90 *b, int x);

class UnkStruct_0229ae90_2 {
    char pad[0x94];

  public:
    UnkStruct_0229ae90 sub;
};

extern "C" void func_ov132_0229ae90(UnkStruct_0229ae90_2 *p)
{
    func_ov002_0220a374(&p->sub, 0);
    p->sub.m3();
}
