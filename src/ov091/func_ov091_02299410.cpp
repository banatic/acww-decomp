/* func_ov091_02299410 @ 0x02299410, 0x4c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov002_02207f60(void *);
extern "C" void func_0208f210(void *, int, int);
extern "C" int func_0206fe54(int);
extern "C" void func_ov002_02209eb8(void *);

class UnkStruct_02299410 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_02299410_2 {
  public:
    virtual void g0();
    virtual void g1();
    virtual int g2();
};

extern "C" int func_ov091_02299410(void *self)
{
    ((UnkStruct_02299410 *) ((char *) self + 0x434))->f3();
    int tmp = func_ov002_02207f60(self);
    func_0208f210((char *) self + 0x3bc, 0, tmp);
    if (func_0206fe54(((UnkStruct_02299410_2 *) ((char *) self + 0x3bc))->g2())) {
        func_ov002_02209eb8((char *) self + 0x434);
    }
    return 1;
}
