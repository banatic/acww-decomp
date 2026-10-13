/* func_ov049_02262ad8 @ 0x02262ad8, 0x4c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262ad8 {
  public:
    char pad_00[0x654];
    int index;
};

typedef int (UnkStruct_02262ad8::*PMF)();

struct Entry {
    int pad_00;
    int pad_04;
    PMF pmf;
};

extern Entry data_ov049_02263640[];

extern "C" int func_ov049_02262ad8(UnkStruct_02262ad8 *obj)
{
    int result = 0;
    int i = obj->index;
    if (data_ov049_02263640[i].pmf != 0) {
        result = (obj->*data_ov049_02263640[i].pmf)();
    }
    return result;
}
