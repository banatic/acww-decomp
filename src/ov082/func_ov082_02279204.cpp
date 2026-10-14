/* func_ov082_02279204 @ 0x02279204, 0x80 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279204;
typedef void (UnkStruct_02279204::*Pmf)();
class UnkStruct_02279204 {
  public:
    char pad_00[0xb4];
    Pmf a;
    Pmf b;
};
extern Pmf __ptmf_null;
extern "C" void func_ov082_02279204(UnkStruct_02279204 *self)
{
    if (self->a) {
        (self->*(self->a))();
        Pmf t = __ptmf_null;
        self->a = t;
        if (self->b) {
            self->a = self->b;
            self->b = t;
        }
    }
}
