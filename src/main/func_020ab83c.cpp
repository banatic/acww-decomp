/* func_020ab83c @ 0x020ab83c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020ab83c {
  public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual int m2() = 0;
    virtual int m3() = 0;
};

extern int data_021f4670;

extern "C" void func_020ab91c(int *g, int a, int b);
extern "C" unsigned char func_020a9a08(int *g, int p1);
extern "C" int func_020a9938(int *g, int p2);
extern "C" int func_020a9530(int *g);
extern "C" void func_020a82bc(int p3, int d);
extern "C" void func_020a99d8(int *g);
extern "C" void func_020ab90c(int *g);

extern "C" int func_020ab83c(UnkStruct_020ab83c *obj, int p1, int p2, int p3)
{
    int a = obj->m3();
    int b = obj->m2();
    func_020ab91c(&data_021f4670, a, b);
    func_020a9a08(&data_021f4670, p1);
    int c = func_020a9938(&data_021f4670, p2);
    int d = func_020a9530(&data_021f4670);
    func_020a82bc(p3, d);
    func_020a99d8(&data_021f4670);
    func_020ab90c(&data_021f4670);
    return c;
}
