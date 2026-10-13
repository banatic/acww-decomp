/* func_0209f820 @ 0x0209f820, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0209f820;
typedef void (UnkStruct_0209f820::*Pmf)();
struct Entry {
    Pmf pmf;
    int pad[2];
};
extern Entry data_021f3ba4[];
class UnkStruct_0209f820 {
  public:
    char pad[0x50];
    int unk_50;
};
extern "C" void func_0209f820(UnkStruct_0209f820 *self, int i)
{
    Entry *e = &data_021f3ba4[i];
    if (e->pmf) {
        (self->*(e->pmf))();
    }
    self->unk_50 = i;
}
