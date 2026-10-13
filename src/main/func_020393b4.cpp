/* func_020393b4 @ 0x020393b4, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020393b4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void called();
    char pad_04[0xb4];
};

struct Container {
    int header;
    UnkStruct_020393b4 arr[4];
};

extern "C" void func_02039540(Container *p);
extern "C" void func_02039510(Container *p);
extern "C" void func_020394a4(Container *p);

extern "C" void func_020393b4(Container *p)
{
    int i;
    func_02039540(p);
    func_02039510(p);
    for (i = 0; i < 4; i++) {
        p->arr[i].called();
    }
    func_020394a4(p);
}
