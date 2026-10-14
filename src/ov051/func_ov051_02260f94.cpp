/* func_ov051_02260f94 @ 0x02260f94, 0x44 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260f94 {
  public:
    char pad_00[0xB4];
    void (UnkStruct_02260f94::*pmf)();
};

extern void (UnkStruct_02260f94::*__ptmf_null)();

extern "C" void func_ov051_02260f94(UnkStruct_02260f94 *obj)
{
    if (obj->pmf) {
        (obj->*obj->pmf)();
        obj->pmf = __ptmf_null;
    }
}
