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
extern Pmf data_0213dd98;
extern "C" void func_ov082_02279204(UnkStruct_02279204 *self)
{
    if (self->a) {
        (self->*(self->a))();
        Pmf t = data_0213dd98;
        self->a = t;
        if (self->b) {
            self->a = self->b;
            self->b = t;
        }
    }
}
