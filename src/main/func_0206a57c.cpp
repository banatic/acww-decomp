/* func_0206a57c @ 0x0206a57c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a873c(void *src, unsigned char *dst);

class UnkStruct_0206a57c_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void method(unsigned char);
};

struct UnkStruct_0206a57c {
    char pad_00[0x24];
    void *ptr;
};

extern "C" void func_0206a57c(UnkStruct_0206a57c *self)
{
    unsigned char buf[8];
    UnkStruct_0206a57c_2 *obj = *(UnkStruct_0206a57c_2 **) ((char *) self->ptr + 0x14a8);
    func_020a873c((char *) self + 0x38, buf);
    obj->method(buf[0]);
}
