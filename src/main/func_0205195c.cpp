/* func_0205195c @ 0x0205195c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0205195c {
  public:
    virtual void v0();
    virtual void v1();
    virtual int getCount();
    virtual void *getBuffer();
};

extern "C" void MI_CpuFill8(void *dest, int ch, unsigned int n);

extern "C" void func_0205195c(UnkStruct_0205195c *obj)
{
    int size = obj->getCount() * 2;
    MI_CpuFill8(obj->getBuffer(), 0, size);
}
