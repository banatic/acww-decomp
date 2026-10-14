/* func_ov070_0227986c @ 0x0227986c, 0x44 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

class ClassName {
  public:
    char pad_00[0xB8];
    void (ClassName::*pmf)();
};

extern void (ClassName::*__ptmf_null)();

extern "C" void func_ov070_0227986c(ClassName *obj)
{
    if (obj->pmf != 0) {
        (obj->*obj->pmf)();
        obj->pmf = __ptmf_null;
    }
}
