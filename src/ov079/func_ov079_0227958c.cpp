/* func_ov079_0227958c @ 0x0227958c, 0x80 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0227958c;
typedef void (UnkStruct_0227958c::*PMF)();

extern PMF __ptmf_null;

class UnkStruct_0227958c {
  public:
    char pad_00[0xb4];
    PMF pmf1;
    PMF pmf2;
};

extern "C" void func_ov079_0227958c(UnkStruct_0227958c *obj)
{
    PMF temp;
    if (obj->pmf1) {
        (obj->*obj->pmf1)();
        temp = __ptmf_null;
        obj->pmf1 = temp;
        if (obj->pmf2) {
            obj->pmf1 = obj->pmf2;
            obj->pmf2 = temp;
        }
    }
}
