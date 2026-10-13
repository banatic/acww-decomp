/* func_ov049_02262a94 @ 0x02262a94, 0x44 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262a94 {
  public:
    int m();
    char pad[0x654];
    int unk_654;
};

struct PMFEntry {
    int (UnkStruct_02262a94::*pmf)();
    int pad[2];
};

extern PMFEntry data_ov049_02263640[];

extern "C" void func_ov049_02262a94(UnkStruct_02262a94 *self, int idx)
{
    int res = 1;
    if (data_ov049_02263640[idx].pmf) {
        res = (self->*data_ov049_02263640[idx].pmf)();
    }
    if (res) {
        self->unk_654 = idx;
    }
}
