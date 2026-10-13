/* func_020a89dc @ 0x020a89dc, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a89dc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" void func_020a89f8(void *dst, int value);

extern "C" void func_020a89dc(void *dst, UnkStruct_020a89dc *obj)
{
    func_020a89f8(dst, obj->v3());
}
