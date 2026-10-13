/* func_020a4e94 @ 0x020a4e94, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a4e94;
typedef void (UnkStruct_020a4e94::*Pmf)();
struct Entry {
    Pmf pmf;
    int pad[2];
};
extern Entry data_021f3ea4[];
class UnkStruct_020a4e94 {
  public:
    char pad[0x50];
    int unk_50;
};
extern "C" void func_020a4e94(UnkStruct_020a4e94 *self, int i)
{
    Entry *e = &data_021f3ea4[i];
    if (e->pmf) {
        (self->*(e->pmf))();
    }
    self->unk_50 = i;
}
