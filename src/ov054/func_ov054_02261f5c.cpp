/* func_ov054_02261f5c @ 0x02261f5c, 0x1a bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261f5c {
  public:
    virtual void virt0();
    virtual void virt1();
    virtual void virt2();
    char pad_04[0xac];
    int value;
};

extern "C" void func_ov054_02261f5c(UnkStruct_02261f5c *obj, int value)
{
    obj->virt2();
    obj->value = value;
}
