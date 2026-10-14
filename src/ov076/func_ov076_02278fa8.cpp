/* func_ov076_02278fa8 @ 0x02278fa8, 0x44 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278fa8 {
  public:
    char pad_00[0xbc];
    void (UnkStruct_02278fa8::*pmf)();
};

extern void (UnkStruct_02278fa8::*__ptmf_null)();

extern "C" void func_ov076_02278fa8(UnkStruct_02278fa8 *self)
{
    if (self->pmf) {
        (self->*self->pmf)();
        self->pmf = __ptmf_null;
    }
}
