/* func_02004b30 @ 0x02004b30, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0206e8d8(void);
extern "C" void func_020f2388(void *);

extern int data_021fd1bc;

class UnkStruct_02004b30 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int arg);
};

extern UnkStruct_02004b30 *data_0213fff0;
extern int data_021c67a4;
extern int data_021c679c;

extern "C" void func_02004b30()
{
    func_0206e8d8();
    func_020f2388(&data_021fd1bc);
    if (data_0213fff0 && data_021c67a4) {
        data_0213fff0->f4(data_021c679c);
    }
}
