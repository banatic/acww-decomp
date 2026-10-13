/* func_ov051_0226122c @ 0x0226122c, 0x44 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226122c {
  public:
    char pad[0x654];
    int unk_654;
    int method();
};
typedef int (UnkStruct_0226122c::*PMF)();
struct PMFEntry {
    PMF pmf;
    int pad[2];
};
extern PMFEntry data_ov051_02261ba8[];
extern "C" void func_ov051_0226122c(UnkStruct_0226122c *self, int index)
{
    int ret = 1;
    if (data_ov051_02261ba8[index].pmf != 0) {
        ret = (self->*data_ov051_02261ba8[index].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = index;
    }
}
