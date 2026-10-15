/* func_0202dc04 @ 0x0202dc04, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202dc04;
typedef void (UnkStruct_0202dc04::*Pmf)();
class UnkStruct_0202dc04 {
  public:
    char pad_00[0xf0];
    Pmf pmf;
};
extern "C" void func_02016128(void *object);
extern "C" void func_0202dc04(UnkStruct_0202dc04 *self)
{
    func_02016128(self);
    if (self->pmf) {
        (self->*(self->pmf))();
    }
}
