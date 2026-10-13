/* func_ov068_0226e878 @ 0x0226e878, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226e878 {
  public:
    char pad[0x654];
    int field_at_654;
};

struct TableEntry {
    int (UnkStruct_0226e878::*pmf)();
    char pad[8];
};

extern TableEntry data_ov068_02278658[];

extern "C" void func_ov068_0226e878(UnkStruct_0226e878 *self, int i)
{
    int result = 1;
    if (data_ov068_02278658[i].pmf != 0) {
        result = (self->*data_ov068_02278658[i].pmf)();
    }
    if (result != 0) {
        self->field_at_654 = i;
    }
}
