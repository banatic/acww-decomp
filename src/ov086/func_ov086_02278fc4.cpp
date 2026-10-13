/* func_ov086_02278fc4 @ 0x02278fc4, 0x4c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278fc4 {
  public:
    unsigned char pad_00[0x654];
    int index;
};

struct PMFEntry {
    int check;
    int pad_04;
    int (UnkStruct_02278fc4::*pmf)();
};

extern PMFEntry data_ov086_02279488[];
extern PMFEntry data_ov086_02279480[];

extern "C" int func_ov086_02278fc4(UnkStruct_02278fc4 *self)
{
    int result = 0;
    int idx = self->index;
    if (data_ov086_02279488[idx].check != 0) {
        result = (self->*data_ov086_02279480[idx].pmf)();
    }
    return result;
}
