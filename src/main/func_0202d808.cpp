/* func_0202d808 @ 0x0202d808, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202d808;
typedef void (UnkStruct_0202d808::*Pmf)();
class UnkStruct_0202d808 {
  public:
    char pad_00[0xf8];
    Pmf pmf;
};
extern Pmf __ptmf_null;
extern "C" void func_0202d808(UnkStruct_0202d808 *self)
{
    if (self->pmf) {
        (self->*(self->pmf))();
        self->pmf = __ptmf_null;
    }
}
