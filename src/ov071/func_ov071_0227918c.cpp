/* func_ov071_0227918c @ 0x0227918c, 0x80 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0227918c {
  public:
    unsigned char pad_00[0xbc];
    void (UnkStruct_0227918c::*pmf1)();
    void (UnkStruct_0227918c::*pmf2)();
};

extern void (UnkStruct_0227918c::*__ptmf_null)();

extern "C" void func_ov071_0227918c(UnkStruct_0227918c *obj)
{
    if (obj->pmf1) {
        (obj->*obj->pmf1)();
        void (UnkStruct_0227918c::*saved)() = __ptmf_null;
        obj->pmf1 = saved;
        if (obj->pmf2) {
            obj->pmf1 = obj->pmf2;
            obj->pmf2 = saved;
        }
    }
}
