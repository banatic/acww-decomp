/* func_ov047_022624f4 @ 0x022624f4, 0x44 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022624f4 {
  public:
    virtual int vfunc_00()
    {
        return 0;
    }
    char pad[0x650];
    int unk_654;
};

struct PMFEntry {
    int (UnkStruct_022624f4::*pmf)();
    int pad_08[2];
};

extern PMFEntry data_ov047_02263048[];

extern "C" void func_ov047_022624f4(UnkStruct_022624f4 *self, int id)
{
    int ret = 1;
    if (data_ov047_02263048[id].pmf) {
        ret = (self->*data_ov047_02263048[id].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = id;
    }
}
