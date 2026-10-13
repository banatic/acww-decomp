/* func_0205401c @ 0x0205401c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02089954(void);
extern "C" void func_0208997c(void);
extern "C" void func_02041bb8(void);
extern "C" void func_02002e14(void);
extern "C" void func_02002354(void);
extern "C" void func_02001ecc(void);

extern volatile int data_021c8c9c;

class SomeObject {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern SomeObject *data_021c8ca0;

extern "C" void func_0205401c(void)
{
    int flag = data_021c8c9c;
    volatile unsigned short *reg = (volatile unsigned short *) 0x04000304;
    *reg = (unsigned short) ((*reg & 0xffff7fff) | (flag << 15));

    func_02089954();
    func_0208997c();
    func_02041bb8();
    func_02002e14();
    func_02002354();

    if (data_021c8ca0 != 0) {
        data_021c8ca0->m2();
    }

    func_02001ecc();
}
