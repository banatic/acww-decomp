/* func_ov115_0229e354 @ 0x0229e354, 0x18 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov115_0229e334(void *obj);

class UnkStruct_0229e354 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
};

extern "C" int func_ov115_0229e354(void *obj)
{
    func_ov115_0229e334(obj);
    UnkStruct_0229e354 *b = reinterpret_cast<UnkStruct_0229e354 *>(reinterpret_cast<char *>(obj) + 0x94);
    return b->v3();
}
