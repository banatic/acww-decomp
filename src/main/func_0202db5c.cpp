/* func_0202db5c @ 0x0202db5c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202db5c;
typedef void (UnkStruct_0202db5c::*Pmf)();
class UnkStruct_0202db5c {
  public:
    char pad_00[0xd8];
    Pmf a;
    Pmf b;
};
extern Pmf data_0213dd98;
extern "C" void func_0202db5c(UnkStruct_0202db5c *self)
{
    if (self->a) {
        (self->*(self->a))();
        Pmf t = data_0213dd98;
        self->a = t;
        if (self->b) {
            self->a = self->b;
        }
        self->b = t;
    }
}
