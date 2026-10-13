/* func_0202db04 @ 0x0202db04, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202db04;
typedef void (UnkStruct_0202db04::*Pmf)();
class UnkStruct_0202db04 {
  public:
    char pad_00[0xe8];
    Pmf pmf;
};
extern Pmf data_0213dd98;
extern "C" void func_0202db04(UnkStruct_0202db04 *self)
{
    if (self->pmf) {
        (self->*(self->pmf))();
        self->pmf = data_0213dd98;
    }
}
