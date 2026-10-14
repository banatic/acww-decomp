/* func_0201ce68 @ 0x0201ce68, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201ce68;
typedef void (UnkStruct_0201ce68::*Pmf)(void *, int);
class UnkStruct_0201ce68 {
  public:
    char pad_00[0xd0];
    Pmf pmf;
};
extern Pmf __ptmf_null;
extern "C" int func_020160b4(UnkStruct_0201ce68 *);
extern "C" int func_020ab504(int);
extern "C" void func_0201ce68(UnkStruct_0201ce68 *self, void *arg)
{
    if (self->pmf) {
        int h = func_020160b4(self);
        int v = h ? func_020ab504(h) : -1;
        (self->*(self->pmf))(arg, v);
        self->pmf = __ptmf_null;
    }
}
