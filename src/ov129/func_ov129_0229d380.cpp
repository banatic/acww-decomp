/* func_ov129_0229d380 @ 0x0229d380, 0x60 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern "C" unsigned char *func_ov129_0229d380(void *this_ptr);
extern "C" void func_ov002_02207fc0(void *);
extern "C" void func_ov002_0220a374(void *, int);
extern "C" int func_ov002_0220a768(void *, int);
extern "C" int func_ov002_0220a72c(void *, int);
extern "C" void func_ov002_0220a0b4(void *, int, int);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

class SubClass {
  public:
    virtual void vmethod0();
    virtual void vmethod1();
    virtual void vmethod2();
    virtual void vmethod3();
};

extern "C" unsigned char *func_ov129_0229d380(void *this_ptr)
{
    func_ov002_02207fc0(this_ptr);
    ((unsigned char *) this_ptr)[0xaf] = 1;
    func_ov002_0220a374((unsigned char *) this_ptr + 0x3a0, 1);
    ((SubClass *) ((unsigned char *) this_ptr + 0x3a0))->vmethod3();
    int a = func_ov002_0220a768((unsigned char *) this_ptr + 0x1d4, 4);
    int b = func_ov002_0220a72c((unsigned char *) this_ptr + 0x1d4, 4);
    func_ov002_0220a0b4((unsigned char *) this_ptr + 0x3a0, a, b);
    return func_ov002_02208098((void *) (this_ptr), 0xc);
}
