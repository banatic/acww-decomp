/* func_ov083_02278edc @ 0x02278edc, 0x4c bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278edc {
  public:
    virtual int vfunc_00();
    unsigned char pad[0x654];
    int index;
};

typedef int (UnkStruct_02278edc::*PMF)();

struct TestEntry {
    int first;
    int pad[3];
};

struct TableEntry {
    int pad[2];
    PMF pmf;
};

extern TestEntry data_ov083_02279368[];
extern TableEntry data_ov083_02279360[];

int func_ov083_02278edc(UnkStruct_02278edc *self)
{
    int result = 0;
    int idx = self->index;
    if (data_ov083_02279368[idx].first != 0) {
        result = (self->*data_ov083_02279360[idx].pmf)();
    }
    return result;
}
}
