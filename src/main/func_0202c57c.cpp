/* func_0202c57c @ 0x0202c57c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202c57c {
    int a;
    int b;
};
class UnkStruct_0202c57c_2 {
  public:
    virtual int m00();
    virtual int m01();
    virtual int m02();
    virtual int m03();
    virtual int m04();
    virtual int m05();
    virtual int m06();
    virtual int m07();
    virtual int m08();
    virtual int m09();
    virtual int m10();
    virtual int m11();
    virtual int m12();
    virtual int m13();
    virtual int m14();
    virtual int m15();
    virtual int m16();
    virtual int m17();
    virtual int m18();
    virtual int m19();
    virtual int m20();
    virtual int m21();
    virtual int m22();
    virtual int m23();
    virtual int m24();
    virtual int m25();
};
extern "C" int func_0207f1c8(int arg);
extern "C" int func_0209b5e8(int arg);
extern "C" void func_0209e474(UnkStruct_0202c57c *arg);
extern "C" void func_0202c704(UnkStruct_0202c57c_2 *p0, int x, int p1, int p2, int p3, UnkStruct_0202c57c *arg);
extern "C" void func_0202c5dc(UnkStruct_0202c57c_2 *p0, int x, int p1, int p2, int p3, UnkStruct_0202c57c *arg);
extern "C" void func_0202c57c(UnkStruct_0202c57c_2 *p0, int p1, int p2, int p3)
{
    int x;
    UnkStruct_0202c57c local;
    if (p0->m25() == 0) {
        return;
    }
    x = func_0209b5e8(func_0207f1c8(p0->m25()));
    local.a = 0;
    local.b = 0;
    func_0209e474(&local);
    func_0202c704(p0, x, p1, p2, p3, &local);
    func_0202c5dc(p0, x, p1, p2, p3, &local);
}
