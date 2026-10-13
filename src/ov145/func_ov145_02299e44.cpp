/* func_ov145_02299e44 @ 0x02299e44, 0x1a bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02299e44 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
extern "C" void func_ov002_0220a0ec(UnkStruct_02299e44 *);
extern "C" void func_ov145_02299e44(char *self)
{
    func_ov002_0220a0ec((UnkStruct_02299e44 *) (self + 0xc8));
    ((UnkStruct_02299e44 *) (self + 0xc8))->v3();
}
