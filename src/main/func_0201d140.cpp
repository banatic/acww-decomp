/* func_0201d140 @ 0x0201d140, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201d140;
typedef void (UnkStruct_0201d140::*Pmf)(void *);
class UnkStruct_0201d140 {
  public:
    char pad_00[0xb8];
    Pmf pmf;
};
extern Pmf data_0213dd98;
extern "C" int func_0201d198(UnkStruct_0201d140 *, void *);
extern "C" void func_0201d140(UnkStruct_0201d140 *self, void *arg)
{
    if (!func_0201d198(self, arg)) {
        if (self->pmf) {
            (self->*(self->pmf))(arg);
            self->pmf = data_0213dd98;
        }
    }
}
