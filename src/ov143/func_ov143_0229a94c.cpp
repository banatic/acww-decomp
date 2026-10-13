/* func_ov143_0229a94c @ 0x0229a94c, 0x18 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229a94c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_0229a94c_2 {
  public:
    char pad_00[0xac];
    UnkStruct_0229a94c sub;
};

extern "C" void func_ov143_0229a91c(UnkStruct_0229a94c_2 *obj);

extern "C" void func_ov143_0229a94c(UnkStruct_0229a94c_2 *obj)
{
    func_ov143_0229a91c(obj);
    UnkStruct_0229a94c *sub = &obj->sub;
    sub->v3();
}
