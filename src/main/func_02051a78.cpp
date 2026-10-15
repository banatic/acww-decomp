/* func_02051a78 @ 0x02051a78, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02051a78 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" int func_02051a94(void *dst, int value);

extern "C" void func_02051a78(void *dst, UnkStruct_02051a78 *obj)
{
    func_02051a94(dst, obj->v3());
}
