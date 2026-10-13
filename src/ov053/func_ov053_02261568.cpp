/* func_ov053_02261568 @ 0x02261568, 0x4c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261568 {
  public:
    virtual int f0();
    virtual int f1();
    char pad_04[0x650];
    int index;
};

typedef int (UnkStruct_02261568::*PMF)();

struct Entry {
    int pad_00;
    int pad_04;
    PMF pmf;
};

extern Entry data_ov053_02261c64[];

extern "C" int func_ov053_02261568(UnkStruct_02261568 *obj)
{
    int result = 0;
    int idx = obj->index;
    if (data_ov053_02261c64[idx].pmf != 0) {
        result = (obj->*data_ov053_02261c64[idx].pmf)();
    }
    return result;
}
